#!/usr/bin/env bash

make format

git add *.c *.sh
git commit -m "auto push"
git push
