#include <mulle-vararg/mulle-vararg.h>
#include <mulle-vararg/mulle-vararg.h>

#include <stdio.h>
#include <string.h>

//
// varargs are always promoted to int/double if smaller !
// struct { struct { char c, char d } x}, not though... ?
//
struct reference
{
   int          c;
   double       d;
   int          e;
   long double  f;
};


int   main( void)
{
   mulle_vararg_builderbuffer_t  buf[ mulle_vararg_builderbuffer_n( sizeof( struct reference))];
   mulle_vararg_list             list;
   mulle_vararg_list             q;
   struct reference              ref;

   list = mulle_vararg_make_builderbuffer( buf);

   memset( buf, 0, sizeof( buf));
   memset( &ref, 0, sizeof( ref));

   ref.c = 18;
   ref.d = 48.0;
   ref.e = 1848;
   ref.f = 18.48e10;

   mulle_vararg_copy( q, list);
   mulle_vararg_push_int( q, ref.c);
   mulle_vararg_push_double( q, ref.d);
   mulle_vararg_push_int( q, ref.e);
   mulle_vararg_push_longdouble( q, ref.f);

   if( memcmp( &ref, list.p, sizeof( struct reference)))
   {
      fprintf( stderr, "reference layout differs\n");
      return( 1);
   }

   printf( "%d\n",   mulle_vararg_next_int( list));
   printf( "%.2f\n", mulle_vararg_next_double( list));
   printf( "%d\n",   mulle_vararg_next_int( list));
   printf( "%.2f\n", (double) mulle_vararg_next_longdouble( list));

   return( 0);
}
