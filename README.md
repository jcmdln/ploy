`ploy` is a lisp-like programming language for fun and learning.


Usage
---
The following examples show how to build and run `ploy` on Fedora.

```sh
# Release build (Default)
$ sudo dnf install -y gc-devel meson readline-devel
$ meson builddir

# Debug build /w ccache and clang++
$ sudo dnf install -y ccache clang-tools-extra libasan libubsan
$ CXX="ccache clang++" CXX_LD="lld" meson builddir -Dbuildtype=debug \
    -Dwerror=true -Doptimization=g -Db_sanitize=address,undefined

# Compile
$ meson compile -C builddir

# Run
$ ./builddir/ploy
Ploy v0.0.0
Press Ctrl+c to exit

λ ("wew")
("wew")
```


Special Thanks
---
* http://www.paulgraham.com/lisp.html
* https://github.com/krig/LISP
* https://github.com/rui314/minilisp
* https://github.com/kanaka/mal
* https://github.com/seven1m/mal-cpp
