#!/usr/bin/perl -w

$count = 50000;

print "$count\n";

$i = 0;
while ($i < $count) {
    print (int (rand (100000)));
    print "\n";
    $i++;
}
