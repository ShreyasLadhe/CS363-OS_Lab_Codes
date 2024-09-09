#!/bin/bash

read -p "Enter the filename: " filename

if [ -e "$filename" ]; then
  echo "File name is found at $(realpath "$filename")."

  if [ -w "$filename" ]; then
    echo "Hurray!!! I can write on $filename."
  else
    echo "So sad."
  fi
else
  echo "File does not exist."
fi