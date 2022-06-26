`ploy` is a simple lisp/scheme implementation for my own fun and learning.

## Usage

The following example shows how to build and run `ploy` on Fedora.

```sh
# Release build (Default)
$ sudo dnf install -y gc-devel meson readline-devel
$ meson builddir

# Debug build
$ sudo dnf install -y clang-tools-extra libasan libubsan
$ meson builddir -Dbuildtype=debug -Dwerror=true -Doptimization=g -Db_sanitize=address,undefined

# Fancier debug build example using ccache, clang, mold
$ sudo dnf install -y ccache clang mold
$ CC="ccache clang" CC_LD="mold" meson builddir \
    -Dbuildtype=debug -Dwerror=true -Doptimization=g -Db_sanitize=address,undefined

# Compile
$ meson compile -C builddir

# Run
$ ./builddir/ploy
Ploy v0.0.0
Press Ctrl+c to exit

λ ("wew")
("wew")
```

## Special Thanks

- http://www.paulgraham.com/lisp.html
- https://github.com/kanaka/mal
- https://github.com/krig/LISP
- https://github.com/rui314/minilisp
