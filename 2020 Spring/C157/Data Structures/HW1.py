import time
import csv

#Uses the dict data structure
def dict_struc():
    t0 = time.time()

    #Uses the text file to create keys to look up the dictionary I created
    with open("queries.txt", "r") as lookupfile:
        lookuplist = lookupfile.read().splitlines()
    lookupfile.close()

    #Saves the csv file into a dictionary data sturcture
    keydict = {}
    pop = open("populations.csv", "r")
    for line in pop:
        it = line.rstrip("n").split(",")
        key, values = it[0], it[1:]
        keydict[key] = values
    pop.close()

    for key in lookuplist:
        if key in keydict:
            print("City/County: ", key, ", Population: ", ','.join(keydict[key]))
    t1 = time.time()
    total = t1 - t0
    print("Time for dictionary structure: ", total)

#Uses the array list data structure
def array_list_struc():
    t0 = time.time()

    place = []
    pop = []

    #Reads and saves the content of the codes into array lists
    reader = csv.reader(open("populations.csv"))
    for row in reader:
        place.append(row[0])
        pop.append(row[1])

    lookFile = open("queries.txt", "r")
    look = lookFile.readlines()
    lookFile.close()

    numCou = 0
    head = []

    for i in look:
        let = list(look[numCou])
        let.pop()
        head.append("".join(let))
        plIndex= place.index((head[numCou]))
        print("City/County: ", head[numCou], ", Population: ",pop[plIndex])
        numCou += 1
    t1 = time.time()
    total = t1 - t0
    print("Time for array data structure: ", total)

def main():
    dict_struc()
    array_list_struc()

if __name__ == "__main__":
        main()

#Answers for the conceptual questions
#7. The first data structure (dictionary) runs in less than a second (estimated time around 0.1306 seconds) while the second one (array list) runs in slighlty more than a second (estimated time around 1.472 seconds)
#   If I were to make a copy of queries.txt that contains 100 place names in it, they both run in less than a second (estimated for 0.045 for the first one and 0.059 for the second). However, the first one still runs faster.
#8.
#   a. If you want to store a user’s history of visited webpages for the purpose of implementing a “Back” button, use a doubly-linked list with a reference to the current page of the user and use that reference to mave about the historu.
#       For example, when the user vists a page by clicking a link, that page will be added to the current page reference and updated to point to the new element.
#   b. If you want to storing filenames of photos that should be viewable in chronological or random order, use a dictionary because you need to store both the filename and the date it was taken/created/modified. Using a dictionaryallows you to store a key and value pair, and you can sort it in a for loop too.
#   c. If you want to store a to-do list of tasks based on the urgency with which they need to be completed, use a mab to create something like map <date, vector <string>> to store the date/ time the task is needed to be done and the task that is needed to be done.
#   d. If you want to store a sequence of printing jobs that have been sent to a shared printer, use queue because it will store elements in a sequential manner; in this case the sequence of printing jobs.
#   e. If you want to store a mapping of user IDs to password hashes for validating login attempts, use a haash table to uniquely identify user IDs and store it to its key (in this case, the password.


