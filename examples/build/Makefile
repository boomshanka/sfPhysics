export SRCROOT  = ..
export CPP      = g++
export CFLAGS   = -W -Wall -ansi -g -O2 -DNDEBUG
export EXAMPLES = rocket moonlander tower

samples: all

all: $(EXAMPLES)

$(EXAMPLES):
	$(MAKE) -f Makefile.$@

clean mrproper:
	for example in $(EXAMPLES); do $(MAKE) $@ -f Makefile.$${example}; done

.PHONY: clean mrproper

