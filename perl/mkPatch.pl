#!/bin/env perl
######
# mkPatch.pl
#
# Creates a patch file from the a perforce repository
# Copyright (c) under GPL 3
# Author Michal Grochmal
######

use strict;
use warnings;

# Globals
# Holds the job name, the changelists and the diff program between subroutines
my $job_name;
my $diff_prog;
my @changelists = ();

######
# main
#
# Organize subroutines (intuitive)
######

&init;
&find_changelists;

foreach (@changelists)
{
    &find_files($_);
}

######
# init
#
# Check the command line arguments, check the environmet and prints help
######

sub init
{
    my $argNum = $#ARGV + 1; # Number of arguments
    my $usage = "\nUsage:\n\t\tmkPatch [-h | --help] <job name>\n\n" .
        "Create a patch file from all files involving the perforce job.\n" .
        "For edited files this script depends on a GNU compatible diff,\n" .
        "if you are unsure about your diff program you can download a GNU\n" .
        "compatible diff through the open source binutils package.\n" .
        "As perforce's diff (p4 diff ...) isn't GNU compatible we need\n" .
        "to use a different diff program.\n" .
        "This script suposes the name of the GNU compatible diff as\n" .
        "simply \"diff\" (it's true on most linux systems, on the other\n" .
        "hand on most comercial UNIX system it's not). If you have a\n" .
        "different name for your diff please setup a \"PATCHDIFF\"\n" .
        "environment variable to the diff program name to be used by this\n" .
        "script and, consequently, by the perforce diff's\n\n";

    # Test the argument number or if the user wants help
    if($argNum != 1)
    {
        die $usage;
    }
    elsif($ARGV[0] eq "-h" || $ARGV[0] eq "--help")
    {
        die $usage;
    }
    else
    {
        $job_name = $ARGV[0];
    }

    # Test is such perforce job really exist
    # This will be 'p4 -j $job_name > /dev/null 2>&1'
    if(0 != system("cat job2change > /dev/null 2>&1"))
    {
        die "No such p4 job!\n";
    }

    # Test if we are using some different diff from the default
    if(exists $ENV{'PATCHDIFF'})
    {
        $diff_prog = $ENV{'PATCHDIFF'};
    }
    else
    {
        $diff_prog = "diff";
    }
}

######
# find_changelists
#
# Find the changelists related to this job and store in @changelists
######

sub find_changelists
{
    # This will be "p4 -j $job_name"
    open(JOB, '<job2change_onechange');
    while(<JOB>)
    {
        my $line = $_;
        chomp($line);

        $line =~ m/change\s[0-9]*\s/p;
        $line = ${^MATCH};

        $line =~ m/[0-9]+/p;
        $line = ${^MATCH};

        &add_to_array($line);
    }

    close(JOB);
}

######
# add_to_array
#
# Add only distinct values to array
######

sub add_to_array
{
    my($change) = @_;
    my $is_in_array = 'NO';

    foreach my $change_in_array (@changelists)
    {
        if($change_in_array eq $change)
        {
            $is_in_array = 'YES';
        }
    }

    if($is_in_array ne 'YES')
    {
        push(@changelists, $change);
    }
}

######
# find_files
#
# Lookup through the changelists for opened files and ditinguish them into
# added files, edited files and deleted files
######

sub find_files
{
    my($changelist) = @_;

    #open(CHANGE, "p4 opened -c $changelist");
    open(CHANGE, "<filesopened");
    while(<CHANGE>)
    {
        my $line = $_;
        chomp($line);

        if($line =~ m/#[0-9]*\s-\sedit\s/p) # Edit change
        {
            $line = ${^PREMATCH};
            print "File edited: \"" . $line . "\"\n";
        }
        elsif($line =~ m/#[0-9]*\s-\sadd\s/p) # Add change
        {
            $line = ${^PREMATCH};
            print "File added: \"" . $line . "\"\n";
        }
        elsif($line =~ m/#[0-9]*\s-\sdelete\s/p) # Delete change
        {
            $line = ${^PREMATCH};
            print "File deleted: \"" . $line . "\"\n";
        }
    }

    close(CHANGE);
}

######
# edit_file
#
# Uses p4 diff to create a patch from a file
######

sub edit_file
{
    my($depot_name) = @_;

    $ENV{'P4DIFF'} = $diff_prog;

    #open(DIFF, "p4 diff -du $depot_name");
    open(DIFF, "<edit_diff");
    while(<DIFF>)
    {
        $line = $_;
        chomp($line);

        $line =~ s/^====/---/

