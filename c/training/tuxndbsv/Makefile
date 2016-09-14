#*-----------------------------------------------------------------------
#* These are the bits you can play with
#*-----------------------------------------------------------------------

# Name your make type:
# Must be 	EXE
# or		LIB
# or		CLIENT
# or		SERVER
# or		INCLUDE (.v => .h. .vn => .h, .fd => .h)
# or		SCRIPT  (.sh => /opt/bin )
# or		OTHER (submakes, subdirectories etc)
TTYPE	=SERVER

# *** MUST GET THIS CORRECT ! Use SQL= if no ESQL, SQL=SQL if ESQL used
SQL	=

#CDEFINES=_ALL_SOURCE
SERVICES=HELLONM


# Name your files
FILES	= hellonmsv hellonmsvc hellonm

# Name your library, if that's what you're building
LIB	=

# Name your executable, if you want an ordinary biary, client, or server
EXE	= hellonmsv

# If server, put server flags here, e.g. -s DUMMY
SRVFLAGS=

# Where the makefile lives (so people can copy it to home dir)
# NB !!! It * MUST * end in /, e.g ORGDIR=/home/tom/
ORGDIR	=./

# Add your own includes here
INCPATH	= $(ORGDIR). \
	$(ORGDIR)../include \
	$(ORGDIR)../../../common/src/include \
	$(ORGDIR)../../../common/src/include/sys \
	$(ORGDIR)../../../common/src/include/db \
	$(ROOTDIR)/include

# Add paths to any libraries
LIBPATH	=$(ORGDIR)../lib\
	$(ORGDIR)../../../common/src/lib\
	$(ROOTDIR)/lib

# Add any library dependencies
LIBDEPS	=condb core stdlib

SYSLIBS =

# Where test executables go
TSTDIR	=.
# Where final executables go
EXEDIR	=../bin
# Where libraries go
LIBDIR	=
# Any subsidiary makes to trigger
SUBMAKES=
# Any subdirectories to make in
SUBDIRS	=

#*-----------------------------------------------------------------------
#* These bits are (fairly) untouchable ...
#*-----------------------------------------------------------------------
include /opt/bin/makeinc

