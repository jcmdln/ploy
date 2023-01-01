Ploy is a lisp-like language for my own fun and learning.

# Usage

This section outlines using Ploy on Fedora, though it should work anywhere. If
your platform isn't supported, please file an issue or submit a pull request.

## Build

Building Ploy requires [Meson] and [Ninja] (or [Muon] and [Samurai]), and depends
on [bdwgc] and [GNU Readline]. At some point the dependencies will be removed in
favor of hand-written alternatives.

[bdwgc]: https://github.com/ivmai/bdwgc
[c17]: domain.tld
[clang]: https://releases.llvm.org/7.0.0/tools/clang/docs/UsersManual.html#differences-between-various-standard-modes
[gcc]: https://gcc.gnu.org/onlinedocs/gcc-8.1.0/gcc/Standards.html#C-Language
[meson]: https://mesonbuild.com/
[muon]: https://muon.build/
[msvc]: https://devblogs.microsoft.com/cppblog/c11-and-c17-standard-support-arriving-in-msvc/
[ninja]: https://ninja-build.org/
[readline]: https://git.savannah.gnu.org/cgit/readline.git
[samurai]: https://github.com/michaelforney/samurai

### Release (Default)

By default, Meson will perform a simple release build. See `default_options` in
[meson.build](./meson.build) for specifics.

```sh
sudo dnf install -y gc-devel meson pkgconf readline-devel
meson builddir
ninja -C builddir
```

### Debug

When performing a debug build, install additional sanitizers and manually set
the specified options with Meson:

```sh
sudo dnf install -y clang-tools-extra gc-devel libasan libubsan meson pkgconf readline-devel
meson builddir -Dbuildtype=debugoptimized -Dwerror=true -Db_sanitize=address,undefined
ninja -C builddir
```

## Lint

This section describes how various linters should be used.

### clang-format

See [.clang-format](./.clang-format) for the settings:

```sh
clang-format --dry-run --Werror include/**/*.h src/*.c src/**/*.c
```

### clang-tidy

See [.clang-tidy](./.clang-tidy) for the settings:

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

This section gives thanks for resources that helped to inspire me and/or the
design of Ploy.

- http://www.paulgraham.com/lisp.html
- https://github.com/kanaka/mal
- https://github.com/rui314/minilisp
- https://github.com/krig/LISP
- https://buildyourownlisp.com/
- https://www.gnu.org/software/mes/
