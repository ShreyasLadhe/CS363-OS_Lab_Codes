#!/bin/bash

read -p "Enter the first string: " string1
read -p "Enter the second string: " string2
concat_str="$string1$string2"
echo "Concatenated string: $concat_str"