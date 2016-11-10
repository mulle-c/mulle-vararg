# mulle-vararg

A variable argument passing scheme written in C (C11). It's an alternative
to [stdarg](//en.wikipedia.org/wiki/Stdarg.h) or [varargs](//pubs.opengroup.org/onlinepubs/7908799/xsh/varargs.h.html), but not compatible with either.

Fork         | Branch  | Version | Build Status 
-------------|-------- |---------|----------------
[Mulle kybernetiK](//github.com/mulle-nat/mulle-vararg)  | release | ![GitHub version](https://badge.fury.io/gh/mulle-nat%2Fmulle-vararg.svg) | [![Build Status](https://travis-ci.org/mulle-nat/mulle-vararg.svg?branch=release)](https://travis-ci.org/mulle-nat/mulle-vararg)
[Community](https://github.com/mulle-objc/mulle-vararg/tree/release)      | release | ![GitHub version](https://badge.fury.io/gh/mulle-objc%2Fmulle-vararg.svg) |  [![Build Status](https://travis-ci.org/mulle-objc/mulle-vararg.svg?branch=release)](https://travis-ci.org/mulle-objc/mulle-vararg)
[Community](//github.com/mulle-objc/mulle-vararg)    | master | current |  [![Build Status](https://travis-ci.org/mulle-objc/mulle-vararg.svg?branch=master)](https://travis-ci.org/mulle-objc/mulle-vararg)


#### Advantages

* Easy to write in C, does not need compiler ABI internals to construct or
read. You don't need [libffi](//sourceware.org/libffi/) or some such.
* Cheap forwarding to other functions.


#### Disadvantages

* Not compatible with `<stdarg.h>`


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


## API

* [API](dox/API_VARARG.md)


## Install

On OS X and Linux you can use [homebrew](//brew.sh), respectively
[linuxbrew](//linuxbrew.sh) to install the library:

```
brew tap mulle-kybernetik/software
brew install mulle-vararg
```

On other platforms you can use **mulle-install** from
[mulle-build](//www.mulle-kybernetik.com/software/git/mulle-build) to install the library:

```
mulle-install --prefix /usr/local --branch release https://www.mulle-kybernetik.com/repositories/mulle-vararg
```

Otherwise read:

* [How to Build](dox/BUILD.md)


### Platforms and Compilers

All platforms and compilers supported by
[mulle-c11](//www.mulle-kybernetik.com/software/git/mulle-c11/)

## Author

[Nat!](//www.mulle-kybernetik.com/weblog) for
[Mulle kybernetiK](//www.mulle-kybernetik.com) and
[Codeon GmbH](//www.codeon.de)

