#!/usr/bin/env bash

make

for i in {0..8}; do
    ./banhammer -s -a -f $(( 10**i )) < ~/resources/corpora/calgary/news
done

gnuplot << EOF
set terminal pdf
set bmargin 4
set key outside
set logscale x; set xtics 1, 100, 1e8
set xlabel "bf size"

set output "stats.pdf"
set title "Statistics for avg branches and avg bst height"
set ylabel "Info"
plot "bst_height.dat" using 1:2 with linespoints title "avg bst height", \
    "avg_branches.dat" using 1:2 with linespoints title " avg branches traversed "

EOF

rm -rf *.dat
make clean

git add *.pdf
git commit -m "adding stats pdfs"
git push
