This directory contains tests for validating Ploy.

# Printer

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

                object_list(list_new(
                    object_list(list_new(
                        object_symbol("wew"),
                        object_list(list_new(
                            object_keyword("lad"),
                            object_list(list_new(
                                object_string("foo bar"),

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
                                    object_nil()
                                ))

                            ))
                        ))
                    )),
                    object_nil()
                ))

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
