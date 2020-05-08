#!/bin/bash

# Remove old directory
rm -rf ./public

# Clone gh-pages branch
git clone -b gh-pages git@github.com:ReverentEngineer/minimalist-map.git public

# Remove old artifacts
cd public
git rm -rf ./*
cd ..

# Make new artifacts
doxygen

# Add new artifacts to git
cd public
git add ./*
git commit -m "Update from $(date)"
git push
