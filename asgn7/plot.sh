#!/usr/bin/env bash

make

for i in {0..10}; do
    ./banhammer -s -a -t $(( 10**i )) -f $(( 10**i )) < ~/resources/corpora/calgary/news
done

gnuplot << EOF
set terminal pdf
set bmargin 4
set key outside
set size ration 0.75
set xlabel "bf and ht size (they are set the same values)"

set output "stats.pdf"
set title "Statistics for avg_branches, avg_bst_height, and avg_bst_size"
set ylabel "Info"
plot "./bst_size.dat" using 1:2 with linespoints title "avg_bst_size", \
    "./bst_height.dat" using 1:2 with linespoints title "avg_bst_height", \
    "./avg_branches.dat" using 1:2 with linespoints title " avg_branches traversed "

EOF

rm -rf *.dat
make clean

git add *.jpg
git commit -m "adding jpgs"
git push
