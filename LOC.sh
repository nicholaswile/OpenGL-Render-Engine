#!/bin/sh

git ls-files | grep '\.cpp' | xargs wc -l
git ls-files | grep '\.glsl' | xargs wc -l