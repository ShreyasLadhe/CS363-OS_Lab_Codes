#!/bin/bash

read -p "Enter a number: " number

echo "Multiplication table for $number:"
for i in {1..10}; do
  result=$((number * i))
  echo "$number x $i = $result"
done
