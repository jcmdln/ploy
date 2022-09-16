This directory contains tests for validating Ploy.

# Printer

Testing the printer requires hand-crafting objects and comparing the tree to
the output of the Reader.

```c
// clang-format off

// reader("(wew :lad \"foo bar\" (wew :lad \"foo bar\" (wew :lad \"foo bar\")))")
Print(
    object_list(list_new(
        object_symbol("wew"),
        object_list(list_new(
            object_keyword("lad"),
            object_list(list_new(
                object_string("foo bar"),
                object_nil()
            ))
        ))
    ))
);

// reader("(((wew :lad \"foo bar\") wew :lad \"foo bar\") wew :lad \"foo bar\")")
Print(
    object_list(list_new(
        object_list(list_new(
            object_list(list_new(
                object_symbol("wew"),
                object_list(list_new(
                    object_keyword("lad"),
                    object_list(list_new(
                        object_string("foo bar"),
                        object_nil()
                    ))
                ))
            )),
            object_list(list_new(
                object_symbol("wew"),
                object_list(list_new(
                    object_keyword("lad"),
                    object_list(list_new(
                        object_string("foo bar"),
                        object_nil()
                    ))
                ))
            ))
        )),
        object_list(list_new(
            object_symbol("wew"),
            object_list(list_new(
                object_keyword("lad"),
                object_list(list_new(
                    object_string("foo bar"),
                    object_nil()
                ))
            ))
        ))
    ))
);

// clang-format on
```

# Reader

## Lexer

## Parser

```py
# Valid forms
wew :lad "foobar"
(wew :lad "foobar")

wew :lad "foobar" (wew :lad "foobar")
(wew :lad "foobar" (wew :lad "foobar"))

(wew :lad "foobar") wew :lad "foobar"
((wew :lad "foobar") wew :lad "foobar")
```
