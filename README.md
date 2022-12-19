`ploy` is a lisp-like language for my own fun and learning.

# Usage

## Build

### Release (Default)

```sh
sudo dnf install -y gc-devel meson pkgconf readline-devel
meson builddir
ninja -C builddir
```

### Debug

```sh
sudo dnf install -y clang-tools-extra gc-devel libasan libubsan meson pkgconf readline-devel
meson builddir -Dbuildtype=debug -Dwerror=true -Doptimization=g -Db_sanitize=address,undefined
ninja -C builddir
```

## Lint

### clang-format

```sh
clang-format --dry-run --Werror include/**/*.h src/*.c src/**/*.c
```

### clang-tidy

```sh
clang-tidy -p ./builddir include/**/*.h src/*.c src/**/*.c
```

## Test

No real tests are written, but the plumbing is workable.

```sh
# FIXME: https://github.com/mesonbuild/meson/issues/2518
# FIXME: https://github.com/mesonbuild/meson/pull/6511
meson configure builddir -Dtest=true
ninja -C builddir test
```

## Run

```sh
./builddir/ploy -h
usage: ploy [-h] [-e STRING]

    -h      Show help output
    -e      Evaluate an expression
```

## Install

```sh
ninja -C builddir install
```

## Uninstall

```sh
ninja -C builddir uninstall
```

# Special Thanks

- http://www.paulgraham.com/lisp.html
- https://buildyourownlisp.com/
- https://github.com/kanaka/mal
- https://github.com/rui314/minilisp
- https://github.com/krig/LISP
