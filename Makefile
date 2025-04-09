prefertmpaddr.so: prefertmpaddr.c
	gcc -nostartfiles -fpic -shared $< -o $@ -ldl -D_GNU_SOURCE
	strip $@

$(HOME)/lib/%.so: %.so
	mkdir -p $(@D)
	cp -f $< $@

install: $(HOME)/lib/prefertmpaddr.so

clean:
	rm -f prefertmpaddr.so
