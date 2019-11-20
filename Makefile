BUILD_PY := scripts/build.py
PYTHON   := python

# Build for Majora's Mask by default
all: mm

# Build for "mm" target (Majora's Mask)
mm:
	$(PYTHON) $(BUILD_PY) -t mm --compile-c --virtual

# Build for "oot" target (Ocarina of Time)
oot:
	$(PYTHON) $(BUILD_PY) -t oot --compile-c
