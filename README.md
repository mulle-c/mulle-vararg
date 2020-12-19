# mulle-vararg

####  ⏪ Access variable arguments in struct layout fashion in C

A variable argument passing scheme written in C (C11). It's an alternative
to
[stdarg](//en.wikipedia.org/wiki/Stdarg.h) or
[varargs](//pubs.opengroup.org/onlinepubs/7908799/xsh/varargs.h.html),
but not compatible with either.


| Release Version
|-----------------------------------
| ![Mulle kybernetiK tag](https://img.shields.io/github/tag/mulle-c/mulle-vararg.svg?branch=release) [![Build Status](https://github.com/mulle-c/mulle-vararg/workflows/CI/badge.svg?branch=release)](https://github.com/mulle-c/mulle-vararg/actions)


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
some experimental code to write to it.



#### Advantages

* Easy to write in C, does not need compiler ABI internals to construct or
read. You don't need [libffi](//sourceware.org/libffi/) or some such.
* Cheap forwarding to other functions.


#### Disadvantages

* Not compatible with `<stdarg.h>`



## API

There is an API to access mulle-vararg arguments. You can also build up
a mulle-vararg manually with the builder functions.

* [Vararg](dox/API_VARARG.md)
* [VarargBuilder](dox/API_VARARG_BUILDER.md)

### Platforms and Compilers

All platforms and compilers supported by
[mulle-c11](//github.com/mulle-c/mulle-c11)


## Add

### Either: link library

Use [mulle-sde](//github.com/mulle-sde) to add mulle-buffer to your project:

```
mulle-sde dependency add --c --github mulle-c mulle-buffer
```

### Or: add Sources

Alternatively you can read [STEAL.md](//github.com/mulle-c11/dox/STEAL.md) on
how to add mulle-c source code into your own projects.

## Install

### mulle-sde

Use [mulle-sde](//github.com/mulle-sde) to build and install mulle-vararg and all dependencies:

```
mulle-sde install --prefix /usr/local \
   https://github.com/mulle-c/mulle-vararg/archive/latest.tar.gz
```

### Manual Installation


Install the requirements:

Requirements                                 | Description
---------------------------------------------|-----------------------
[mulle-c11](//github.com/mulle-c/mulle-c11)  | Compiler glue


Install into `/usr/local`:

```
mkdir build 2> /dev/null
(
   cd build ;
   cmake -DCMAKE_INSTALL_PREFIX=/usr/local \
         -DCMAKE_PREFIX_PATH=/usr/local \
         -DCMAKE_BUILD_TYPE=Release .. ;
   make install
)
```


## Author

[Nat!](//www.mulle-kybernetik.com/weblog) for
[Mulle kybernetiK](//www.mulle-kybernetik.com) and
[Codeon GmbH](//www.codeon.de)

