Ploy is a (work-in-progress) lisp-like language for my own fun and learning.

Building Ploy requires the following:

- A [c11] compiler
- CMake
- [bdwgc]
- [GNU Readline][readline]

[bdwgc]: https://github.com/ivmai/bdwgc
[c11]: https://en.wikipedia.org/wiki/C11_(C_standard_revision)
[cmake]: https://mesonbuild.com/
[readline]: https://git.savannah.gnu.org/cgit/readline.git

# Using

## Build

### Release

```sh
sudo dnf install -y cmake gc-devel ninja-build pkgconf readline-devel
cmake -B build
ninja -C build
```

### Debug

```sh
sudo dnf install -y clang-tools-extra libasan libubsan
cmake -B build \
  -DCMAKE_BUILD_TYPE:STRING="RelWithDebInfo"\
  -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
  -DPLOY_USE_ASAN:BOOL=ON
ninja -C build
```

## Lint

### clang-format

```sh
ninja -C build clang-format
```

### clang-tidy

```sh
ninja -C build clang-tidy
```

## Test

```sh
ninja -C build
ninja -C build test
```

## Run

```sh
$ ./build/ploy -h
usage: ploy [-h] [-e EXPR | -f FILE]

    -e      Evaluate an expression
    -f      Evaluate contents of a FILE
    -h      Show help output
```

# Special Thanks

- https://en.wikipedia.org/wiki/John_McCarthy_(computer_scientist)
- https://github.com/rui314/minilisp
- https://github.com/krig/LISP
- https://github.com/jart/sectorlisp
- https://www.gnu.org/software/mes/
- https://github.com/kanaka/mal
