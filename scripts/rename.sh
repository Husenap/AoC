#!/bin/bash

# Find all files with a single digit in the filename
for filepath in $(find . -regex ".*_[0-9]*_[1-9]"); do

  # Extract the filename and directory path
  filename=$(basename "$filepath")
  dirpath=$(dirname "$filepath")

  # Extract the parts of the filename before and after the digit
  prefix=$(echo $filename | sed 's/_[0-9]_/./' | cut -d'.' -f1)
  suffix=$(echo $filename | sed 's/_[0-9]_/./' | cut -d'.' -f2)

  prefix=$(echo $filename | sed -E 's/day_([0-9]{4})_([1-9][0-9]*)/\1/')
  suffix=$(echo $filename | sed -E 's/day_([0-9]{4})_([1-9][0-9]*)/\2/')

  # Add a leading zero to the digit in the filename
  newname="$prefix"_0"$suffix"

  echo $newname

  # Rename the file
  # mv "$filepath" "$dirpath/$newname"
done
