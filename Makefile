# SPDX-License-Identifier: ISC
#
# Copyright (c) 2023 Johnathan C Maudlin <jcmdln@gmail.com>
.POSIX:

VERSION = 0.0.1

CC      = cc
CFLAGS  = -O2 -std=c11 \
	-fshort-wchar -fstrict-aliasing -funsigned-char \
	-Wall -Wextra -pedantic \
	-Werror=cast-qual \
	-Werror=conversion \
	-Werror=implicit-int \
	-Werror=strict-prototypes \
	-Werror=switch \
	-Werror=vla \
	-Werror=write-strings
LDFLAGS = -D_DEFAULT_SOURCE -DPLOY_VERSION=\"$(VERSION)\" \
	-Iinclude/ -lgc -lm -lreadline -pthread
PREFIX  = /usr/local
SOURCES = \
	src/main.c \
	src/core.c \
	src/evaluator.c \
	src/math.c \
	src/printer.c \
	src/reader.c \
	src/type.c

all: release

clean:
	rm -f ploy

debug: $(SOURCES)
	$(CC) -g -Werror $(CFLAGS) -o ploy $(SOURCES) $(LDFLAGS)
asan: $(SOURCES)
	$(CC) -g -Werror -fsanitize=address,undefined $(CFLAGS) -o ploy $(SOURCES) $(LDFLAGS)
tsan: $(SOURCES)
	$(CC) -g -Werror -fsanitize=thread $(CFLAGS) -o ploy $(SOURCES) $(LDFLAGS)
release: $(SOURCES)
	$(CC) $(CFLAGS) -o ploy $(SOURCES) $(LDFLAGS)

# install:
#
# uninstall:
