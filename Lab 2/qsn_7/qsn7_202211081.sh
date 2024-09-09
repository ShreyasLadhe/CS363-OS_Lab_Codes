#!/bin/bash

prime_check() {
   num=$1
  
  if [ "$num" -lt 2 ]; then
    echo "$num is not a prime number."
    return
  fi

  if [ "$num" -eq 2 ]; then
    echo "$num is a prime number."
    return
  fi

  if [ $((num % 2)) -eq 0 ]; then
    echo "$num is not a prime number."
    return
  fi

   limit=$(echo "sqrt($num)" | bc)
  for (( i=3; i<=$limit; i+=2 )); do
    if [ $((num % i)) -eq 0 ]; then
      echo "$num is not a prime number."
      return
    fi
  done

  echo "$num is a prime number."
}

read -p "Enter a number to check if it's prime: " number
prime_check $number
