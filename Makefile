BUILD_PY := scripts/build.py
PYTHON   := python

# Build for "oot" target by default
all: oot

# Run for "mm" target (Majora's Mask)
mm:
	$(PYTHON) $(BUILD_PY) -t mm --compile-c --virtual

# Run for "oot" target (Ocarina of Time)
oot:
	$(PYTHON) $(BUILD_PY) -t oot --compile-c
