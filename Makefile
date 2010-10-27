all: sfphysics

sfphysics samples install clean mrproper:
	cd ./build && $(MAKE) $@

examples:
	cd ./examples/build/make && $(MAKE) $@

.PHONY: samples

