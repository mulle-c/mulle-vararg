### 1.2.3



* `add_subdirectory` consumers now again inherit the library include directory, so `#include `<mulle-core/mulle-core.h>`` resolves without extra setup
* whole-archive force-linking now requires CMake 3.30, preventing generate failures on CMake 3.24-3.29









* exercise all `mulle_vararg_sizeof_*` and `mulle_vararg_alignof_*` convenience macros to catch routing regressions such as the `sizeof_float` issue
* round-trip every typed `mulle_vararg_push_*/next_*` pair, plus `mulle_vararg_builder_do` and `mulle_vararg_start_fp`

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
