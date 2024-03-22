Input format
============

MooViE accepts the data as single CSV file using **commas** as column delimiters. It expects input variables in the
first columns and output variables after that. The first non-blank non-comment line determines the column header, in
which the input/output variables are further described. The syntax for column headers is
- `i#<input name>[<unit>](<range begin>, <range end>)` for input headers and
- `o#<output name>[<unit>](<range begin>, <range end>)` for output headers.

An example file could look like this:

```text
i#"total length" [m](0, 2), i#"number of iterations", o#profit [$], o#popularity
                       1.2,                        4,          321,            8
                       0.4,                        2,          117,           12
                       1.9,                         ,           50,            1
```

If a column name should contain commas or square brackets, it has to be masked by quotes. Units and ranges are
optional and can be omitted. Empty table cells / NaNs are allowed only for input columns.
