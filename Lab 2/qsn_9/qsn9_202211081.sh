#!/bin/bash

# sudo apt install imagemagick

read -p "Enter the directory path to search for image files: " dir_path

if [ ! -d "$dir_path" ]; then
  echo "The directory does not exist."
  exit 1
fi

echo "Image files in $dir_path:"
find "$dir_path" -type f \( -iname "*.jpg" -o -iname "*.jpeg" -o -iname "*.png" -o -iname "*.gif" -o -iname "*.bmp" \) -print
jpg_files=$(find "$dir_path" -type f -iname "*.jpg")

if [ -z "$jpg_files" ]; then
  echo "No .jpg files found in the directory."
  exit 0
fi

for jpg_file in $jpg_files; do
  bmp_file="${jpg_file%.jpg}.bmp"
  echo "Converting $jpg_file to $bmp_file..."
  convert "$jpg_file" "$bmp_file"
done

echo "Conversion complete."
