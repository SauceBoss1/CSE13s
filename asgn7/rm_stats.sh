#!/usr/bin/env bash

git rm avg_branches.pdf lookups.pdf
git commit -m "remove pdf"
git push

rm -rf avg_branches.pdf lookups.pdf
