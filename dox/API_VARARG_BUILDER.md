# mulle-vararg-builder API

The builder lets you **construct** a variable argument list in a plain C
buffer, without a special compiler. The produced list can then be passed to
any consumer that reads `mulle_vararg_list`, such as `mulle_mvsprintf`.


## How to use it

Link against `mulle_vararg` and
`#include <mulle-vararg/mulle-vararg.h>` in your code.

Here is an example. You want to pass an `int` value and a `long` value to a
variable argument consumer such as `mulle_mvsprintf`.

The critical part is the proper estimation of the required size of the
buffer. Use the `mulle_vararg_sizeof_*`/`mulle_vararg_alignof_*` macros for
that — they already account for the C promotion rules
(`char`/`short` → `int`, `float` → `double`).

``` c
#include <mulle-vararg/mulle-vararg.h>

#include <stdio.h>


#define BUFFER_SIZE                                                       \
   mulle_vararg_builderbuffer_n( mulle_vararg_sizeof_integer( int) +      \
                                 mulle_vararg_sizeof_integer( long))


int   main( void)
{
   mulle_vararg_builderbuffer_t  buf[ BUFFER_SIZE];
   mulle_vararg_list             list;
   mulle_vararg_list             q;
   int                           i;
   long                          l;

   //
   // build up variable argument list
   //
   list = mulle_vararg_list_make( buf);

   mulle_vararg_copy( q, list);
   mulle_vararg_push_int( q, 18);
   mulle_vararg_push_long( q, 48L);

   //
   // hand the list to a consumer (here we read it back ourselves).
   // Read arguments in separate statements — the order of evaluation of
   // function arguments is unspecified in C.
   //
   i = mulle_vararg_next_integer( list, int);
   l = mulle_vararg_next_integer( list, long);
   printf( "%d %ld\n", i, l);

   return( 0);
}
```

This will print `18 48`.

To hand the built list to `mulle_mvsprintf` instead (from the
[mulle-sprintf](https://github.com/mulle-c/mulle-sprintf) component of
mulle-core):

``` c
char                       out[ 64];

mulle_mvsprintf( out, "%d %ld", list);
printf( "%s\n", out);      // prints: 18 48
```

> Only `mulle-c11` is required for the builder itself (plus `mulle-allocator`
> if you use `mulle_vararg_builder_do`, see below). `mulle_sprintf` etc. are
> optional consumers from other mulle-core components.


## Types

Type                           | Description
-------------------------------|------------------------------------------------
`mulle_vararg_list`            | The variable argument storage (from `mulle-vararg.h`).
`mulle_vararg_builderbuffer_t` | The buffer element type (`long double`). Its alignment satisfies the strictest argument alignment (`alignof( long double)`).


## Macros


### `mulle_vararg_builderbuffer_n`

`mulle_vararg_builderbuffer_n( n)`

The number of `mulle_vararg_builderbuffer_t` elements needed to hold **n**
bytes of vararg data. Use it to size your buffer array:

``` c
mulle_vararg_builderbuffer_t   buf[ mulle_vararg_builderbuffer_n( size)];
```


### `mulle_vararg_list_make`

`mulle_vararg_list   mulle_vararg_list_make( void *buf)`

Turn a buffer into a `mulle_vararg_list` pointing at its start. Pass the
result to a consumer (e.g. `mulle_mvsprintf`).


### `mulle_vararg_copy`

`mulle_vararg_copy( dst, src)`

Copy a list, so you can push into the copy without losing the start address
of the original (see the example above).


### Sizing macros

These compute the slot size/alignment of an argument **as laid out in the
vararg buffer** (i.e. after C promotion). Use them to size your buffer and to
reason about the layout:

| Macro | Meaning |
|---|---|
| `mulle_vararg_sizeof_integer( type)` | slot size of an integer argument |
| `mulle_vararg_alignof_integer( type)` | slot alignment of an integer argument |
| `mulle_vararg_sizeof_fp( type)` | slot size of a floating point argument |
| `mulle_vararg_alignof_fp( type)` | slot alignment of a floating point argument |
| `mulle_vararg_sizeof_pointer( type)` | slot size of a pointer argument (`sizeof( void *)`) |
| `mulle_vararg_alignof_pointer( type)` | slot alignment of a pointer argument |
| `mulle_vararg_sizeof_functionpointer( type)` | slot size of a function pointer argument |
| `mulle_vararg_alignof_functionpointer( type)` | slot alignment of a function pointer argument |
| `mulle_vararg_sizeof_struct( type)` | slot size of a struct argument |
| `mulle_vararg_alignof_struct( type)` | slot alignment of a struct argument |

The `mulle_vararg_sizeof_char()` … `mulle_vararg_sizeof_double()`
convenience macros delegate to the generic ones above, e.g.
`mulle_vararg_sizeof_float()` is `mulle_vararg_sizeof_fp( float)` and
therefore returns `sizeof( double)` (a `float` occupies a `double`-sized
slot).


### `mulle_vararg_push_integer`

`mulle_vararg_push_integer( ap, type, value)`

Push an integer **value** of **type** into the buffer. Small types are stored
in an `int`-sized slot (C promotion).


### `mulle_vararg_push_fp`

`mulle_vararg_push_fp( ap, type, value)`

Push a floating point **value** of **type**. `float` is stored in a
`double`-sized slot.


### `mulle_vararg_push_struct`

`mulle_vararg_push_struct( ap, value)`

Push a struct **value** (copied by value) into the buffer.


### `mulle_vararg_push_union`

`mulle_vararg_push_union( ap, value)`

Push a union **value** (copied by value) into the buffer.


### `mulle_vararg_push_pointer`

`mulle_vararg_push_pointer( ap, value)`

Push a pointer **value** into the buffer.


### `mulle_vararg_push_functionpointer`

`mulle_vararg_push_functionpointer( ap, value)`

Push a function pointer **value** into the buffer.


### Convenience push macros

| Macro | Equivalent to |
|---|---|
| `mulle_vararg_push_char( ap, value)` | `mulle_vararg_push_integer( ap, char, value)` |
| `mulle_vararg_push_short( ap, value)` | `mulle_vararg_push_integer( ap, short, value)` |
| `mulle_vararg_push_int( ap, value)` | `mulle_vararg_push_integer( ap, int, value)` |
| `mulle_vararg_push_int32( ap, value)` | `mulle_vararg_push_integer( ap, int32_t, value)` |
| `mulle_vararg_push_int64( ap, value)` | `mulle_vararg_push_integer( ap, int64_t, value)` |
| `mulle_vararg_push_long( ap, value)` | `mulle_vararg_push_integer( ap, long, value)` |
| `mulle_vararg_push_longlong( ap, value)` | `mulle_vararg_push_integer( ap, long long, value)` |
| `mulle_vararg_push_unsignedchar( ap, value)` … `mulle_vararg_push_unsignedlonglong( ap, value)` | the corresponding `mulle_vararg_push_integer( ap, …, value)` |
| `mulle_vararg_push_uint32( ap, value)`, `mulle_vararg_push_uint64( ap, value)` | the corresponding `mulle_vararg_push_integer( ap, …, value)` |
| `mulle_vararg_push_float( ap, value)` | `mulle_vararg_push_fp( ap, float, value)` |
| `mulle_vararg_push_double( ap, value)` | `mulle_vararg_push_fp( ap, double, value)` |
| `mulle_vararg_push_longdouble( ap, value)` | `mulle_vararg_push_fp( ap, long double, value)` |


### `mulle_vararg_builder_do`

`mulle_vararg_builder_do( name, size)`

Convenience for allocating the buffer on the stack and declaring the
`mulle_vararg_list` **name** in one step:

``` c
mulle_vararg_builder_do( varargs, mulle_vararg_sizeof_integer( int) +
                                 mulle_vararg_sizeof_integer( long));
```

> This macro expands to `mulle_alloca_do` from
> [mulle-allocator](https://github.com/mulle-c/mulle-allocator). You must
> link against `mulle-allocator` to use it (the header includes it
> automatically; inside the mulle-core amalgamation this is already the
> case).


### Buffer size rules

- The buffer must be large enough to hold **all** pushed arguments at their
  promoted slot sizes and alignments. Use the `mulle_vararg_sizeof_*` /
  `mulle_vararg_alignof_*` macros to compute the total size.
- Round up the byte size with `mulle_vararg_builderbuffer_n()`.
- Sizing too small is undefined behavior — there is no bounds checking.
