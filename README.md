Ploy is a (work-in-progress) lisp-like language for my own fun and learning.

Building Ploy requires the following:

- A [c11] compiler
- [Meson] (or [Muon]) and [Ninja] (or [Samurai])
- [bdwgc]
- [GNU Readline][readline]

[bdwgc]: https://github.com/ivmai/bdwgc
[c11]: https://en.wikipedia.org/wiki/C11_(C_standard_revision)
[meson]: https://mesonbuild.com/
[muon]: https://muon.build/
[ninja]: https://ninja-build.org/
[readline]: https://git.savannah.gnu.org/cgit/readline.git
[samurai]: https://github.com/michaelforney/samurai

# Using

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

When setting up the meson builddir, you may want to consider setting additional
environment variables to specify an alternate compiler, linker, meson or ninja
implementation:

```sh
CC="clang" CC_LD="mold" NINJA="samu" \
muon setup -Db_sanitize=address,undefined -Dbuildtype=debugoptimized -Dwerror=true builddir
samu -C builddir
```

## Lint

This section describes how various linters should be used.

### clang-format

See [.clang-format](./.clang-format) for the settings:

```sh
ninja -C builddir clang-format
```

### clang-tidy

See [.clang-tidy](./.clang-tidy) for the settings:

```sh
ninja -C builddir clang-tidy
```

## Test

This section describes how to run tests.

### meson

- https://github.com/mesonbuild/meson/issues/2518
- https://github.com/mesonbuild/meson/pull/6511

```sh
ninja -C builddir test
```

### muon

```sh
muon -C builddir test
```

## Run

```sh
$ ./builddir/ploy -h
usage: ploy [-h] [-e EXPR | -f FILE]

    -e      Evaluate an expression
    -f      Evaluate contents of a FILE
    -h      Show help output

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

- https://en.wikipedia.org/wiki/John_McCarthy_(computer_scientist)
- https://github.com/rui314/minilisp
- https://github.com/krig/LISP
- https://github.com/jart/sectorlisp
- https://www.gnu.org/software/mes/
- https://github.com/kanaka/mal
