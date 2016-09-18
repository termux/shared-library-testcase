#include <stdio.h>

extern int libshared_get_value();

void plugin_function() {
	printf("plugin: value = %d\n", libshared_get_value());
}
