#!/bin/bash

read -p "Enter the number of terms in the series: " terms

a=0
b=1

echo "Fibonacci series up to $terms terms:"

for (( i=0; i<terms; i++ )); do
  if [ $i -eq 0 ]; then
    echo "$a"
  elif [ $i -eq 1 ]; then
    echo "$b"
  else
    next=$((a + b))
    echo "$next"
    a=$b
    b=$next
  fi
done
