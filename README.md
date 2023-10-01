Ploy is a (work-in-progress) lisp-like language for my own fun and learning.

Building Ploy requires the following:

- A [c11] compiler
- [CMake] and [Ninja]
- [bdwgc]
- [linenoise]

[bdwgc]: http://www.hboehm.info/gc/
[c11]: https://en.wikipedia.org/wiki/C11_(C_standard_revision)
[cmake]: https://cmake.org/
[ninja]: https://ninja-build.org/
[linenoise]: https://github.com/antirez/linenoise

# Using

This section describes various ways of using Ploy.

## Build

This section describes building Ploy.

```sh
git clone --origin upstream --recurse-submodules https://github.com/jcmdln/ploy
cd ploy
```

### Release

This section describes performing a release build of Ploy.

```sh
# Fedora
sudo dnf install -y cmake git ninja
```

```sh
mkdir build
cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release
ninja
```

### Debug

This section describes performing a debug build of Ploy.

If you don't want [ASan]/[UBSan], use `-DCMAKE_BUILD_TYPE=RelWithDebInfo`.

[ASan]: https://clang.llvm.org/docs/AddressSanitizer.html
[UBSan]: https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html

```sh
# Fedora
sudo dnf install -y libasan libubsan
```

```sh
mkdir build
cd build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Debug
ninja
```

## Lint

This section describes how various linters can be used.

```sh
# Fedora
sudo dnf install -y clang-tools-extra
```

### clang-format

See [.clang-format](./.clang-format) for the settings:

```sh
ninja -C build clang-format
```

### clang-tidy

See [.clang-tidy](./.clang-tidy) for the settings:

```sh
ninja -C build clang-tidy
```

## Test

This section describes how to run tests.

## Run

This section describes running Ploy

```sh
$ ./build/ploy -h
usage: ploy [-h] [-e EXPR | -f FILE]

    -e      Evaluate an expression
    -f      Evaluate contents of a FILE
    -h      Show help output
```

## Install

This section describes installing Ploy.

```sh
ninja -C build install
```

## Uninstall

This section describes uninstalling Ploy.

```sh
ninja -C build uninstall
```

# Special Thanks

- https://en.wikipedia.org/wiki/John_McCarthy_(computer_scientist)
- https://github.com/rui314/minilisp
- https://github.com/krig/LISP
- https://github.com/jart/sectorlisp
- https://www.gnu.org/software/mes/
- https://github.com/kanaka/mal
