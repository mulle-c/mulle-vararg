
#ifndef mulle_vararg_h__
#define mulle_vararg_h__

#include "mulle-align.h"


// sketched out idea for a vararg builder
// returns the address to push next argument unto.
// it's the callers responsiblity to
// * remember the start of the vararg buffer
// * ensure that the buffer is large enough (tricky!)
// * use the returne value as the first argument next time
//
// Intended use:
//
// mulle_vararg_builderbuffer_t  buf[ mulle_vararg_builderbuffer_n( sizeof( int) + sizeof( long)]
// mulle_vararg_list             p = mulle_vararg_builderbuffer_get_list( buf);
// mulle_vararg_list             q;
//
// q = mulle_vararg_push_integer( p, 18);
// q = mulle_vararg_push_integer( q, 48L);
// mulle_mvsprintf( buffer, "%d %ld", p);

// use double for alignment
typedef double   mulle_vararg_builderbuffer_t;
typedef void     *mulle_vararg_builder_t;

#define mulle_vararg_builderbuffer_n( size_t n)  \
   (((n) + sizeof( mulle_vararg_builderbuffer_t) - 1)/ sizeof( mulle_vararg_builderbuffer_t))


static inline void   mulle_vararg_push_longdouble( mulle_vararg_list *ap, long double value)
{
   long double   *q;

   q     = mulle_pointer_align( ap->p, alignof( long double));
   *q++  = value;
   ap->p = q;
}


static inline void   mulle_vararg_push_double( mulle_vararg_list *ap, double value)
{
   double   *q;

   q     = mulle_pointer_align( ap->p, alignof( double));
   *q++  = value;
   ap->p = q;
}


static inline void   mulle_vararg_push_longlong( mulle_vararg_list *ap, long long value)
{
   long long   *q;

   q    = mulle_pointer_align( p, alignof( long long));
   *q++ = value;
   ap->p = q;
}


static inline void   mulle_vararg_push_int( mulle_vararg_list *ap, int value)
{
   int   *q;

   q    = mulle_pointer_align( p, alignof( int));
   *q++ = value;
   ap->p = q;
}


static inline void   mulle_vararg_push_long( mulle_vararg_list *ap, long value)
{
   long   *q;

   q    = mulle_pointer_align( p, alignof( long));
   *q++ = value;
   ap->p = q;
}


static inline void   mulle_vararg_push_pointer( mulle_vararg_list *ap, void *value)
{
   void   **q;

   q    = mulle_pointer_align( p, alignof( void *));
   *q++ = value;
   ap->p = q;
}


typedef void  (*mulle_vararg_void_functionpointer)( void);

static inline void *
   mulle_vararg_push_functionpointer( void *ap,
                                      mulle_vararg_void_functionpointer value)
{
   mulle_vararg_void_functionpointer   *q;

   q    = mulle_pointer_align( p, alignof( mulle_vararg_void_functionpointer));
   *q++ = value;
   ap->p = q;
}


#define mulle_vararg_push_integer( p , x)                      \
   (                                                           \
      sizeof( x) <= sizeof( int)                               \
         ? mulle_vararg_push_int( p, (int) x)                  \
         : (sizeof( x) <= sizeof( long))                       \
            ? mulle_vararg_push_long( p, (long) x)             \
            : mulle_vararg_push_longlong( p, (long long) x)    \
   )

#define mulle_vararg_push_fp( p , x)                           \
   (                                                           \
      sizeof( x) <= sizeof( double)                            \
         ? mulle_vararg_push_double( p, (double) x)            \
         : mulle_vararg_push_longdouble( p, (long double) x)   \
   )


#define mulle_vararg_push_struct( ap , x)                                     \
   (                                                                          \
      memcpy( mulle_pointer_align( ap->p, alignof( x)), &x, sizeof( x)),      \
      ap->p = &((char *) mulle_pointer_align( p, alignof( x)))[ sizeof( x)]   \
   )

#define mulle_vararg_push_union( ap , x)    mulle_vararg_push_struct( p, x)

#endif

