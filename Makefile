bin/yndent: src/yndent.c
	mkdir -p bin
	c99 $^ -o $@
