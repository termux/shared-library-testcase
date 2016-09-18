#include <dlfcn.h>
#include <stdio.h>

typedef void (*plugin_function_t)();

extern int libshared_get_value();

int main() {
	void* plugin_handle = dlopen("./libplugin.so", RTLD_LAZY);
	if (plugin_handle == NULL) {
		printf("dlopen failed: %s\n", dlerror());
		return 1;
	}
	plugin_function_t plugin_function = dlsym(plugin_handle, "plugin_function");
	if (plugin_function == NULL) {
		printf("plugin_function not found\n");
		return 1;
	}

	printf("main: value = %d\n", libshared_get_value());
	plugin_function();

	return 0;
}

