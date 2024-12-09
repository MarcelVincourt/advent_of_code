#!/usr/bin/env python3

import re
FILE = "input.txt"

regex = "do\(\)|don't\(\)|mul\([0-9]+,[0-9]+\)"

if __name__ == "__main__":
    print("dag 3")

    text = ""
    summ = 0
    skipp = False
    with open(FILE, 'r') as f:
       text = f.read()
    matches = re.findall(regex, text)
    print(matches)
    for match in matches:
        if match == "don't()":
            skipp = True
            continue
        elif match == "do()":
            skipp = False
            continue
        if skipp:
            continue
        match = match.replace("mul(", "")
        match = match.replace(")", "")
        a, b = match.split(",")
        summ += int(a) * int(b)
    print(summ)

