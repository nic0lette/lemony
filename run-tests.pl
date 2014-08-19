#! /usr/bin/env perl
use strict;
use warnings;
use IPC::Open3;

sub runTest {
	my $file = $_[0];
	printf("Run test: %s\n", $file);
	
	my $expected = "";
	
	open(FILE, $file);
	my @lines = <FILE>;
	foreach my $line (@lines) {
		$line =~ s/\\n/\n/g;
		if ($line !~ /^\n$/) {
			if ($line =~ /^#= /) {
				$line =~ s/^#= //;
				chomp($line);
				
				$expected = $line;
			} elsif ($line =~ /^# /) {
				printf("%s", $line);
			} else {
				my $pid = open3(\*LSTDIN, \*LSTDOUT, \*LSTDERR, "./lemony")
					or die("Couldn't start interperter");
					
				# Send in the input then close
				print LSTDIN $line;
				close LSTDIN;
				
				# Read results
				my $out;
				while(<LSTDOUT>) {
					$out = $_;
					printf(" lemony: %s", $out);
				}
				while(<LSTDERR>) {
					$out = $_;
					printf(" lemony [e]: %s", $out);
				}
				
				# Rip off the EOL from the output
				chomp($out);
				
				if ($out eq $expected) {
					printf(" Test: PASS\n");
				} elsif ($expected eq "") {
					printf(" Test: No expected results\n");
				} else {
					printf(" Test: FAIL :: '%s' vs '%s'\n", $expected, $out);
				}
				
				# Done
				close LSTDOUT;
				close LSTDERR;
				$expected = "";
			}
		}
	}
	
	close(FILE);
}

my $testsDir = 'tests/';
opendir(DIR, $testsDir) or die $!;

while (my $file = readdir(DIR)) {
	if ($file =~ /\.lm/) {
		runTest($testsDir . $file);
	}
}

closedir(DIR);