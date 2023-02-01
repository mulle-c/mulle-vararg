# mulle-vararg API

Familiarize yourself with [stdarg](//wikipedia.org/wiki/Stdarg.h) first,
because **mulle-vararg** is very similiar. The main difference is, that
in stdarg you specify the type as a parameter to `va_next`, whereas in
**mulle-vararg** you need to call different macros depending on type.

> Attention: **mulle-valist** is not compatible with **valist**


## How to use it

Link against `mulle_vararg` and
`#include <mulle-vararg/mulle-vararg.h>` in your code.

Here is an example. A structure is defined with two fields, **a** and **b**.
`mulle_vararg_start` is initialized with **a**. It will now use the
first value *AFTER* **a** as the first variable argument.

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
   -1848,
   18
};


int   main( void)
{
   mulle_vararg_list   list;

   mulle_vararg_start( list, value.a);

   printf( "%d\n", mulle_vararg_next_integer( list, char));

   mulle_vararg_end( list);
   return( 0);
}
```

## Types

Type                | Description
--------------------|------------------------------------------------
`mulle_vararg_list` | The variable argument storage.



## Macros


### `mulle_vararg_copy`

`mulle_vararg_copy( dst, src)`

Copy `mulle_vararg_list` **src** to **dst**. Use this if you want to iterate
a second time over a `mulle_vararg_list` argument.


### `mulle_vararg_end`

`mulle_vararg_end( args)`

Marks the end of the use of **args** `mulle_vararg_list` variable.


### `mulle_vararg_next_fp`

`mulle_vararg_next_fp( args, type)`

Use it for all floating point types, like float, double, long double.


Example:

``` c
mulle_vararg_next_fp( args, float);
```


### `mulle_vararg_next_integer`

`mulle_vararg_next_integer( args, type)`

Use it for all integer types, like char, short, int, long, long long and their
unsigned variants.

Example:

``` c
mulle_vararg_next_integer( args, unsigned short);
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

Get the next struct value. Use it for all struct types.

Example:

```
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

x = mulle_vararg_next_struct( args, struct x_t);
```


### `mulle_vararg_next_union`

`mulle_vararg_next_union( args, type)`

Get the next union value. Use it for all union types.

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

x = mulle_vararg_next_union( args, struct x_t);
```



### `mulle_vararg_start`

`mulle_vararg_start( args, ap)`

Start the variable argument access.
**args** is a `mulle_vararg_list` variable. **ap** is the last non-variable
argument.


## Functions


### `mulle_address_align`

`uintptr_t   mulle_address_align( uintptr_t p, unsigned int alignment)`

Pass in an address **p** and an alignment **alignment**. `mulle_address_align`
will return the aligned address.

e.g. `mulle_address_align( 0x11, 0x10)` will return `0x20`


### `mulle_pointer_align`

`void   *mulle_pointer_align( void *p, unsigned int alignment)`

Pass in a pointer **p** and an alignment **alignment**. `mulle_align_pointer`
will return the aligned pointer.


### `mulle_vararg_count_pointers` - count null terminated vararg pointers

`size_t   mulle_vararg_count_pointers( mulle_vararg_list args, void *p)`

The interface is a bit weird but practical. You give it a variable argument
list and the first pointer of that list of pointers. The function assumes that
all subsequent variable arguments are also of pointer type. It will then
compute the number of non-NULL pointers including `*p`.

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

   mulle_vararg_start( list, array->pointers[ 0]);

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



