#!/bin/bash

c_files=$(ls *.c)

for file in $c_files; do
    filename=$(basename "$file" .c)

    gcc "$file" -o "$filename"

    if [ $? -eq 0 ]; then
        echo "Compiled $file successfully"
        xterm -hold -e "./$filename" &
    else
        echo "Failed to compile $file"
    fi
done
