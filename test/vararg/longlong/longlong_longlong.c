#include <mulle-vararg/mulle-vararg.h>
#include <stdio.h>


struct
{
   long long   a;
   long long   b;
} value =
{
   -1848,
   1848
};


int   main( void)
{
   mulle_vararg_list   list;

   mulle_vararg_start( list, value.a);

   printf( "%lld\n", mulle_vararg_next_integer( list, long long));

   mulle_vararg_end( list);
   return( 0);
}
