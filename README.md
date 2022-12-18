`ploy` is a lisp-like language for my own fun and learning.

# Usage

The following examples show how to build and run `ploy` on Fedora.

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

## Test

```sh
# FIXME: https://github.com/mesonbuild/meson/issues/2518
# FIXME: https://github.com/mesonbuild/meson/pull/6511
meson configure builddir -Dtest=true
ninja -C builddir test
```

## Run

```sh
./builddir/ploy
```

## Install

```sh
ninja install -C builddir
```

## Uninstall

```sh
ninja uninstall -C builddir
```

# Special Thanks

- http://www.paulgraham.com/lisp.html
- https://buildyourownlisp.com/
- https://github.com/kanaka/mal
- https://github.com/rui314/minilisp
- https://github.com/krig/LISP
