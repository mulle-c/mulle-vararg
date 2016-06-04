//
//  mulle_vararg.h
//  mulle-objc-runtime
//
//  Created by Nat! on 29.10.15.
//  Copyright © 2015 Mulle kybernetiK. All rights reserved.
//

#ifndef mulle_vararg_h__
#define mulle_vararg_h__

#include "mulle_align.h"

#define MULLE_VARARG_VERSION  ((0 << 20) | (3 << 8) | 0)


/*
 * -print:(NSString *) format, ...
 * [print:@"%d",  0.1]
 *
 * 32 bit:
 * struct vararg
 * {
 *    NSString *X;    // assume .align 2
 *    double    Y;    // assume .align 8
 * }
 *
 * 00: XXXXXXXX
 * 04: 00000000
 * 08: YYYYYYYY
 * 0A: YYYYYYYY
 *
 * -addIfTrue:(BOOL) flag a:(float) a, ...
 * [addIfTrue:YES a:0.2, 0.3]
 *
 * 32 bit:
 * struct vararg
 * {
 *    BOOL      X;
 *    float     Y;    // assume .align 4
 *    double    Z;    // assume .align 8
 * }
 *
 * 00: XX000000
 * 04: YYYYYYYY
 * 08: ZZZZZZZZ
 * 0A: ZZZZZZZZ
 */
typedef struct
{
   void   *p;
}  mulle_vararg_list;



#define mulle_vararg_start( args, ap)          \
do                                             \
{                                              \
   args.p = &ap;                               \
   args.p = &((char *) args.p)[ sizeof( ap) < sizeof( int) ? sizeof( int) : sizeof( ap)];  \
}                                              \
while( 0)




// use this for integer types

static inline char  *_mulle_vararg_int_aligned_pointer( mulle_vararg_list *args, size_t size, unsigned int align)
{
   char   *q;
   
   if( size < sizeof( int))
   {
      align = sizeof( int);
      size  = sizeof( int);
   }
   
   q       = mulle_align_pointer( args->p, align);
   args->p = &q[ size];
   return( q);
}
   

#define mulle_vararg_next_integer( args, type)                                                   \
   (sizeof( type) < sizeof( int)                                                                 \
      ? (type) *(int *) _mulle_vararg_int_aligned_pointer( &args, sizeof( type), alignof( type)) \
      : *(type *) _mulle_vararg_int_aligned_pointer( &args, sizeof( type), alignof( type)))


static inline char  *_mulle_vararg_aligned_pointer( mulle_vararg_list *args, unsigned int align)
{
   char   *q;
   
   q       = mulle_align_pointer( args->p, align);
   args->p = &q[ sizeof( void *)];
   return( q);
}


// use this for all pointer and id types
#define mulle_vararg_next_pointer( args, type)  \
   (*(type *) _mulle_vararg_aligned_pointer( &args, alignof( type)))

// use this for objects types
#define mulle_vararg_next( args)                \
   mulle_vararg_next_pointer( args, id)

// synonym
#define mulle_vararg_next_object( args, type)    \
   mulle_vararg_next_pointer( args, type)


// use this for all struct types
#define mulle_vararg_next_struct( args, type)    \
   (*(type *) _mulle_vararg_aligned_pointer( &args, alignof( type)))


static inline char  *_mulle_vararg_double_aligned_pointer( mulle_vararg_list *args, size_t size, unsigned int align)
{
   char   *q;
   
   if( size < sizeof( double))
   {
      align = sizeof( double);
      size  = sizeof( double);
   }
   
   q       = mulle_align_pointer( args->p, align);
   args->p = &q[ size];
   return( q);
}


// need separate routine for FP arguments, as float promotes to double
#define mulle_vararg_next_fp( args, type)                                                              \
   (sizeof( type) < sizeof( double)                                                                    \
      ? (type) *(double *) _mulle_vararg_double_aligned_pointer( &args, sizeof( type), alignof( type)) \
      : *(type *) _mulle_vararg_double_aligned_pointer( &args, sizeof( type), alignof( type)))




#define mulle_vararg_copy( dst, src)         \
do                                           \
{                                            \
   dst = src;                                \
}                                            \
while( 0)

#define mulle_vararg_end( args)


// only works for objects and pointers

static inline size_t    mulle_vararg_count( mulle_vararg_list args, void *object)
{
   size_t   count;
   void     *p;

   count = 0;
   p     = object;
   while( p)
   {
      ++count;
      p = mulle_vararg_next_pointer( args, void *);
   }
   
   return( count);
}
   
#endif /* mulle_vararg_h */
