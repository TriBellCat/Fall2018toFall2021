#Lab 8 - A Paging Simulator
#Trinity Caitlin Atayan Belen

from os import listdir, remove
"""
The classes that the program will get information from
"""
#Class for the executable file
class Program:
    name = None     #The name/key for the exe
    size = None     #The size of exe
    pages = None    #Exe's user input size
    table = {}      #The table of pages for exe

#Class for the memory
class Memory:
    mem = 524288    #512KB is the total number of bytes
    size = 512      #The size per frame in the total number of bytes
    frames = 1024   #Mimics frames in physical memory
    frametable = {}      #Table for frames
    programs = {}   #The list of executable files
    numProgs = 0    #The number of programs/exes in the memory

#Class for the frame
class Frame:
    index = None    #Number for the frame
    occupied = 0    #How many frames are used
    total = None    #The size (Bytes)
    free = True     #Checks whether or not the frame is free or occupied, true by default
    program = None  #The program that holds the frame

    #Prints frame for information later
    def fraprint(self):
        print("Frame #:", self.index)
        print(self.size, "bytes")

        if self.free:
            print("Currently free.")
        elif self.free is False:
            print("Currently occupied")

        print("Program holding frame: ", self.program)

"""
The function for the memory.
"""
#Displays a list of the information for each frame allocated in the memory file
def memorydump():
    print("Total Memory: %d\nFrame Sizes: %d\nNumber of Frames: %s" % (Memory.mem, Memory.size, Memory.frames))
    for x in range(Memory.frames):
        if Memory.frametable.get(x).free is not True:
            print(Frame.fraprint(Memory.frametable.get(x)))

#Loads an “executable” file into appropriate frames in the memory file
def load():
    pages = int(input("Input number of pages from the exe: "))
    index = 0
    page_table = []

    #Prevents loading if the number of free frames is less than the number of exe file pages
    if pages * 1024 > int(Memory.mem):
        print("File needs more memory than currently available, please try again!")
        load()
    #Else, saves page table information, and updates the free-frame list accordingly
    else:
        #Sets the program information and then updates the memory's information about the memory
        program = Program()
        program.pages = pages
        program.size = (1024 * pages)
        program.name = "Program " + str((len(Memory.programs) + 1))
        Memory.programs.update({program.name: program})
        Memory.numProgs += 1

        #Sets up a temporary value that contains the program size to use later
        temp = program.size

        x = 0
        #Updates the free-frame list throughout the while loop
        while temp > 0 and x != int(Memory.frames):
            frame = Memory.frametable.get(x)
            #If the temp value minus the number of bytes is less than 0 and if the frame is free, then set occupied to temp and also sets up the frame's program info
            if temp - 512 < 0:
                if frame.free is True:
                    frame.occupied = temp
                    frame.free = False
                    frame.program = program.name

                    Memory.frametable.update({x: frame})
                    page_table.append([index, x])
                    index += 1

                    temp = temp - frame.occupied
            #Else, do almost the same thing, but the value of the iterator of the memory's frame table is saved to frame
            else:
                if frame.free is True:
                    frame = Memory.frametable.get(x)
                    frame.free = False
                    frame.program = program.name
                    frame.occupied = 512

                    Memory.frametable.update({x: frame})
                    page_table.append([index, x])
                    index += 1

                    temp = temp - frame.occupied
            x += 1
        #Then save the memory to use later
        memorysave()

#Reads the memory from the file
def memoryread():
    print("Reading the memory file...")
    with open('memory.txt', 'r') as file:
        #After opening file, save lines to memory
        Memory.mem = int(file.readline().strip())
        Memory.size = int(file.readline().strip())
        Memory.frames = int(file.readline().strip())

        buffer = []
        #Ierates in the range of frames
        for x in range(Memory.frames):
            #Appends files information into the buffer and then updates the memory's frame table
            buffer.append(file.readline().strip().split(' '))
            Memory.frametable.update({buffer[x][0]: buffer[x][1]})

            #Sets the frame information
            frame = Frame()
            frame.index = x
            frame.size = buffer[x][1]
            frame.free = buffer[x][2]
            frame.program = buffer[x][3]

        file.close()

#Function to write memory information into the file
def memoryinitialize():
    print("Initializing the memory file...")
    file = open('memory.txt', 'w')

    #Writes memory to file
    file.write('%d\n%d\n%d\n%d\n%s\n' % (Memory.mem, Memory.size, Memory.frames, Memory.numProgs, Memory.programs))

    #Iterates at the start of 0 and stops when it reaches the number of frames
    for x in range(0, Memory.frames):
        #Initializes frame information
        frame = Frame()
        frame.index = x
        frame.size = Memory.size
        frame.free = True

        #Then the memory's table frame gets updated as x iterates
        Memory.frametable.update({x: frame})

        #Writes frame information to file
        file.write('%d %d %s %s\n' % (frame.index, frame.size, frame.free, frame.program))
    file.close()

    return Memory

#Function to save current memory info to the text file to use later
def memorysave():
    print("Saving memory file...")
    file = open('memory.txt', 'w')
    file.write('%d\n%d\n%d\n%d\n%s\n' % (Memory.mem, Memory.size, Memory.frames, Memory.numProgs, Memory.programs))

    #Iterates through the frames to get the frame table info at x to write info to file
    for x in range(0, Memory.frames):
        frame = Memory.frametable.get(x)
        file.write('%d %d %s %s\n' % (frame.index, frame.size, frame.free, frame.program))
    file.close()

#Frees frames from programs that user named in their input
def memoryfree(name):
    #Iterates through the frames to check if the frame table at x is the named program
    for x in range(0, Memory.frames):
        if Memory.frametable.get(x).program == name:
            #Frees the frames and then sets the program to none
            Memory.frametable.get(x).free = True
            Memory.frametable.get(x).program = None

            #Saves the name to temp and then deletes temp, and then the number of programs in memory goes down by 1
            temp = Memory.programs.get(name)
            del temp
            Memory.numProgs -= 1

#List all frames of the programs that user named using a for loop and checks if it's the named program, then using the frame print function from the Frame class
def programlist(name):
    for x in range(0, Memory.frames):
        if Memory.frametable.get(x).program == name:
            Frame.fraprint(Memory.frametable.get(x))

"""
The main function, a menu in which the user input the action that they want the program to do.
"""
def main():
    memoryinitialize()
    while True:
        print("What would you like to do?")
        print("0. Load||1. Initialize||2. Dump||3. Reset||4. Free||5. List||6. Exit")
        userinput = input()

        if userinput == '0':
            load()
        elif userinput == '1':
            memoryinitialize()
        elif userinput == '2':
            memorydump()
        elif userinput == '3' and 'memory.txt' in listdir():
            remove('memory.txt')
            Memory.numProgs = 0
            Memory.programs = {}
            memoryinitialize()
        elif userinput == '4':
            prog = input("Free program name: ")
            memoryfree(prog)
        elif userinput == '5':
            prog = input("List program name: ")
            programlist(prog)
        elif userinput == '6':
            memorysave()
            exit(0)
        else:
            print("A wrong input! Please choose one of the options this time.")
            main()

if __name__ == "__main__":
    main()