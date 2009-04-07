# $Id$
#
# Some notes about static linking:
# There are two ways of linking to static library: using the -l command line
# option or specifying the full path to the library file as one of the inputs.
# When using the -l option, the library search paths will be searched for a
# dynamic version of the library, if that is not found, the search paths will
# be searched for a static version of the library. This means we cannot force
# static linking of a library this way. It is possible to force static linking
# of all libraries, but we want to control it per library.
# Conclusion: We have to specify the full path to each library that should be
#             linked statically.
#
# Legend of the suffixes:
# _SYS_DYN: link dynamically against system libs
#           this is the default mode; useful for local binaries
# _SYS_STA: link statically against system libs
#           this seems pointless to me; not implemented
# _3RD_DYN: link dynamically against libs from non-system dir
#           might be useful; not implemented
# _3RD_STA: link statically against libs from non-system dir
#           this is how we build our redistributable binaries

# This Makefile needs parameters to operate; check that they were specified:
# - log file
ifeq ($(origin LOG),undefined)
$(error Missing parameter: LOG)
endif
# - installation location of 3rd party libraries
ifeq ($(origin 3RDPARTY_INSTALL_DIR),undefined)
$(error Missing parameter: 3RDPARTY_INSTALL_DIR)
endif


# Functions
# =========

ALL_FUNCS:=FTRUNCATE GETTIMEOFDAY MMAP USLEEP POSIX_MEMALIGN

FTRUNCATE_FUNC:=ftruncate
FTRUNCATE_HEADER:=<unistd.h>

GETTIMEOFDAY_FUNC:=gettimeofday
GETTIMEOFDAY_HEADER:=<sys/time.h>

MMAP_FUNC:=mmap
MMAP_HEADER:=<sys/mman.h>

USLEEP_FUNC:=usleep
USLEEP_HEADER:=<unistd.h>

POSIX_MEMALIGN_FUNC:=posix_memalign
POSIX_MEMALIGN_HEADER:=<stdlib.h>

# Disabled X11, because it is not useful yet and the link flags are not here.
#X11_FUNC:=XtMalloc
#X11_HEADER:=<X11/Intrinsic.h>


# Headers
# =======

ALL_HEADERS:=$(addsuffix _H, \
	GL GL_GL GLEW GL_GLEW JACK PNG SDL SDL_IMAGE SDL_TTF \
	SYS_MMAN SYS_SOCKET TCL XML ZLIB )

# Location of GL headers is not standardised; if one of these matches,
# we consider the GL headers found.
GL_HEADER:=<gl.h>
GL_GL_HEADER:=<GL/gl.h>
GL_CFLAGS:=
# Use GL_CFLAGS for GL_GL as well, if someone overrides it.
# In any case, only GL_CFLAGS will be used by the actual build.
GL_GL_CFLAGS=$(GL_CFLAGS)

# The comment for the GL headers applies to GLEW as well.
GLEW_HEADER:=<glew.h>
GL_GLEW_HEADER:=<GL/glew.h>
GLEW_CFLAGS_SYS_DYN:=
GLEW_CFLAGS_3RD_STA:=-I$(3RDPARTY_INSTALL_DIR)/include

JACK_HEADER:=<jack/jack.h>
JACK_CFLAGS_SYS_DYN:=
JACK_CFLAGS_3RD_STA:=-I$(3RDPARTY_INSTALL_DIR)/include

PNG_HEADER:=<png.h>
PNG_CFLAGS_SYS_DYN:=`libpng-config --cflags 2>> $(LOG)`
# Note: The additional -I is to pick up the zlib headers when zlib is not
#       installed systemwide.
PNG_CFLAGS_3RD_STA:=`$(3RDPARTY_INSTALL_DIR)/bin/libpng-config --cflags 2>> $(LOG)` -I$(3RDPARTY_INSTALL_DIR)/include

SDL_HEADER:=<SDL.h>
SDL_CFLAGS_SYS_DYN:=`sdl-config --cflags 2>> $(LOG)`
SDL_CFLAGS_3RD_STA:=`$(3RDPARTY_INSTALL_DIR)/bin/sdl-config --cflags 2>> $(LOG)`

SDL_IMAGE_HEADER:=<SDL_image.h>
# Note: "=" instead of ":=", so overriden value of SDL_CFLAGS will be used.
SDL_IMAGE_CFLAGS_SYS_DYN=$(SDL_CFLAGS_SYS_DYN)
SDL_IMAGE_CFLAGS_3RD_STA=$(SDL_CFLAGS_3RD_STA)

SDL_TTF_HEADER:=<SDL_ttf.h>
# Note: "=" instead of ":=", so overriden value of SDL_CFLAGS will be used.
SDL_TTF_CFLAGS_SYS_DYN=$(SDL_CFLAGS_SYS_DYN)
SDL_TTF_CFLAGS_3RD_STA=$(SDL_CFLAGS_3RD_STA)

SYS_MMAN_HEADER:=<sys/mman.h>

SYS_SOCKET_HEADER:=<sys/socket.h>

TCL_HEADER:=<tcl.h>
TCL_CFLAGS_SYS_DYN:=`build/tcl-search.sh --cflags 2>> $(LOG)`
TCL_CFLAGS_3RD_STA:=`TCL_CONFIG_DIR=$(3RDPARTY_INSTALL_DIR)/lib build/tcl-search.sh --cflags 2>> $(LOG)`

XML_HEADER:=<libxml/parser.h>
XML_CFLAGS_SYS_DYN:=`xml2-config --cflags 2>> $(LOG)`
XML_CFLAGS_3RD_STA:=`$(3RDPARTY_INSTALL_DIR)/bin/xml2-config --cflags 2>> $(LOG)` -DLIBXML_STATIC

ZLIB_HEADER:=<zlib.h>
ZLIB_CFLAGS_SYS_DYN:=
ZLIB_CFLAGS_3RD_STA:=-I$(3RDPARTY_INSTALL_DIR)/include


# Libraries
# =========

ALL_LIBS:=GL GLEW JACK PNG SDL SDL_IMAGE SDL_TTF TCL XML ZLIB
ALL_LIBS+=ABC XYZ

GL_LDFLAGS:=-lGL
GL_RESULT:=yes

GLEW_LDFLAGS_SYS_DYN:=-lGLEW
GLEW_LDFLAGS_3RD_STA:=$(3RDPARTY_INSTALL_DIR)/lib/libGLEW.a
GLEW_RESULT:=yes

JACK_LDFLAGS_SYS_DYN:=-ljack
JACK_LDFLAGS_3RD_STA:=$(3RDPARTY_INSTALL_DIR)/lib/libjack.a
JACK_RESULT:=yes

PNG_LDFLAGS_SYS_DYN:=`libpng-config --ldflags 2>> $(LOG)`
PNG_LDFLAGS_3RD_STA:=$(3RDPARTY_INSTALL_DIR)/lib/libpng12.a
PNG_RESULT_SYS_DYN:=`libpng-config --version`
PNG_RESULT_3RD_STA:=`$(3RDPARTY_INSTALL_DIR)/bin/libpng-config --version`

SDL_LDFLAGS_SYS_DYN:=`sdl-config --libs 2>> $(LOG)`
SDL_LDFLAGS_3RD_STA:=$(3RDPARTY_INSTALL_DIR)/lib/libSDL.a
SDL_RESULT_SYS_DYN:=`sdl-config --version`
SDL_RESULT_3RD_STA:=`$(3RDPARTY_INSTALL_DIR)/bin/sdl-config --version`

# Note: "=" instead of ":=", so overriden value of SDL_LDFLAGS will be used.
SDL_IMAGE_LDFLAGS_SYS_DYN=-lSDL_image $(SDL_LDFLAGS_SYS_DYN)
SDL_IMAGE_LDFLAGS_3RD_STA:=$(3RDPARTY_INSTALL_DIR)/lib/libSDL_image.a
SDL_IMAGE_RESULT:=yes

SDL_TTF_LDFLAGS_SYS_DYN=-lSDL_ttf $(SDL_LDFLAGS_SYS_DYN)
SDL_TTF_LDFLAGS_3RD_STA:=$(3RDPARTY_INSTALL_DIR)/lib/libSDL_ttf.a $(3RDPARTY_INSTALL_DIR)/lib/libfreetype.a
SDL_TTF_RESULT:=yes

TCL_LDFLAGS_SYS_DYN:=`build/tcl-search.sh --ldflags 2>> $(LOG)`
# Note: Tcl can be compiled with a static or a dynamic library, not both.
#       So whether this returns static or dynamic link flags depends on how
#       this copy of Tcl was built.
TCL_LDFLAGS_3RD_STA:=`TCL_CONFIG_DIR=$(3RDPARTY_INSTALL_DIR)/lib build/tcl-search.sh --static-libs 2>> $(LOG)`
TCL_RESULT_SYS_DYN:=`build/tcl-search.sh --version 2>> $(LOG)`
TCL_RESULT_3RD_STA:=`TCL_CONFIG_DIR=$(3RDPARTY_INSTALL_DIR)/lib build/tcl-search.sh --version 2>> $(LOG)`

XML_LDFLAGS_SYS_DYN:=`xml2-config --libs 2>> $(LOG)`
XML_LDFLAGS_3RD_STA:=$(3RDPARTY_INSTALL_DIR)/lib/libxml2.a
XML_RESULT_SYS_DYN:=`xml2-config --version`
XML_RESULT_3RD_STA:=`$(3RDPARTY_INSTALL_DIR)/bin/xml2-config --version`

ZLIB_LDFLAGS_SYS_DYN:=-lz
ZLIB_LDFLAGS_3RD_STA:=$(3RDPARTY_INSTALL_DIR)/lib/libz.a
ZLIB_RESULT:=yes

# Libraries that do not exist:
# (these are to test error reporting, it is expected that they are not found)

ABC_LDFLAGS:=`abc-config --libs 2>> $(LOG)`
ABC_RESULT:=impossible

XYZ_LDFLAGS:=-lxyz
XYZ_RESULT:=impossible