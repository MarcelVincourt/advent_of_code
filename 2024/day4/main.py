#!/usr/bin/env python3

FILE = "input.txt"

#2363 to low
#2547 to low
#2581 to high

#2571

#part 2
#1946 to low

def count_in_line(line: str) -> int:
    count = 0
    target = "XMAS"
    target_len = len(target)
    for i in range(len(line) - target_len + 1):
        if line[i:i + target_len] == target:
            count += 1
    return count

def vertical(lines: list[str]) -> int:
    summ = 0
    text = ""
    for i in range(len(lines)):
        for j in range(len(lines[i])):
            text += lines[j][i]
        summ += count_in_line(text)
        summ += count_in_line(text[::-1])
        text = ""
    return summ

def new_diagonally(grid: list[str]):
    rows = len(grid)
    cols = len(grid[0])
    target = "XMAS"
    target_len = len(target)
    total_count = 0
    # 3. Count diagonally (top-left to bottom-right and bottom-left to top-right)
    # Top-left to bottom-right diagonals
    for start in range(-rows + 1, cols):
        diagonal = ''.join(grid[row][start + row] for row in range(rows) if 0 <= start + row < cols)
        total_count += count_in_line(diagonal)  # TL to BR
        total_count += count_in_line(diagonal[::-1])  # BR to TL

    # Bottom-left to top-right diagonals
    for start in range(rows + cols - 1):
        diagonal = ''.join(grid[row][start - row] for row in range(rows) if 0 <= start - row < cols)
        total_count += count_in_line(diagonal)  # BL to TR
        total_count += count_in_line(diagonal[::-1])  # TR to BL
    return total_count

def xmas(lines):
    text1 = ""
    text2 = ""
    count = 0
    rows = len(lines)
    columns = len(lines[0])
    print("rows: ", rows)
    print("cols: ", columns)
    for row in range(len(lines)):
        for col in range(len(lines[row])):
            try:
                text1 += lines[row][col]
                text1 += lines[row+1][col+1]
                text1 += lines[row+2][col+2]
            except IndexError:
                #print(row, col)
                text1 = ""

            try:
                text2 += lines[row][col+2]
                text2 += lines[row+1][col+1]
                text2 += lines[row+2][col]
            except IndexError:
                text2 = ""

            if text1 and text2:
                if (text1 == "MAS" or text1 == "SAM") and (text2 == "MAS" or text2 == "SAM"):
                    print(text1, text2)
                    count += 1

            text1 = ""
            text2 = ""
    return count


if __name__ == "__main__":
    print("dag 4")

    puzzle = []

    with open(FILE, 'r') as f:
        lines = f.readlines()
    lines = [line.strip() for line in lines]

    summ = 0
    for line in lines:
        summ += count_in_line(line)
        summ += count_in_line(line[::-1])
    summ += vertical(lines)
    summ += new_diagonally(lines)
    print("Found: ", summ)

    p2 = xmas(lines)
    print("part2: ", p2)
