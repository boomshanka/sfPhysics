all: sfphysics

sfphysics samples install clean mrproper sfml nosfml:
	cd ./build && $(MAKE) $@

.PHONY: samples


