#!/usr/bin/env perl

use strict;
use URI;
use IO::Socket;

my $showOpenedSockets=1;

my $server = IO::Socket::INET->new (
   LocalPort => 8080,
   Type      => SOCK_STREAM,
   Reuse     => 1,
   Listen    => 10);


binmode $server;

while (my $browser = $server->accept()) {
  print "\n\n--------------------------------------------\n";

  binmode $browser;

  my $method              ="";
  my $content_length      = 0;
  my $content             = 0;
  my $accu_content_length = 0;
  my $host;
  my $hostAddr;
  my $httpVer;

  while (my $browser_line = <$browser>) {
    unless ($method) {
      ($method, $hostAddr, $httpVer) = $browser_line =~ /^(\w+) +(\S+) +(\S+)/;

      my $uri = URI->new($hostAddr);

     # print "URI: [] [$uri->host] [$uri->port] [$hostAddr]\n";
      $host = IO::Socket::INET->new (
        PeerAddr=> $uri->host,
        PeerPort=> $uri->port );

        die "couldn't open $hostAddr" unless $host;

      if ($showOpenedSockets) {
        print "Opened ".$uri->host." , port ".$uri->port."\n";
      }

      binmode $host;

      print $host "$method ".$uri->path_query." $httpVer\n";
      print "$method ".$uri->path_query." $httpVer\n";
      next;
    }

    $content_length = $1 if      $browser_line=~/Content-length: +(\d+)/i;
    $accu_content_length+=length $browser_line;

    print $browser_line;

    print $host $browser_line;

    last if $browser_line =~ /^\s*$/ and $method ne 'POST';
    if ($browser_line =~ /^\s*$/ and $method eq "POST") {
      $content = 1;
      last unless $content_length;
      next;
    }
    if ($content) {
      $accu_content_length+=length $browser_line;
      last if $accu_content_length >= $content_length;
    }
  }
  print "\n\n....................................\n";
  
  $content_length      = 0;
  $content             = 0;
  $accu_content_length = 0;
  while (my $host_line = <$host>) {
    print $host_line;
    print $browser $host_line;
    $content_length = $1 if $host_line=~/Content-length: +(\d+)/i;
    if ($host_line =~ m/^\s*$/ and not $content) {
      $content = 1;
      #last unless $content_length;
      next;
    }
    if ($content) {
      if ($content_length) {
        $accu_content_length+=length $host_line;
        #print "\nContent Length: $content_length, accu: $accu_content_length\n";
        last if $accu_content_length >= $content_length;
      }
    }
  }
  $browser-> close;
  $host   -> close;
}

