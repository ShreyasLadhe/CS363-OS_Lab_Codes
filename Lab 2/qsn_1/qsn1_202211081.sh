#!/bin/bash

leap_check() {
  year=$1
  
  if [ $((year % 4)) -eq 0 ]; then
    if [ $((year % 100)) -eq 0 ]; then
      if [ $((year % 400)) -eq 0 ]; then
        echo "$year is a leap year."
      else
        echo "$year is not a leap year."
      fi
    else
      echo "$year is a leap year."
    fi
  else
    echo "$year is not a leap year."
  fi
}

read -p "Enter a year " year
leap_check $year

