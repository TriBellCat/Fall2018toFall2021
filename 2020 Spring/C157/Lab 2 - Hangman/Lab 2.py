import random

def hangedman():
    with open("capitals.txt","r") as capital:
        ans = capital.readlines()
        randomCap = random.choice(ans)
    capital.close()
    ans =randomCap

    ansList = [] #List for the right letters
    userList = [] #A list to check and compare lists
    guessList = [] #List for the letters the user gussed

    #Hides word with underscore and stores letters in lists, then prints it out later
    for i in ans:
        if i >= 'A' and i <= 'Z':
            ansList.append("_")
            userList.append("_")
        else:
            ansList.append(i)
            userList.append(i)

    print("".join(ansList))

    #Will not end if the user has not guessed all the letters
    while ("".join(ansList) != ans):
        userAns = input("Enter a letter: ")
        userAns = userAns.capitalize()

        if userAns in guessList:
            print("You already used the letter " + userAns)

        for i in range(len(ans)):
            if ans[i] == userAns:
                ansList[i] = userAns
                guessList.append(userAns)
            else:
                userList[i] = ansList[i]

        if ("".join(userList) == "".join(ansList)):
                print("Either " + userAns + " is not in the answer or you already used the right letter")
                guessList.append(userAns)

        else:
            print(userAns + " is in the answer")

        print("".join(ansList))

    print("Congrats! You won the game!")

#auto-start code
if __name__ == "__main__":
    hangedman()