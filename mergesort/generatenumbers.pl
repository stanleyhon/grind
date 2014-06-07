#!/usr/bin/perl -w

$count = 0;
print "900\n";
while ($count < 900) {
    print int(rand(1024));
    print "\n";
    $count++;
}

