This directory contains tests for validating Ploy.

# Printer

```c
#include <ploy/ploy.h>

int
main(void) {
    // Read("(wew :lad \"foo bar\" (wew :lad \"foo bar\" (wew :lad \"foo bar\")))")
    struct object *head = object_nil();
    head = Append(head, object_symbol("wew"));
    head = Append(head, object_keyword("lad"));
    head = Append(head, object_string("Hello, world!"));
    struct object *mid = object_nil();
    mid = Append(mid, object_symbol("foo"));
    mid = Append(mid, object_keyword("bar"));
    mid = Append(mid, object_string("Hello, again!"));
    struct object *tail = object_nil();
    tail = Append(tail, object_symbol("wew"));
    tail = Append(tail, object_keyword("lad"));
    tail = Append(tail, object_string("And yet again!"));
    Print(Append(head, Append(mid, tail)));
}
```

# Reader

```c
puts("form: (wew :lad \"foo bar\")");
Print(Eval(Read("wew :lad \"foo bar\"")));
Print(Eval(Read("(wew :lad \"foo bar\")")));
putchar('\n');

puts("form: (wew :lad \"foo bar\" (wew :lad \"foo bar\"))");
Print(Eval(Read("wew :lad \"foo bar\" (wew :lad \"foo bar\")")));
Print(Eval(Read("(wew :lad \"foo bar\" (wew :lad \"foo bar\"))")));
putchar('\n');

puts("form: (wew :lad \"foo bar\" (wew :lad \"foo bar\" (wew :lad \"foo bar\")))");
Print(Eval(Read("wew :lad \"foo bar\" (wew :lad \"foo bar\" (wew :lad \"foo bar\"))")));
Print(Eval(Read("(wew :lad \"foo bar\" (wew :lad \"foo bar\" (wew :lad \"foo bar\")))")));
putchar('\n');

puts("form: (((wew :lad \"foo bar\") wew :lad \"foo bar\") wew :lad \"foo bar\")");
Print(Eval(Read("((wew :lad \"foo bar\") wew :lad \"foo bar\") wew :lad \"foo bar\"")));
Print(Eval(Read("(((wew :lad \"foo bar\") wew :lad \"foo bar\") wew :lad \"foo bar\")")));
putchar('\n');

puts("form: ((wew :lad \"foo bar\") wew :lad \"foo bar\")");
Print(Eval(Read("(wew :lad \"foo bar\") wew :lad \"foo bar\"")));
Print(Eval(Read("((wew :lad \"foo bar\") wew :lad \"foo bar\")")));
putchar('\n');
```
