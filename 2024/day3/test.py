#!/usr/bin/env python

import re

FILE_PATH = "input.txt"

# Regex pattern
pattern = r"mul\(\d{1,3},\d{1,3}\)"

if __name__ == '__main__':

    with open(FILE_PATH, 'r') as f:
        string = f.readline()
    matches = re.findall(pattern, string)
    print(len(matches))

    sum = 0
    for match in matches:
        match = match.replace("mul(", "")
        match = match.replace(")", "")
        a, b = match.split(",")
        sum += int(a) * int(b)
    print(sum)
