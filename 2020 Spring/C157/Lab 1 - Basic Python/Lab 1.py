"Lab 1 Program written by Trinity Caitlin Atayan Belen"
def greeting():
    print ("Hello world!")

def swap():
    x, y = 'a', 23.55
    print('x is the value, type: {}'.format(x), type(x))
    print('y is the value, type: {}'.format(y), type(y))
    x, y = y, x
    print('x became the value, type: {}'.format(x), type(x))
    print('y became the value, type: {}'.format(y), type(y))

def madlib():
    adjective = input("Give me an adjective!")
    noun = input("Give me a noun!")
    verb = input("Give me a verb!")
    print("Yesterday, you went to the " + adjective + " " + "park")
    print("You saw a " + noun)
    print("You " + verb + " back to home")

def menu():
    x = "1. Chocolate Crepes"
    y = "2. Vanilla Waffles"
    z = "3. Strawberry Ice Cream"
    
    print("Here's the dessert menu:")
    print(x)
    print(y)
    print(z)

    choice = input("What will you choose? (Please write the number of your choice!)")
    if choice == '1':
        return print(x)

    elif choice == '2':
        return print(y)

    elif choice == '3':
        return print(z)

    else:
        print("Invalid input! Try again!")
        menu()

def factcheck():
    answer = input("What is the color of the sky when it's bright and sunny? (Just write one color!)\n")
    correct = "blue"
    if answer == correct.lower() or answer == correct.upper() or answer == "Blue":
        print("You got the right answer!")

    else:
        print("You got that wrong!")

def listslice():
    list = [1, 2, 3, 4, 5, 6, 7, "Hi"]
    print(list[0])
    print(list[-1])
    print(list[slice(3)])
    print(list[3:6])
    print(list[1:8])
    print(list[0:6])

def vowelreplacer():
    s = "jumanji"

    for char in s:
        if char in "aeiou":
            s = s.replace(char, '*')

    print (s)

def main():
    greeting()
    swap()
    madlib()
    menu()
    factcheck()
    listslice()
    vowelreplacer()

#auto-start code
if __name__ == "__main__":
    main()

