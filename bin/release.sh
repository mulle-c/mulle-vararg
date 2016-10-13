#! /bin/sh -x

#
# These variables have to be configured on a by project basis
#
NAME="mulle-vararg"  # not the ruby name
DESC="Access variable arguments in struct layout fashion"
PROJECT=MulleVararg  # ruby requires camel-case
HEADER="src/mulle_vararg.h"
VERSIONNAME="MULLE_VARARG_VERSION"
ORIGIN=public
DEPENDENCIES=

HOMEPAGE="https://www.mulle-kybernetik.com/software/git/${NAME}"
RBFILE="${NAME}.rb"
HOMEBREWTAP="../homebrew-software"

# ARCHIVEURL will be evaled later! keep it in single quotes
ARCHIVEURL='https://www.mulle-kybernetik.com/software/git/${NAME}/tarball/${VERSION}'


main()
{
   # source it
   . ./bin/mulle-homebrew/mulle-homebrew.sh

   local VERSION  #  upper case for consistency in eval
   local TAG

   #
   # Version has to be figured out on a per project basis
   # get_header_version grabs the version from a header
   #
   VERSION="`get_header_version ${HEADER}`"
   TAG="${1:-${VERSION}}"

   git_main "${ORIGIN}" "${TAG}" || exit 1
   homebrew_main || exit 1
}

main "$@"
