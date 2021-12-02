#!/usr/bin/env bash

make

for i in {0..10}; do
    ./banhammer -s -a -f $(( 10**i )) < ~/resources/corpora/calgary/news
done

gnuplot << EOF
set terminal pdf
set bmargin 4
set key outside
set logscale x; set xtics 1, 100, 1e10
set xlabel "bf size"

set output "lookups.pdf"
set title "Statistics for the number of lookups as bf size incr."
set ylabel "number of lookups"
plot "lookups.dat" using 1:2 with linespoints title "num of lookups", \

set output "avg_branches.pdf"
set title "Statistics for the average branches traversed"
set ylabel "average branches traversed"
plot "avg_branches.dat" using 1:2 with linespoints title "avg branches traversed"

EOF

rm -rf *.dat
make clean

git add *.pdf
git commit -m "adding stats pdfs"
git push
