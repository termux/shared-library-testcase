executable: main.c libshared.so libplugin.so
	$(CC) -pie -fPIC -L. main.c -lshared -ldl -o executable

libshared.so: libshared.c
	$(CC) -fPIC -shared -rdynamic libshared.c -o libshared.so

libplugin.so: libplugin.c
	$(CC) -fPIC -shared libplugin.c -o libplugin.so

clean:
	rm -f executable libshared.so libplugin.so testcase.zip

run: executable
	./run.sh

zip: executable
	rm -f testcase.zip
	zip testcase.zip executable libshared.so libplugin.so run.sh


.PHONY: run clean zip
