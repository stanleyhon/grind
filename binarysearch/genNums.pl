#!/usr/bin/perl -w

$total = $ARGV[0];

print $total;
print "\n";

$lookFor = 0;
$cur = 0;
$num = 0;
while ($num < $total) {
    print $cur;
    print "\n";
    $cur += int(rand(40));

    if ($lookFor == 0) {
        if (int(rand(100)) == 10) {
            $lookFor = $cur;
        }
    }

    $num++;
}

print $lookFor;

