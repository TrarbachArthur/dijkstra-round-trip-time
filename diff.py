#!/usr/bin/python


#
# usage: ./scripts file1 file2
# This script does not compare the output order
#

from sys import argv
from math import fabs

ERR = 1e-10


def parser_line(raw: str) -> tuple[int, int, float]:
    a, b, err = raw.split(" ")
    return (int(a), int(b), float(err))

def print_diff(line1, line2: tuple[int, int, float]):
    a1, b1, err1 = line1
    a2, b2, err2 = line2
    print(f"{a1} {b1} {err1} -> {a2} {b2} {err2}")

def main():

    file1_path, file2_path = argv[1], argv[2]

    inputs1 = []
    inputs2 = []

    with open(file1_path, "r") as file1, open(file2_path, "r") as file2:

        lines1 = file1.readlines()
        lines2 = file2.readlines()

        if len(lines1) != len(lines2):
            print("the files are not the same size")
            exit(0)

        for i in range(len(lines1)):
            
            line1 = parser_line(lines1[i])
            line2 = parser_line(lines2[i])

            inputs1.append(line1)
            inputs2.append(line2)

    compare = dict()

    for i in inputs1:
        key = f"{i[0]}x{i[1]}"
        compare[key] = i[2]

    
    for i in inputs2:
        key = f"{i[0]}x{i[1]}"
        if abs(compare[key] - i[2]) > ERR:
            print_diff((i[0], i[1], compare[key]), i)


if __name__ == "__main__":

    if (len(argv) != 3):
        print(f"usage: {argv[0]} file1 file2")
        exit(1)

    main()