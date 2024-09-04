Ploy is a (work-in-progress) lisp-like language for my own fun and learning.

Building Ploy requires the following:

- A [c11](<https://en.wikipedia.org/wiki/C11_(C_standard_revision)>) compiler
- [CMake](https://github.com/Kitware/CMake)
- [bdwgc](https://github.com/ivmai/bdwgc)
- [GNU Readline](https://git.savannah.gnu.org/cgit/readline.git)

# Example

```sh
#!/usr/bin/env ploy

(print "Hello, world!")
```

# Using

## Build

### Release

```sh
sudo dnf install -y cmake gc-devel ninja-build pkgconf readline-devel
cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON
ninja -C build
```

### Debug

`-DCMAKE_BUILD_TYPE:STRING="Debug"` requires ASan/UBSan. If you want to avoid
these dependencies use `-DCMAKE_BUILD_TYPE:STRING="RelWithDebInfo"` instead.

```sh
sudo dnf install -y clang-tools-extra libasan libubsan
cmake -B build -DCMAKE_BUILD_TYPE:STRING="Debug" -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON
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
usage: ploy [-h] [-v] [-e EXPR] [-f FILE]

  -h         Show help output
  -v         Show version
  -e EXPR    Evaluate an expression
  -f FILE    Evaluate contents of a FILE
```

# Special Thanks

- https://en.wikipedia.org/wiki/John_McCarthy_(computer_scientist)
- https://github.com/rui314/minilisp
- https://github.com/krig/LISP
- https://github.com/jart/sectorlisp
- https://www.gnu.org/software/mes/
- https://github.com/kanaka/mal
