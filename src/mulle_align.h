//
//  mulle_align.h
//  mulle-objc-runtime
//
//  Created by Nat! on 07.04.16.
//  Copyright © 2016 Mulle kybernetiK. All rights reserved.
//

#ifndef mulle_align_h__
#define mulle_align_h__

#include <stdint.h>
#include <stddef.h>

// ugliness creeps in due to windows
#ifdef _WIN32
# define alignof( x)  __alignof( x)
#else
# include <stdalign.h>
#endif

#if ! defined( __clang__) && ! defined( __GNUC__)
# ifndef MULLE_CONST_VALUE_RETURN
#  define MULLE_CONST_VALUE_RETURN   __attribute__(( const))
# endif
#else
# ifndef MULLE_CONST_VALUE_RETURN
#  define MULLE_CONST_VALUE_RETURN
# endif
#endif


MULLE_CONST_VALUE_RETURN
static inline uintptr_t   mulle_align( uintptr_t p, unsigned int alignment)
{
   intptr_t   misalignment;
   
   if( alignment)
   {
      misalignment = p % alignment;
      if( misalignment)
         p += alignment - misalignment;
   }
   return( p);
}


MULLE_CONST_VALUE_RETURN
static inline void   *mulle_align_pointer( void *p, unsigned int alignment)
{
   return( (void *) mulle_align( (uintptr_t) p, alignment));
}


#endif /* mulle_align_h */
