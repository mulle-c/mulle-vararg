# mulle-vararg-builder API


## How to use it

Link against `mulle_vararg` and
`#include <mulle-vararg/mulle-vararg.h>` in your code.

Here is an example. You want to pass an int and a float to a variable
argument functions such as `mulle_sprintf`.

The critical part here is the proper estimation of the required size of
the buffer to hold the arguments.


```
#include <mulle-vararg/mulle-vararg.h>
#include <mulle-buffer/mulle-buffer.h>
#include <mulle-sprintf/mulle-sprintf.h>

#include <stdio.h>


int   main( void)
{
   mulle_vararg_builderbuffer_t  buf[ mulle_vararg_builderbuffer_n( sizeof( struct{ int a; long b;}))];
   mulle_vararg_list             list;
   mulle_vararg_list             q;
   struct mulle_buffer           buffer;

   //
   // build up variable argument list
   //
   list = mulle_vararg_make_builderbuffer( buf);

   mulle_vararg_copy( q, list);
   mulle_vararg_push_int( q, 18);
   mulle_vararg_push_long( q, 48L);

   //
   // pass to mulle_mvsprintf which will print into buffer
   //
   mulle_buffer_init( &buffer, NULL);
   mulle_mvsprintf( &buffer, "%d %ld", list);

   //
   // get produced character string and printf
   //
   mulle_buffer_add_byte( &buffer, 0);
   printf( "%s\n", mulle_buffer_get_bytes( &buffer));
   mulle_buffer_done( &buffer);

   return( 0);
}
```

## Types

Type                | Description
--------------------|------------------------------------------------
`mulle_vararg_list` | The variable argument storage.



## Macros


### `mulle_vararg_push_int`

`mulle_vararg_push_int( va, value)`

Push an `int` value.


### MORE....



