#!/usr/bin/perl
undef $/;
$_ = <>;
$n = 0;

#
# This code read .seq frame by frame and store each one in a figure
# in results/fout/
#
# First running this code, do:
# hexdump -n16 -C Rec-000001.seq 
# to check the magic bits, which is camera specific!!
#
$pat="\x46\x46\x46\x00\x52\x65\x73\x65\x61\x72\x63\x68\x49\x52";

for $content (split(/(?=$pat)/)) {
    open(OUT, ">results/fout/seq_n" . ++$n . ".fff");
    binmode OUT;
    print OUT $content;
    close(OUT);
}
