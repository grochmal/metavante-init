#!/bin/awk   -f
#
# @(#) - Script to auto generate iso_de.fd
# 
# Syntax:  
#         gen_iso_de_fd.sh

M_relno=0+0

BEGIN {

	# Generate the fixed header 

print "# _____ Automatically generated by P4 stamps - Do not edit! _____"
print "# #(@) E13CB5D2 $Id: //depot/cortex/project/cortex_v3.2_db_esql/base/common/src/tuxfbuf/gen_iso_de_fd.sh#1 $"
print "# #(@) E13CB5D2 $Author: qa $"
print "# #(@) E13CB5D2 $DateTime: 2009/12/08 17:59:56 $"
print "# #(@) E13CB5D2 $Change: 78584 $"
print "# _________________________ End of P4 stamps ____________________"
print ""
print "# JCN NMR010291 23/09/2003"
print "# Make sure that the file is only included once"
print "# Use the '$' to pass the static code through"
print "$#ifndef __ISO_DE_FD"
print "$#define __ISO_DE_FD"
print ""
print "*base 3200"
print ""
print "#name           relno   type    flags   comment"
print "#----           -----   ----    -----   -------"
print ""

	M_relno=0+0;

	# Special for MTID
	printf "ISO_DE_MTID	%d	carray	-	1 ISO MTID\n",M_relno
	M_relno++;

	# Special for the ISO BITMAP
	printf "ISO_DE_BITMAP	%d	string	-	1 ISO Bitmap 1 (ctx gen)\n",M_relno
	M_relno++
	
	# First Generate all the ISO_DExxx elements
	for (de_num=1; de_num<=192; de_num++) {
		printf "ISO_DE%03d	%d	carray	-	1 ISO DE %03d\n",de_num,M_relno,de_num
		M_relno++
	}

	# Generate DE 3 with subfields 0-3
	gen_subfields(3, 3, 1)

	# Generate DE 7 with subfields 0-2
	gen_subfields(7, 2, 1)

	# Generate DE 22 with subfields 0-2
	gen_subfields(22, 2, 1)

	# Generate DE 48 with subfields 0-100 (Mastercard)
	gen_subfields(48, 100, "M")

	# Generate DE 53 with subfields 0-6 (Mastercard)
	gen_subfields(53, 6, 1)

	# Generate DE 54 with subfields 0-4 (Mastercard)
	gen_subfields(54, 4, "M")

	# DE 55 fields are special, as multiple
	# occurrences of ISO_DE055_TAG_L & ISO_DE055_VAL
	print
	printf "ISO_DE%03d_BITMAP %d	string  -	1 DE%03d Bitmap (ctx gen)\n",55,M_relno,55
	M_relno++;
	printf "ISO_DE%03d_FORMAT %d	short	-	1 DE%03d Format (ctx gen)\n",55,M_relno,55
	M_relno++
	printf "ISO_DE055_TAG_L	%d	long	-	M De 55 tag as long num\n",M_relno
	M_relno++
	printf "ISO_DE055_VAL	%d	carray	-	M DE 55 val as binary\n",M_relno
	M_relno++

	# Generate DE 60 with subfields 0-10 (Visa)
	gen_subfields(60, 3, 1)

	# Generate DE 61 with subfields 0-14 (Mastercard)
	gen_subfields(61,14, 1)

	# Generate DE 63 with subfields 0-2 (Mastercard)
	gen_subfields(63, 2, 1)

	# Generate DE 90 with subfields 0-5 (Mastercard)
	gen_subfields(90, 5, 1)

	# Generate DE 94 with subfields 0-3 (Mastercard)
	gen_subfields(94, 3, 1)

	# Generate DE 95 with subfields 0-4 (Mastercard)
	gen_subfields(95, 4, 1)

	# Generate DE 112 with subfields 0-3 (Mastercard)
	gen_subfields(112, 3, "M")

	# Generate DE 120 with subfields 0-4 (Mastercard)
	gen_subfields(120, 4, "M")

print ""
print "# MAX FIELD NUMBER = 1799 (Next file=tim.fd starting at field 5000)"
print ""
print "# JCN NMR010291 23/09/2003"
print "# Make sure that the file is only included once"
print "# Use the '$' to pass the static code through"
print "$#endif"
	exit
}


function gen_subfields(de, num_subfields, num_char) {

	# Leave a blank before the new group of fields
	print

	# Generate the bitmap data element saying which internal
	# fields are present (Generated by Cortex, just a string 
	# of ASCII '0' and '1's, offset 0=field 0
	printf "ISO_DE%03d_BITMAP %d	string  -	1 DE%03d Bitmap (ctx gen)\n",de,M_relno,de
	M_relno++;

	# Generate the format code, in case this field could be
	# one of many formats
	printf "ISO_DE%03d_FORMAT %d	short	-	1 DE%03d Format (ctx gen)\n",de,M_relno,de
	M_relno++

	# Now Generate the ISO_DEaaa_xxx subfields
	for (subfld=0; subfld<=num_subfields; subfld++) {
		printf "ISO_DE%03d_%02d	%d	carray	-	%s DE%03d subfield %d\n",de,subfld,M_relno,num_char "",de,subfld
		M_relno++;
	}

	# Add 10 to M_relno to leave space for more fields later
	M_relno += 10
}
