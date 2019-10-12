#!/usr/bin/env python3

import sys
import os

import argparse
import json
import re
from subprocess import check_call as call

from rom_diff import create_diff
from ntype import BigStream
from crc import calculate_crc

def build_data_symbols(symbols):
    data_symbols = {}
    for (name, sym) in symbols.items():
        if sym['type'] == 'data':
            addr = int(sym['address'], 16)
            if 0x80400000 <= addr < 0x80420000:
                addr = addr - 0x80400000 + 0x03480000
            else:
                continue
            data_symbols[name] = '{0:08X}'.format(addr)
    return data_symbols

def dump_json_to_file(data, path):
    with open(path, 'w') as f:
        json.dump(data, f, indent=4, sort_keys=True)

def fixup_asm_symbols(path):
    with open(path, 'rb') as f:
        asm_symbols_content = f.read()
    asm_symbols_content = asm_symbols_content.replace(b'\r\n', b'\n')
    asm_symbols_content = asm_symbols_content.replace(b'\x1A', b'')
    with open(path, 'wb') as f:
        f.write(asm_symbols_content)

def parse_asm_symbols(path, c_symbols):
    symbols = {}
    with open(path, 'r') as f:
        for line in f:
            parts = line.strip().split(' ')
            if len(parts) < 2:
                continue
            address, sym_name = parts
            if address[0] != '8':
                continue
            if sym_name[0] in ['.', '@']:
                continue
            sym_type = c_symbols.get(sym_name) or ('data' if sym_name.isupper() else 'code')
            symbols[sym_name] = {
                'type': sym_type,
                'address': address,
            }
    return symbols

def parse_c_symbols(path):
    c_sym_types = {}
    with open(path, 'r') as f:
        for line in f:
            m = re.match(r'''
                    ^
                    [0-9a-fA-F]+
                    .*
                    \.
                    ([^\s]+)
                    \s+
                    [0-9a-fA-F]+
                    \s+
                    ([^.$][^\s]+)
                    \s+$
                ''', line, re.VERBOSE)
            if m:
                sym_type = m.group(1)
                name = m.group(2)
                c_sym_types[name] = 'code' if sym_type == 'text' else 'data'
    return c_sym_types

def update_crc(path):
    with open(path, 'r+b') as stream:
        buffer = bytearray(stream.read(0x101000))
        crc = calculate_crc(BigStream(buffer))
        stream.seek(0x10)
        stream.write(bytearray(crc))

def write_pj64_symbols(f, symbols):
    key = lambda pair: pair[1]['address']
    for sym_name, sym in sorted(symbols.items(), key=key):
        f.write('{0},{1},{2}\n'.format(sym['address'], sym['type'], sym_name))

def get_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument('--pj64sym', help="Output path for PJ64 debugging symbols")
    parser.add_argument('--compile-c', action='store_true', help="Recompile C modules")
    return parser

def main():
    args = get_parser().parse_args()
    pj64_sym_path = args.pj64sym
    compile_c = args.compile_c

    script_dir = os.path.dirname(os.path.realpath(__file__))
    run_dir = script_dir + '/..'
    os.chdir(run_dir)

    # Compile code

    os.environ['PATH'] = script_dir + os.pathsep + os.environ['PATH']

    if compile_c:
        os.chdir(run_dir + '/target/oot/c')
        call(['make'])

    os.chdir(run_dir + '/target/oot/src')
    call(['armips', '-sym2', '../build/asm_symbols.txt', 'build.asm'])
    os.chdir(run_dir)

    fixup_asm_symbols('target/oot/build/asm_symbols.txt')

    # ...
    c_sym_types = parse_c_symbols('target/oot/build/c_symbols.txt')

    # ...
    symbols = parse_asm_symbols('target/oot/build/asm_symbols.txt', c_sym_types)

    # Output symbols

    os.chdir(run_dir)

    # Dump symbols as JSON
    data_symbols = build_data_symbols(symbols)
    dump_json_to_file(data_symbols, 'target/oot/data/generated/symbols.json')

    if pj64_sym_path:
        pj64_sym_path = os.path.realpath(pj64_sym_path)
        with open(pj64_sym_path, 'w') as f:
            write_pj64_symbols(f, symbols)

    update_crc('target/oot/roms/patched.z64')

    # Diff ROMs
    create_diff('target/oot/roms/base.z64', 'target/oot/roms/patched.z64', 'target/oot/data/generated/rom_patch.txt')

if __name__ == '__main__':
    main()
