#!/bin/bash

read -p "Enter the directory path to process: " dir_path

if [ ! -d "$dir_path" ]; then
  echo "The directory does not exist."
  exit 1
fi

find "$dir_path" -type f -name "*.o" -print -exec rm {} \;

find "$dir_path" -type d -mindepth 1 -print | while read subdir; do
  zip -r "${subdir}.zip" "$subdir"
  echo "Created zip archive for $subdir"
done

echo "Processing complete."
