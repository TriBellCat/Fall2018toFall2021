#Trinity Belen
#Comp 157
#Project 1: Tile Puzzle
#Description: A program to solve tile puzzles through the use of breadth first search
#I am counting the number of moves made by program when it uses bfs (i.e. going through the while loop in the bfs function) as a basic operation

import copy
import os
import time

#Breadth First Search Function: Searches through parents and then their children, and then children of the children
def bfs(tiles, Astar, dim):
    countMoves = 0
    tile_arr = []
    directions = []
    visited = []

    tile_arr.append(tiles)
    visited.append(tiles)
    directions.append(" ")

    while tile_arr:
        tiles = tile_arr.pop(0)
        dir = directions.pop(0)

        rows, col = find_x(tiles, dim)
        countMoves += 1
        if (col + 1 > dim):
            countMoves += 1
            copytiles = copy.deepcopy(tiles)
            temp = traverse_board(copytiles, rows, col, 'D')
            if temp not in visited:
                tile_arr.append(temp)
                visited.append(temp)
                directions.append(dir + "Down ")

        if (rows - 1 < 0):
            countMoves += 1
            copytiles = copy.deepcopy(tiles)
            temp = traverse_board(copytiles, rows, col, 'U')
            if temp not in visited:
                tile_arr.append(temp)
                visited.append(temp)
                directions.append(dir + "Up ")

        if (col + 1 < dim):
            countMoves += 1
            copytiles = copy.deepcopy(tiles)
            temp = traverse_board(copytiles, rows, col, 'R')
            if temp not in visited:
                tile_arr.append(temp)
                visited.append(temp)
                directions.append(dir + "Right ")


        if (col - 1 >= 0):
            countMoves += 1
            copytiles = copy.deepcopy(tiles)
            temp = traverse_board(copytiles, rows, col, 'L')
            if temp not in visited:
                tile_arr.append(temp)
                visited.append(temp)
                directions.append(dir + "Left ")
    print("Number of moves made so far: %s" % countMoves)
    return "Unsolvable"

#Stores the board
def memory(choose_type, tile_choice):
    tiles = []
    file = open("Puzzles_" + choose_type + "/" + "puzzle" + tile_choice + ".txt")
    for line in file:
        btiles = line.split(' ')
        temp = []
        for tile in btiles:
            temp.append(tile.strip())
        tiles.append(temp)
    file = open(choose_type + "Answer.txt", 'r')
    Astar = []

    for line in file:
        btiles = line.split(' ')
        temp = []
        for tile in btiles:
            temp.append(tile.strip())
        Astar.append(temp)
    file.close()
    return tiles, Astar


def menu():
    print("3 digits and X\n", "8 digits and X\n","15 digits and X\n")

    choose_type = input("Enter the number of digits of the tile puzzle you want: (3,8, or 15): ")
    print(os.listdir("Puzzles_" + choose_type))
    tile_choice = input("Enter the number of the puzzle you want (number is the # from puzzle#.txt) :")

    return choose_type, tile_choice

#Prints the board
def print_board(tiles, row):
    for i in range(0, row):
        word = " ".join(tiles[i])
        print(word)

#Finds the x that the program can move
def find_x(tiles, dimension):
    for i in range(0, dimension):
        for j in range(0, dimension):
            if 'X' == tiles[i][j]:
                return i, j

#Traverses through the board to find and move x in a specific direction
def traverse_board(tilesList, rows, col, dir):
    if dir == 'U':
        tempNum = tilesList[rows - 1][col]
        tilesList[rows - 1][col] = 'X'
        tilesList[rows][col] = tempNum

    elif dir == 'L':
        tempNum = tilesList[rows][col - 1]
        tilesList[rows][col - 1] = 'X'
        tilesList[rows][col] = tempNum

    elif dir == "D":
        tempNum = tilesList[rows + 1][col]
        tilesList[rows + 1][col] = 'X'
        tilesList[rows][col] = tempNum

    elif dir == "R":
        tempNum = tilesList[rows][col + 1]
        tilesList[rows][col + 1] = 'X'
        tilesList[rows][col] = tempNum
    return tilesList


def main():
    start_time = time.time()
    choice = 'y'
    reset = 0
    while (choice == 'y'):
        #Resets the timer if the user decides to continue on
        if (reset > 0):
            start_time = time.time()

        choose_type, tile_choice = menu()
        tiles, Astar = memory(choose_type, tile_choice)

        dim = len(tiles)

        print_board(tiles, dim)
        print("Here's the boards")

        print(bfs(tiles, Astar, dim))
        print("--- %s seconds ---" % (time.time() - start_time))
        reset += 1
        choice = str.lower(input("Do you wish to continue? (y/n): "))

if __name__ == "__main__":
    main()