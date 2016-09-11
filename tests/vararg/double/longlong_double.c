#include <mulle_vararg/mulle_vararg.h>
#include <stdio.h>


struct
{
   long long   a;
   double      b;
} value =
{
   -1848,
   18.48
};


int   main( void)
{
   mulle_vararg_list   list;

   mulle_vararg_start( list, value.a);

   printf( "%.2f\n", mulle_vararg_next_fp( list, double));

   mulle_vararg_end( list);
   return( 0);
}