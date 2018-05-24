#include <mulle-vararg/mulle-vararg.h>
#include <stdio.h>


struct
{
   double   a;
   char   b;
} value =
{
   -1848,
   18
};


int   main( voids)
{
   mulle_vararg_list   list;

   mulle_vararg_start( list, value.a);

   printf( "%d\n", mulle_vararg_next_integer( list, char));

   mulle_vararg_end( list);
   return( 0);
}
