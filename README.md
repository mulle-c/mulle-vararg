# mulle-vararg

⏪ Access variable arguments in struct layout fashion in C

A variable argument passing scheme written in C (C11). It's an alternative
to
[stdarg](//en.wikipedia.org/wiki/Stdarg.h) or
[varargs](//pubs.opengroup.org/onlinepubs/7908799/xsh/varargs.h.html),
but not compatible with either.


Build Status | Release Version
-------------|-----------------------------------
[![Build Status](https://travis-ci.org/mulle-nat/mulle-vararg.svg?branch=release)](https://travis-ci.org/mulle-nat/mulle-vararg) | ![Mulle kybernetiK tag](https://img.shields.io/github/tag/mulle-nat/mulle-vararg.svg) [![Build Status](https://travis-ci.org/mulle-nat/mulle-vararg.svg?branch=release)](https://travis-ci.org/mulle-nat/mulle-vararg)

## Install

Install the prerequisites first:

| Prerequisites                                           |
|---------------------------------------------------------|
| [mulle-c11](//github.com/mulle-c/mulle-c11)             |


Then build and install

```
mkdir build 2> /dev/null
(
   cd build ;
   cmake .. ;
   make install
)
```

Or let [mulle-sde](//github.com/mulle-sde) do it all for you.


## How it works

**mulle-vararg** assumes that the arguments are not layed out in stack
alignment fashion but like in a struct. The C promotion rules are still
observed though.

> Remember the C argument promotion rules are
>
> 1. char and short to int/unsigned int
> 2. float to double
>

Let's assume there is a compiler that uses **mulle-vararg** for variable
arguments. It collects **all** function parameters and packs them into a struct,
then passes this struct to the function.

A **printf** function being being called like this:

```
printf( "%d %f %lld\n", (char) 'x', (float) 0.2, 1848LL;
```

would get its arguments embedded in a struct like this

```
struct
{
   char    *format;
   struct
   {
      int         value1;     // standard char -> int promotion
      double      value2;     // standard float -> double promotion
      long long   value3;
   } varargs;
} _param;
```

**mulle-vararg** provides the necessary functions to read such a struct. It has
no code to create it.


#### Advantages

* Easy to write in C, does not need compiler ABI internals to construct or
read. You don't need [libffi](//sourceware.org/libffi/) or some such.
* Cheap forwarding to other functions.


#### Disadvantages

* Not compatible with `<stdarg.h>`



## API

* [Vararg](dox/API_VARARG.md)

### Platforms and Compilers

All platforms and compilers supported by
[mulle-c11](//github.com/mulle-c/mulle-c11)

## Author

[Nat!](//www.mulle-kybernetik.com/weblog) for
[Mulle kybernetiK](//www.mulle-kybernetik.com) and
[Codeon GmbH](//www.codeon.de)

