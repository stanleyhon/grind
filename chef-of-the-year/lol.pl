
$input = <>;
@tokens = split (' ', $input);

$numChefs = $tokens[0];
$numEmails = $tokens[1];
@tokens = "";

%chefs = ();

$count = 0;
while ($count < $numChefs) {
    $stdin = <>;
    chomp $stdin;
    @tokens = split (/ /, $stdin);
#printf ("Adding chef |$tokens[0]| from |$tokens[1]|\n");
    $chefs{$tokens[0]} = $tokens[1];
    $count++;
}

%chefVotes = ();
%countryVotes = ();

# now emails
$count = 0;

while ($count < $numEmails) {
    $chefname = <>;
    chomp $chefname;
#:/print "Counting one for $chefname\n";
    if (exists $chefVotes{$chefname}) {
        $chefVotes{$chefname}++;
    } else {
        $chefVotes{$chefname} = 1;
    }
    $chefCountry = $chefs{$chefname};
#print "Counting one for country $chefCountry\n";
    if (exists $countryVotes{$chefCountry}) {
        $countryVotes{$chefCountry}++;
    } else {
        $countryVotes{$chefCountry} = 1;
    }
    $count++;
}

# now find highest country
$highestVote = 0;
@highestKeys = ();
foreach $key (keys %countryVotes) {
#   print "Currently, highestVote is $highestVote\n";
    if ($countryVotes{$key} == $highestVote) {
        push (@highestKeys, $key);
    } elsif ($countryVotes{$key} > $highestVote) {
        $highestVote = $countryVotes{$key};
        # Wipe the array
        @highestKeys = ();
        $scalarCount = scalar @highestKeys;
        push (@highestKeys, $key);
    }
}

# Print highest voted country
if (scalar @highestKeys == 1) {
    print "$highestKeys[0]\n";
} else {
    # Somehow, smallest word
    $smallestName = ();
    $count = 0;
    while ($count < scalar @highestKeys) {
        if ($count == 0) {
            $smallestName = $highestKeys[0];
        } else {
            if ($highestKeys[$count] lt $smallestName) {
                $smallestName = $highestKeys[$count];
            }
        }
        $count++;
    }
    print "$smallestName\n";
}

# Print highest voted chef
$highestVote = 0;
@highestKeys = ();
foreach $key (keys %chefVotes) {
#print "chefvotes $key is hashed to $chefVotes{$key}\n"; 
    if ($highestVote < $chefVotes{$key}) { # new highest
        @highestKeys = ();
        $highestVote = $chefVotes{$key};
        push (@highestKeys, $key);
    } elsif ($highestVote == $chefVotes{$key}) { # Equal, push
        push (@highestKeys, $key);
    }
}


# Print highest voted chef 
if (scalar @highestKeys == 1) {
    print "$highestKeys[0]\n";
} else {
    $numResults = scalar @highestKeys;
    # Somehow, smallest word
    $smallestName = "";
    $count = 0;
    while ($count < scalar @highestKeys) {
        if ($count == 0) {
            $smallestName = $highestKeys[0];
#        print "Choosing $highestKeys[0] since first loop\n";
        } else {
            if ($highestKeys[$count] lt $smallestName) {
                $smallestName = $highestKeys[$count];
            }
        }
        $count++;
    }
    print "$smallestName\n";
}
