Shared library symbols not visible on dlopen()
==============================================
This project contains the following files:

1. `libshared.c` which contains the function `libshared_get_value()`. It is built as a shared library named `libshared.so`.
2. `libplugin.c` which has a simple function calling an extern function `libshared_get_value()`. It does not link against `libshared.so`.
3. `main.c` which is linked against `libshared.so` and calls `libshared_get_value()`. It also `dlopen()`:s the `libplugin.so` shared library.

This works on "normal" Linux (tested on Ubuntu 16.04).

This does not work on Android (tested on Android 5.0/arm and 6.0/aarch) with the error message `cannot locate symbol "libshared_get_value" referenced by "libplugin.so"`.

This difference in behaviour causes problems for things like perl and node, where extensions built as shared libraries expects symbols from already loaded libraries to be visible without needing to link against the libraries containing the symbols explicitly. See e.g. [How To Link -lperl to Extensions During Build](http://www.perlmonks.org/?node_id=1126197) where it's simply stated as:

> Thanks to its broken linker, I need to link libperl.so with every extension that uses symbols from it.

Is the Android linker or tools really broken in this regard, or is the behaviour the expected one?

