#!/usr/bin/perl -w

$range = 1000000;

$count = 0;
while ($count < 10000) {
    print int(rand($range));
    print " ";
    $count++;
}
