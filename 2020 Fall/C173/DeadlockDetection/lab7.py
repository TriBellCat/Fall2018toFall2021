# Lab 7 - Deadlock Detection
# Trinity Caitlin Atayan Belen

from os import listdir

# Allocate function
def allocation(pack):
    stop = False  # stops checking for deadlocks if true, starts checking if false
    missed = []  # array to check for missed values that the checker missed
    order = []   # array to store the order of allocation

    newavail = pack.get("available").copy()    # Creates a new available matrix, which will be updated more to the pack

    # First time to check for deadlock
    for x in range(pack.get("processes") + 1):

        # breaks out of loop if stop is true
        if stop is True:
            break

        print("Checking Process: %d" % x)

        # updates the pack info to the available copy
        pack.update({"available": newavail.copy()})

        if x == pack.get("processes"):
            print("The Final Available: ", pack.get("available"))
            break
        else:
            print("The Currently Available: ", pack.get("available"))

        # Checks in the resources
        for y in range(pack.get("resources")):
            print("\tChecking Need to Available: %s <- %s" % (pack.get("need")[x][y], pack.get("available")[y]))
            if pack.get("need")[x][y] > pack.get("available")[y]:
                # Break = True
                print("----Process %d Failed to Allocate----" % x)
                newavail = pack.get("available")
                missed.append(x)
                break
            else:
                newavail[y] = pack.get("available")[y] + pack.get("allocation")[x][y]
        order.append(x)

    # After the first time of checking for deadlocks, check even further in the length the checker missed
    if len(missed) > 0:
        index = 0
        while index < len(missed):
            value = missed[index]
            for x in order:
                if x == value:
                    order.remove(x)
            index += 1
        del index, value

        # The next loop for checking deadlocks;
        # determines if missed process is deadlocked or can be re-allocated later in program
        for x in missed:
            print("Checking Processes Again: %d" % x)
            pack.update({"available": newavail.copy()})
            print("Currently Available: ", pack.get("available"))

            # loops the y to the range of the pack resources to check for deadlocks
            for y in range(pack.get("resources")):
                print("\tChecking Need to Available: %s <- %s" % (pack.get("need")[x][y], pack.get("available")[y]))

                # if the need matrix is greater than available, deadlock is found
                if pack.get("need")[x][y] > pack.get("available")[y]:
                    print("Deadlock found at process ", x)
                    exit(1)
                # else, initialize the y of new available to available + allocation
                else:
                    newavail[y] = pack.get("available")[y] + pack.get("allocation")[x][y]

            order.append(x)  # appends x to the order as it finished checking it
            pack.update({"available": newavail.copy()})  # updates pack's available to a copy of the new available

    return pack, order, missed

# Calculates the need
def cNeed(arr):
    need = [[]]
    max = arr[4]
    allo = arr[3]
    for row in range(0, arr[0]):
        need.append([])
        for col in range(0, arr[1]):
            need[row].append(max[row][col] - allo[row][col])

    del need[len(need)-1]

    return need

# Prints out the data from the file
def printFile(arr):
    print("Number of Processes: ", arr[0])
    print("Number of Resource Types: ", arr[1])
    print("Available Resources: ", arr[2])

    if len(arr) == 6:
        print("Allocation Matrix:\t\t\t\tRequest Matrix:\t\t\tNeed Matrix:")
        for index in range(len(arr[3])):
            print('\t%s\t\t\t\t%s\t\t\t%s' % (arr[3][index], arr[4][index], arr[5][index]))
    else:
        print("Allocation Matrix:\t\t Request Matrix:")
        for index in range(len(arr[3])):
            print('\t%s\t\t\t\t%s' % (arr[3][index], arr[4][index]))

def main(file):
    matrix = [[]] # matrix to use for later
    line = 0 # checks each line of the file

    # Creates data from the file and turns it into data matrix so it could be used later
    dattrix = open(file, 'r')

    # goes through each line of the data matrix
    while line < dattrix.__sizeof__():
        # stores data into the matrix
        matrix[line] = dattrix.readline().strip()

        # checks for white space
        if matrix[line].count('') == 1:
            del matrix[line]
            break
        else:
            matrix.append([])
        line += 1

    # closes file
    dattrix.close()

    # deletes the line and file so that it can remove the binding of that name from the local or global namespace
    del line, dattrix

    # Rows to be split from each other
    for row in range(len(matrix)):
        matrix[row] = matrix[row].split()

    # Converts matrix[row][col] to numbers
    for row in range(len(matrix)):
        for col in range(len(matrix[row])):
            matrix[row][col] = int(matrix[row][col])

    del row, col

    # From the input data format; uses them as arrays to store information
    processes = matrix[0][0]    # Number of processes
    restypes = matrix[1][0]     # Number of Resource Type
    availsources = matrix[2]    # Available (unallocated) instances of each resource
    alloctrix = []              # Allocation matrix
    reqtrix = []                # Request matrix

    # for each x in the range of the processes, append this value into the allocation matrix
    for x in range(3, processes + 3):
        alloctrix.append(matrix[x])

    # for each x in the range of the processes, append this value into the request matrix
    for x in range(processes + 3, len(matrix)):
        reqtrix.append(matrix[x])

    del matrix  # deletes matrix as we have no more use of it and we stored its data into allocation and request

    # Makes a pack out of usable data
    pack = [processes, restypes, availsources, alloctrix, reqtrix]
    packed = {
        "processes": processes,
        "resources": restypes,
        "available": availsources.copy(),
        "allocation": alloctrix.copy(),
        "max": reqtrix.copy()
    }

    # Finishing touches, deletes data and creates the need matrix to use later
    del processes, restypes, availsources, alloctrix, reqtrix
    netrix = cNeed(pack)
    pack.append(netrix)
    printFile(pack)
    del pack
    packed.setdefault("need", netrix.copy())
    del netrix, x
    packed, order, missed = allocation(packed)
    del packed
    print("\nProcesses can be complete by running them in the order of: ", order)
    del order

    # Gives user another change to run another set of data, loops back to the program
    answer = input("Would you like to run another set of data? (Yes/No) \n")
    if answer.lower() == 'y' or answer.lower() == 'yes':
        file = input("Enter your new filename: ");
        main(file)
    else:
        exit(0)

if __name__ == "__main__":
    file = input("Enter filename: ");
    main(file)