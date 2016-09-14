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
TTYPE	=EXE

# *** MUST GET THIS CORRECT ! Use SQL= if no ESQL, SQL=SQL if ESQL used
SQL	=

# Name your files
FILES	=flags

# Name your library, if that's what you're building
LIB	=

# Name your executable, if you want an ordinary biary, client, or server
EXE	=flags

# If server, put server flags here, e.g. -s DUMMY
SRVFLAGS=

# Where the makefile lives (so people can copy it to home dir)
# NB !!! It * MUST * end in /, e.g ORGDIR=/home/tom/
ORGDIR	=./

# DMG NMR008903 - Common module partly split into crdbase
INCPATH =$(ORGDIR)../../../../base/common/src/include/sys\
	$(ORGDIR)../../../../base/common/src/include/db\
	$(ORGDIR)../../../../base/common/src/include\
	$(ORGDIR).

# Add paths to any libraries
LIBPATH	=$(ORGDIR)../../../../base/common/src/lib

# Add any library dependencies
LIBDEPS = stdlib

SYSLIBS	=

# Where test executables go
TSTDIR	=.
# Where final executables go
EXEDIR	=.
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

