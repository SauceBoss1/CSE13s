#!/usr/bin/env bash

git rm avg_branches.pdf lookups.pdf avg_branches_ht.pdf lookups_ht.pdf
git commit -m "remove pdf"
git push

rm -rf avg_branches.pdf lookups.pdf avg_branches_ht.pdf lookups_ht.pdf
