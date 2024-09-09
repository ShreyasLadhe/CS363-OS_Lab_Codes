#!/bin/bash

perform_operation() {
  local num1=$1
  local num2=$2
  local operation=$3

  if [ "$operation" = "add" ]; then
    result=$(echo "$num1 + $num2" | bc)
  elif [ "$operation" = "subtract" ]; then
    result=$(echo "$num1 - $num2" | bc)
  elif [ "$operation" = "multiply" ]; then
    result=$(echo "$num1 * $num2" | bc)
  elif [ "$operation" = "divide" ]; then
    if [ "$num2" != "0" ]; then
      result=$(echo "scale=2; $num1 / $num2" | bc)
    else
      echo "Error: Division by zero is not allowed."
      return
    fi
  else
    echo "Invalid operation. Please use one of add, subtract, multiply, divide."
    return
  fi

  echo "Result: $result"
}

read -p "Enter the first number: " num1
read -p "Enter the second number: " num2
read -p "Enter the operation (add, subtract, multiply, divide): " operation
perform_operation $num1 $num2 $operation
