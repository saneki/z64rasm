BUILD_PY := scripts/build.py
PYTHON   := python

# Build for "oot" target by default
all: oot

# Run for "oot" target
oot:
	$(PYTHON) $(BUILD_PY) -t oot
