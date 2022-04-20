`ploy` is a simple lisp/scheme implementation for my own fun and learning.


Usage
---
The following example shows how to build and run `ploy` on Fedora.

```sh
# Release build (Default)
$ sudo dnf install -y gc-devel meson readline-devel
$ meson builddir

# Debug build
$ sudo dnf install -y libasan libubsan
$ meson builddir -Dbuildtype=debug -Dwerror=true -Doptimization=g -Db_sanitize=address,undefined

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
