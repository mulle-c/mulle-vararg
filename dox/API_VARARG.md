# mulle-vararg API

Familiarize yourself with [stdarg](//wikipedia.org/wiki/Stdarg.h) first,
because **mulle-vararg** is very similar. The main difference is, that
in stdarg you specify the type as a parameter to `va_arg`, whereas in
**mulle-vararg** you need to call different macros depending on type.

> Attention: a `mulle_vararg_list` is **not** compatible with a `va_list`
> and vice versa. Do not mix the two.

## How to use it

Link against `mulle_vararg` and
`#include <mulle-vararg/mulle-vararg.h>` in your code.

Here is an example. A structure is defined with two fields, **a** and **b**.
`_mulle_vararg_start` is initialized with the lvalue **a**. It will now
use the first value *AFTER* **a** as the first variable argument.

> `_mulle_vararg_start( args, ap)` takes the **lvalue** `ap` (a struct field
> or local variable), not its address — the macro forms `&ap` internally.

So this code will effectively output `18`.

``` c
#include <mulle-vararg/mulle-vararg.h>
#include <stdio.h>


struct
{
   void  *a;
   char  b;
} value =
{
   (void *) -1848,
   18
};


int   main( void)
{
   mulle_vararg_list   list;

   _mulle_vararg_start( list, value.a);

   printf( "%d\n", mulle_vararg_next_integer( list, char));

   mulle_vararg_end( list);
   return( 0);
}
```

Note: `char b` occupies an `int`-sized slot in the vararg layout, because
`char` is promoted to `int` when passed as a variable argument. The
`mulle_vararg_next_integer( list, char)` read therefore returns `18`.

## Types

Type                | Description
--------------------|------------------------------------------------
`mulle_vararg_list` | The variable argument storage.



## Macros


### `mulle_vararg_start`

`mulle_vararg_start( args, ap)`

Start the variable argument access inside a variadic function.

**args** is a `mulle_vararg_list` variable. **ap** is the last named
parameter of the function.

> ⚠️ `mulle_vararg_start` is tied to the **metaABI** of the mulle-clang
> compiler: it expands to `_mulle_vararg_start( args, _param->ap)`. It only
> compiles when the compiler injects a `_param` struct pointer (mulle-objc
> runtime) and the last named parameter is **literally named** `ap`.
>
> For portable code (plain gcc/clang, or any variable name) use
> [`_mulle_vararg_start`](#_mulle_vararg_start) with the address of the last
> named argument instead.

### `mulle_vararg_start_fp`

`mulle_vararg_start_fp( args, ap)`

Like `mulle_vararg_start`, but for variadic functions whose first variable
argument is floating point (respects the `float` → `double` promotion slot
size). Same metaABI restriction as `mulle_vararg_start`.

### `_mulle_vararg_start`

`_mulle_vararg_start( args, ap)`

Start the variable argument access at the first value *after* the lvalue
**ap**. **ap** is any lvalue (a struct field or a local variable); the list
starts at the first byte after `sizeof( ap)` (with `int`-sized minimum, per
C promotion rules).

This is the portable entry point and the one used by all examples and tests.

### `_mulle_vararg_start_fp`

`_mulle_vararg_start_fp( args, ap)`

Like `_mulle_vararg_start`, but for floating-point first arguments
(`double`-sized minimum slot).


### `mulle_vararg_end`

`mulle_vararg_end( args)`

Marks the end of the use of **args** `mulle_vararg_list` variable.
Currently a no-op, but call it for forward compatibility.


### `mulle_vararg_copy`

`mulle_vararg_copy( dst, src)`

Copy `mulle_vararg_list` **src** to **dst**. Use this if you want to iterate
a second time over a `mulle_vararg_list` argument.


### `mulle_vararg_next_integer`

`mulle_vararg_next_integer( args, type)`

Use it for all integer types, like char, short, int, long, long long and their
unsigned variants. Small types are read from an `int`-sized slot (C
promotion) and converted to **type**.

Example:

``` c
mulle_vararg_next_integer( args, unsigned short);
```


### `mulle_vararg_next_fp`

`mulle_vararg_next_fp( args, type)`

Use it for all floating point types, like float, double, long double. `float`
is read from a `double`-sized slot (C promotion).

Example:

``` c
mulle_vararg_next_fp( args, float);
```


### `mulle_vararg_next_pointer`

`mulle_vararg_next_pointer( args, type)`

Use it for all pointer types.

Example:

``` c
mulle_vararg_next_pointer( args, int *);
```


### `mulle_vararg_next_struct`

`mulle_vararg_next_struct( args, type)`

Get the next struct value. Use it for all struct types. The struct is copied
by value out of the varargs.

Example:

``` c
struct x_t
{
   int a;
   int b;
} x;

x = mulle_vararg_next_struct( args, struct x_t);
```


### `_mulle_vararg_next_struct`

`_mulle_vararg_next_struct( args, type)`

Get the address of the next struct.
Use it for all struct types. The struct will not be copied, but
instead you get a reference into the varargs. This is obviously more
risky!

Example:

``` c
struct x_t
{
   int a;
   int b;
} *x;   // pointer

x = _mulle_vararg_next_struct( args, struct x_t);
```


### `mulle_vararg_next_union`

`mulle_vararg_next_union( args, type)`

Get the next union value. Use it for all union types. The union is copied by
value out of the varargs.

Example:

``` c
union x_t
{
   int a;
   int b;
} x;

x = mulle_vararg_next_union( args, union x_t);
```

### `_mulle_vararg_next_union` - get address of next union

`_mulle_vararg_next_union( args, type)`

Use it for all union types. The union will not be copied, but
instead you get a reference into the varargs. This is obviously more
risky!

Example:

``` c
union x_t
{
   int a;
   int b;
} *x;   // pointer

x = _mulle_vararg_next_union( args, union x_t);
```


### Convenience read macros

The following convenience macros delegate to the generic ones above:

| Macro | Equivalent to |
|---|---|
| `mulle_vararg_next_char( ap)` | `mulle_vararg_next_integer( ap, char)` |
| `mulle_vararg_next_short( ap)` | `mulle_vararg_next_integer( ap, short)` |
| `mulle_vararg_next_int( ap)` | `mulle_vararg_next_integer( ap, int)` |
| `mulle_vararg_next_int32( ap)` | `mulle_vararg_next_integer( ap, int32_t)` |
| `mulle_vararg_next_int64( ap)` | `mulle_vararg_next_integer( ap, int64_t)` |
| `mulle_vararg_next_long( ap)` | `mulle_vararg_next_integer( ap, long)` |
| `mulle_vararg_next_longlong( ap)` | `mulle_vararg_next_integer( ap, long long)` |
| `mulle_vararg_next_unsignedchar( ap)` … `mulle_vararg_next_unsignedlonglong( ap)` | the corresponding `mulle_vararg_next_integer( ap, …)` |
| `mulle_vararg_next_uint32( ap)`, `mulle_vararg_next_uint64( ap)` | the corresponding `mulle_vararg_next_integer( ap, …)` |
| `mulle_vararg_next_float( ap)` | `mulle_vararg_next_fp( ap, float)` |
| `mulle_vararg_next_double( ap)` | `mulle_vararg_next_fp( ap, double)` |
| `mulle_vararg_next_longdouble( ap)` | `mulle_vararg_next_fp( ap, long double)` |


## Functions


### `mulle_address_align`

`uintptr_t   mulle_address_align( uintptr_t p, unsigned int alignment)`

Pass in an address **p** and an alignment **alignment**. `mulle_address_align`
will return the aligned address.

e.g. `mulle_address_align( 0x11, 0x10)` will return `0x20`


### `mulle_pointer_align`

`void   *mulle_pointer_align( void *p, unsigned int alignment)`

Pass in a pointer **p** and an alignment **alignment**. `mulle_pointer_align`
will return the aligned pointer.


### `mulle_vararg_count_pointers` - count null terminated vararg pointers

`size_t   mulle_vararg_count_pointers( mulle_vararg_list args, void *first)`

The interface is a bit weird but practical. You give it a variable argument
list and the first pointer of that list of pointers. The function assumes that
all subsequent variable arguments are also of pointer type. It will then
compute the number of non-NULL pointers including `first`.

Example:

``` c
#include <mulle-vararg/mulle-vararg.h>
#include <stdio.h>


struct pointer_32_t
{
   void  *pointers[ 32];
};


static size_t   count( struct pointer_32_t *array)
{
   mulle_vararg_list   list;
   size_t              n;

   _mulle_vararg_start( list, array->pointers[ 0]);

   n = mulle_vararg_count_pointers( list, array->pointers[ 0]);

   mulle_vararg_end( list);
   return( n);
}


int main()
{
   struct pointer_32_t   array = { (void *) 0x1848, (void *) 0x1849, NULL };

   printf( "%ld\n", (long) count( &array));  // will print 2
}
```
