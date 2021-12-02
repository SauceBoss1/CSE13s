#!/usr/bin/env bash

make

for i in {0..6}; do
    ./banhammer -s -t $(( 10**i )) -f $(( 10**i )) < ~/resources/corpora/calgary/news
done

make clean
