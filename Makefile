all: sfphysics

sfphysics samples install clean mrproper:
	cd ./build && $(MAKE) $@

.PHONY: samples


