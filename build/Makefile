export SRCROOT    = ../src/sfPhysics
export DESTDIR    = /usr/local
export DESTLIBDIR = $(DESTDIR)/lib
export DESTINCDIR = $(DESTDIR)/include
export DESTDBGDIR = $(DESTLIBDIR)/debug/$(DESTLIBDIR)
export CC         = gcc
export CPP        = colorgcc ## g++
export CFLAGS     = -W -Wall -pedantic -g -O2 -DNDEBUG -I../include -I../src -fPIC
export CFLAGSEXT  = -I../include -I../src -g -O2 -DNDEBUG -fPIC
export LDFLAGS    = -shared
export SFMLFLAGS  = -DSFML_ENABLED
export LIBPATH    = ../lib
export VERSION    = 1.0
export CP         = cp
export LN         = ln
export LNFLAGS    = -s -f
export LIBS       = system collision


all: sfphysics

sfml: sfmlbuild sfphysics
	
nosfml: nosfmlbuild sfphysics

sfphysics: $(LIBS)


sfmlbuild:
	$(SFMLFLAGS) = -DSFML_ENABLED
	
nosfmlbuild:
	$(SFMLFLAGS) = -DSFML_DISABLED
	

samples:
	cd ../examples/build && $(MAKE)

$(LIBS):
	mkdir -p $(LIBPATH)
	$(MAKE) -f Makefile.$@

install:
	mkdir -p $(DESTLIBDIR)
	mkdir -p $(DESTINCDIR)
	mkdir -p $(DESTDBGDIR)
	$(CP) -r ../include/sfPhysics/ $(DESTINCDIR)/
	find $(DESTINCDIR)/sfPhysics -name .svn -type d -print0 | xargs -0 /bin/rm -rf
	$(MAKE) $@ -f Makefile.system
	$(MAKE) $@ -f Makefile.collision

clean mrproper:
	$(MAKE) $@ -f Makefile.system
	$(MAKE) $@ -f Makefile.collision
	cd ../examples/build && $(MAKE) $@

.PHONY: clean mrproper


