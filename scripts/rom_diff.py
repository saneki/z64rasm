#!/usr/bin/env/python3

import argparse
import ctypes
import json
import struct
import sys

class TableEntry(ctypes.BigEndianStructure):
    """ Table entry structure. """
    _fields_ = (
        ('virt_start', ctypes.c_uint),
        ('virt_end', ctypes.c_uint),
        ('phys_start', ctypes.c_uint),
        ('phys_end', ctypes.c_uint),
    )

    def empty(self):
        """ Whether or not this entry is "empty." """
        return self.virt_start == self.virt_end == self.phys_start == self.phys_end == 0

    def does_not_exist(self):
        """ Whether or not this is a "DoesNotExist" file entry. """
        return self.phys_end == 0xFFFFFFFF

    def is_decompressed(self):
        """ Whether or not this data is decompressed. """
        return self.phys_end == 0

    def decompressed_size(self):
        """ Get size of decompressed data. """
        return self.virt_end - self.virt_start

    def read(self, file):
        """ Read a TableEntry from a file. """
        self.receiveSome(file.read(ctypes.sizeof(self)))
        return self

    def receiveSome(self, data):
        """ Parse from bytes. """
        fit = min(len(data), ctypes.sizeof(self))
        ctypes.memmove(ctypes.addressof(self), data, fit)

class Table(object):
    """ Parsed file table with entries. """
    def __init__(self, offset, entries):
        self._offset = offset
        self._entries = entries

    @staticmethod
    def read(file, offset):
        """ Read a Table from a file and offset. """
        entries = tuple(read_table(file, offset))
        return Table(offset, entries)

    def resolve(self, physical):
        """ Resolve a physical address to a virtual. """
        for entry in self._entries:
            if entry.empty() or entry.does_not_exist():
                continue
            if entry.is_decompressed():
                size = entry.decompressed_size()
                end = entry.phys_start + size
                if entry.phys_start <= physical < end:
                    return (physical - entry.phys_start) + entry.virt_start
            else:
                raise Exception('Must be a fully decompressed ROM! {:08X}'.format(entry.virt_start))

def read_table(file, offset):
    """ Generator for reading all table entries in a file. """
    table_start = offset
    table_entry = None
    while True:
        file.seek(offset)
        entry = TableEntry().read(file)

        # Check if found table entry
        if entry.phys_start == table_start:
            table_entry = entry

        # Check if at end of table
        if table_entry is not None:
            end = table_entry.phys_start + table_entry.decompressed_size()
            if offset >= end:
                break

        offset += ctypes.sizeof(entry)
        yield entry

def get_parser():
    """ Get the argument parser. """
    def auto_int(x):
        return int(x, 0)
    parser = argparse.ArgumentParser()
    parser.add_argument('--table-offset', type=auto_int, help='Offset of file table (use with --virtual)')
    parser.add_argument('--virtual', action='store_true', help='Get virtual addresses instead of physical')
    parser.add_argument('BASE_FILE')
    parser.add_argument('COMPARISON_FILE')
    parser.add_argument('OUTPUT_FILE')
    return parser

def main():
    args = get_parser().parse_args()
    create_diff(args.base_file, args.comparison_file, args.output_file,
        offset=args.table_offset, virtual=args.virtual)

chunk_size = 4096
uint32 = struct.Struct('>I')

def unequal_chunks(file1, file2):
    addr = 0
    while True:
        chunk1 = file1.read(chunk_size)
        chunk2 = file2.read(chunk_size)
        if not chunk1:
            return
        if chunk1 != chunk2:
            words1 = [x[0] for x in uint32.iter_unpack(chunk1)]
            words2 = [x[0] for x in uint32.iter_unpack(chunk2)]
            yield (addr, words1, words2)
        addr += chunk_size

def create_diff(base_path, compare_path, output_path, virtual=False, offset=0):
    diffs = []
    with open(base_path, 'rb') as base_f, open(compare_path, 'rb') as comp_f:
        # Read file table if specified
        table = None
        if virtual:
            table = Table.read(comp_f, offset)
            comp_f.seek(0)
        # Find diffs
        for (addr, base_words, comp_words) in unequal_chunks(base_f, comp_f):
            for j in range(len(comp_words)):
                if comp_words[j] != base_words[j]:
                    found = addr + 4*j
                    # Resolve physical address to virtual address if specified
                    if virtual:
                        found = table.resolve(found)
                    diffs.append((found, comp_words[j]))

    with open(output_path, 'w') as out_f:
        for (addr, word) in diffs:
            out_f.write('{0:x},{1:x}\n'.format(addr, word))

if __name__ == '__main__':
    main()
