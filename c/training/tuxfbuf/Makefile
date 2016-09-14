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
TTYPE	=INCLUDE

# *** MUST GET THIS CORRECT ! Use SQL= if no ESQL, SQL=SQL if ESQL used
SQL	=


FILES	= coint.fd cocrd.fd pdc.fd event.fd atm.fd stat.fd\
	  enc.fd service.fd tim.fd visa.fd iso.fd europay.fd monitor.fd emv.fd\
	  emvscr.fd amex.fd queue.fd iso_de.fd

#   Obsolete files now p4 deleted =  conag.fd gjob.fd

# Name your library, if that's what you're building
LIB	=

# Name your executable, if you want an ordinary biary, client, or server
EXE	=

# If server, put server flags here, e.g. -s DUMMY
SRVFLAGS=

# Where the makefile lives (so people can copy it to home dir)
# NB !!! It * MUST * end in /, e.g ORGDIR=/home/tom/
ORGDIR	=./

# Add your own includes here
INCPATH	=
# Add paths to any libraries
LIBPATH	=
# Add paths to any u files
UPATH	=
# Add any library dependencies
LIBDEPS	=
# Where test executables go
TSTDIR	=
# Where final executables go
EXEDIR	=$(ORGDIR)../include
# Where libraries go
LIBDIR	=
# Any subsidiary makes to trigger
SUBMAKES=
# Any subdirectories to make in
SUBDIRS	=

first: all
	rm -f $(EXEDIR)/../../tuxfbuf/Usysflds
	cp Usysflds $(EXEDIR)/../../tuxfbuf

#*-----------------------------------------------------------------------
#* These bits are (fairly) untouchable ...
#*-----------------------------------------------------------------------
include /opt/bin/makeinc

