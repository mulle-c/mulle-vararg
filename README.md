# mulle-vararg

A variable argument passing scheme written in C (C11).


## How it works

**mulle-vararg** assumes that the arguments are not layed out in stack
alignment fashion but like in a struct. The C promotion rules are still
observed though.

> Remember the C argument promotion rules are
>
> 1. char and short to int/unsigned int
> 2. float to double
>

Let's assume there is a compiler that does not use `<stdarg.h>` variable
arguments but **mulle-vararg** instead. It collects all arguments and packs
them into a struct, then passes this struct to the function.

A **printf** function being being called like this:

```
printf( "%d %f %lld\n", (char) 'x', (float) 0.2, 1848LL;
```

would access the arguments, as if they were embedded in a struct like this

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


## API

* [Vararg](dox/API_VARARG.md)


### Platforms and Compilers

All platforms and compilers supported by
[mulle-c11](//www.mulle-kybernetik.com/software/git/mulle-c11/)

