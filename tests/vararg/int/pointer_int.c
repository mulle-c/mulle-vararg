#include <mulle_vararg/mulle_vararg.h>
#include <stdio.h>

struct
{
   void  *a;
   int    b;
} value =
{
   -1848,
   1848
};


int   main( void)
{
   mulle_vararg_list   list;

   mulle_vararg_start( list, value.a);

   printf( "%d\n", mulle_vararg_next_integer( list, int));

   mulle_vararg_end( list);
   return( 0);
}
