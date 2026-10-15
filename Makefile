SGDK_PATH ?= /sgdk

all:
	make -f $(SGDK_PATH)/makefile.gen

clean:
	make -f $(SGDK_PATH)/makefile.gen clean

.PHONY: all clean
