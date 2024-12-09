#!/usr/bin/env python3

FILE = "test_input.txt"



if __name__ == "__main__":
    print("dag 4")

    puzzle = []

    with open(FILE, 'r') as f:
        lines = f.readlines()
    lines = [line.strip() for line in lines]

