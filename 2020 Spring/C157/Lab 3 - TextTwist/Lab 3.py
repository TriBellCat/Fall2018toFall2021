import random

# selects a random word from the file
def six_letters ():
    with open("sixLetters.txt", "r") as word:
        readWord = word.readlines()
        randomWord = random.choice(readWord)
    word.close()
    readWord = randomWord

    #Scrambles the words
    randoList = list(randomWord)
    randoList.pop(-1)
    random.shuffle(randoList)
    rando = "".join(randoList)
    return rando

# finds words that can be made from the letters of the randomly selected word
def find_word(userInput, testCheck, dicContents):
    userInput = list(userInput)
    userInput.append("\n")
    userInput = "".join(userInput)

    numLetters = 0

    #if the test_word function returns true and the user guesses a word that's in the dictionary, it will remove that word from the dictionary list
    if (testCheck):
        if userInput in dicContents:
            for i in dicContents:
                if (userInput == dicContents[numLetters]):
                    word = dicContents[numLetters]
                    dicContents.remove(word)
                numLetters = numLetters + 1

#counts the amount of words the user has left
def count(chosenWord, dicContents):
    num = 0
    numWord = 0

    #searches through the dictionary contents
    for i in dicContents:
        word = dicContents[num]
        letters = list(word)
        letters.pop(-1)
        word = "".join(letters)
        userChoice = test_word(word, list(chosenWord))

        #if the userchoice is true, adds 1 to word count
        if (userChoice):
            numWord += 1
        num = num +1

        list(word).clear() #clears the list
    return numWord

"""
Function: test_word
Description: takes a word and a list of letters and sees whether the word can be made from the list of letters, e.g.
             "apple" can be made from ['p', 'a', 'p', 'e', 'l'] but not from ['p', 'l', 'e', 'a'] because in the latter
             case there is only one "p".
Parameters: word is a string containing the word to be checked, letters is a list of letters available to try making
            the word
Returns: boolean -- True if word can be made from letters, False otherwise
"""
def test_word(word, letters):
    # make a deep copy of the list of letters, so I can overwrite parts of the copy
    letter_list = letters[:]

    # make sure that letters is a list and the user didn't pass in a string, instead.
    if type(letters) != list:
        letter_list = list(letters)

    # loop through each letter in the word
    for letter in word:
        i = 0
        # find first instance of that letter in the list of letters
        while i < len(letter_list):
            # if letter is found, overwrite it with asterisk so it cannot be reused
            if letter_list[i] == letter:
                letter_list[i] = '*'
                break
            i += 1
        # if letter wasn't found, not possible to make word from list of letters
        if i == len(letter_list):
            return False
    # if successfully found all letters in word, return True
    return True


def main():
    # iterates through the words in the text file
    with open("dictionary.txt","r") as iteration:
        for line in iteration:
            dicContents = iteration.readlines()
    iteration.close()

    randomLetters = six_letters()
    numLeft = 2 #another interger for the count function
    print("Your letters are:" + randomLetters)
    while (numLeft > 1):
        numLeft = count(randomLetters, dicContents)
        print(numLeft, " word left. Enter your guess:  ")
        userInput = input()
        userInput = userInput.lower()

        #If user inputs qqq, they exit the game
        if (userInput == "qqq"):
            break

        testCheck = test_word(userInput, list(randomLetters))
        find_word(userInput, testCheck, dicContents)

        if (numLeft == 1):
            print("Congratulations! You won the game!")

    print("See you later!") #Message when user exits the game

if __name__ == "__main__":
    main()