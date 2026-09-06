### 1.2.2




* fix floating point argument sizing and alignment (float/double now use proper fp size and alignment rules)
* fix function pointer pushes (aligned and copied correctly) and pointer reads via `mulle_vararg_next_pointer`
* fix `mulle_vararg_push_union` macro using an undefined `p` instead of the argument list
* switch builder buffer alignment from double to long double
* add builder tests for fp alignment, sizes, struct/union/pointer/functionpointer pushes



* add BSD-3-Clause license header to mulle-vararg-builder.h
* fix stale project attribution in mulle-align.h and mulle-vararg.h headers

### 1.2.1

Various small improvements
