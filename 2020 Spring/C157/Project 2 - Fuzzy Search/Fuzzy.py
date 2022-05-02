#Trinity Belen
#Comp157
#Project 2: Fuzzy Search

import os
import time

#Function for the fuzzy search
def search(phrase, text):
    mismatch = {}
    removed = []
    num = 0
    together = "".join(phrase)
    found = False
    pop = False

    while found is False:
        for i in range(0, len(phrase)):
            shift = max(1, len(phrase) - i - 1)
            mismatch[phrase[i]] = shift

        for i in range(0, len(text) - len(phrase)):
            skip = 0
            for j in range(len(phrase) - 1, -1, -1):
                if (phrase[j]) != text[i + j]:
                    if text[i + j] not in mismatch:
                        skip = len(phrase)
                    elif mismatch[text[i + j]] is not None:
                        skip = mismatch[text[i + j]]
                    else:
                        skip = len(phrase)
            if skip == 0:
                found = True
                if len(phrase) == 1:
                    print("Found at", i)
                else:
                    print("Found at", i, "to", i + len(phrase) - 1)
                num += 1
            i += skip
        if found:
            print("Times found:", num)

        if found == False:
            for i in range(0, len(phrase)):
                letter_found = False
                for j in range(0, len(text)):
                    if phrase[i] == text[j]:
                        letter_found = True

                if letter_found == False:
                    print("Not found", phrase[i])
                    removed.append(phrase.pop(i))
                    print("removed", removed)
                    pop = True
                    break

        if found == False:
            if pop == False:
                phrase.pop(0)
            print("_______Deletions_______")
            together = "".join(phrase)
            print(together)
    end_time = time.time()
    print("End time: %d", end_time)


def main():
    start_time = time.time() #times the program
    print("Start time: %d", start_time)
    data = [] #saves file data
    phrase = input("Enter the phrase you want to find: ")
    with open(input("Enter your file (make sure you also write .extension): "), 'r') as input_file:
        data = input_file.read()
        text = list(data)
        search(phrase, text)
        input_file.close()

if __name__ == "__main__":
    main()

