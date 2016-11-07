# How to build mulle-vararg


## What you get

* `libmulle_vararg.a` the mulle-vararg static library along with a bunch of
headers.


## Prerequisites

#### mulle-c11

[mulle-c11](//www.mulle-kybernetik.com/software/git/mulle-c11/) is a header
that abstracts a small set of non-standardized compiler features.

#### mulle-configuration

[mulle-configuration](//www.mulle-kybernetik.com/software/git/mulle-configuration/)
are configuration files for building with Xcode or cmake. This is expected to
exist in the project directory root.


## Nice to have

#### mulle-build

[mulle-build](//www.mulle-kybernetik.com/software/git/mulle-build) is used
to assemble the dependencies together and build the library.

#### mulle-homebrew

[mulle-homebrew](//www.mulle-kybernetik.com/software/git/mulle-homebrew/) is
support for generating homebrew formulae. This is expected to
exist in `./bin`, if you want to release a fork.

#### mulle-tests

[mulle-tests](//www.mulle-kybernetik.com/software/git/mulle-tests/) are
scripts to provide an environment for running the tests. This is expected to
exist in `./tests`, if you want to run tests.


### Windows: Installing further prerequisites

Check the [mulle-build README.md](//www.mulle-kybernetik.com/software/git/mulle-build/README.md)
for instrutions how to get the "Git for Windows" bash going.


### OSX: Install mulle-build using homebrew

Install the [homebrew](//brew.sh/) package manager, then

```
brew tap mulle-kybernetik/software
brew install mulle-build
```

### Linux: Install mulle-build using linuxbrew

Install the [linuxbrew](//linuxbrew.sh/) package manager, then

```
brew tap mulle-kybernetik/software
brew install mulle-build
```

### All: Install mulle-build using git

```
git clone https://www.mulle-kybernetik.com/repositories/mulle-bootstrap
( cd mulle-bootstrap ; ./install.sh )
git clone https://www.mulle-kybernetik.com/repositories/mulle-build
( cd mulle-build ; ./install.sh )
```

## All: Install mulle-vararg using mulle-build


Grab the latest **mulle-vararg** release and go into the project directory:

```
git clone https://www.mulle-kybernetik.com/repositories/mulle-vararg
cd mulle-vararg
```

Then let **mulle-build** fetch the dependencies and build **mulle-vararg** in
debug mode:

```
mulle-build --debug
```

Build library in release mode and install into `tmp` :

```
mulle-clean ;
mulle-install --prefix /tmp
```