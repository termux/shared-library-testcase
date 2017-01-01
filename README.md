Shared library symbols not visible on dlopen()
==============================================
This project contains the following files:

1. `libshared.c` which contains the function `libshared_get_value()`. It is built as a shared library named `libshared.so`.
2. `libplugin.c` which has a simple function calling an extern function `libshared_get_value()`. It does not link against `libshared.so`.
3. `main.c` which is linked against `libshared.so` and calls `libshared_get_value()`. It also `dlopen()`:s the `libplugin.so` shared library.

This works on "normal" Linux (tested on Ubuntu 16.04).

This does not work on Android (tested on Android 5.0/arm and 6.0/aarch) but fails at runtime with the error message `cannot locate symbol "libshared_get_value" referenced by "libplugin.so"`.

This difference in behaviour causes problems for things like perl and node, where extensions built as shared libraries expects symbols from already loaded libraries to be visible without needing to link against the libraries containing the symbols explicitly. See e.g. [How To Link -lperl to Extensions During Build](http://www.perlmonks.org/?node_id=1126197) where the following is said:

> Thanks to its broken linker, I need to link libperl.so with every extension that uses symbols from it.

Is the Android linker (or tools) really broken in this regard, or is the behaviour the expected one?

Reproducing
===========
Run `make run` to test this on Linux.

Run `make clean` and `CC=PATH_TO_NDK_STANDALONE_TOOLCHAIN/bin/CC_NAME make zip` to create a `testcase.zip` file. This file can be extracted on an Android device and be run using the contained `./run.sh` script.


Cause
=====
See https://github.com/android-ndk/ndk/issues/201:

> tl;dr; This one of the not many differences between linux loader and android loader. On Android only the main executable and LD_PRELOADs are considered to be RTLD_GLOBAL, all the dependencies of the main executable remain RTLD_LOCAL.
> 
> Longer explanation:
> 
> ld-linux.so marks everything linked against main executable with RTLD_GLOBAL, this is why the example works on Linux. Android loader was not handling RTLD_GLOBAL correctly up until M release. It was fixed in M for things like dlopen/dlsym() but not for the dependencies of the main executable, because it lead to many compatibility problems.
> 
> Workaround:
> 
> Adding libshared.so dependency to libplugin.so should solve this problem and make the executable.
