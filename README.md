`ploy` is a (work-in-progress) lisp-like language for my own fun and learning.

# Usage

The following examples show how to build and run `ploy` on Fedora.

## Build

### Release (Default)

```sh
sudo dnf install -y gc-devel meson readline-devel
meson builddir
ninja -C builddir
```

### Debug

```sh
sudo dnf install -y clang clang-tools-extra gc-devel libasan libubsan meson readline-devel
meson builddir -Dbuildtype=debug -Dwerror=true -Doptimization=g -Db_sanitize=address,undefined
ninja -C builddir
```

### Fancy Debug

```sh
sudo dnf -y install \
    ccache clang clang-tools-extra gc-devel libasan libubsan meson mold readline-devel
CC="ccache clang" CC_LD="mold" NINJA="samu" meson builddir \
    -Dbuildtype=debug -Dwerror=true -Doptimization=g -Db_sanitize=address,undefined
samu -C builddir
```

## Test

```sh
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
- https://github.com/kanaka/mal
- https://github.com/krig/LISP
- https://github.com/rui314/minilisp
