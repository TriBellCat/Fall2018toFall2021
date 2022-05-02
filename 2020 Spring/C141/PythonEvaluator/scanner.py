# Phase 1.2: Scanner for Limp
# Trinity Caitlin Atayan Belen
# Comp 141: Programming Langauages

import re
import sys
import keyword

#passes the input line to the scanner
def scanner (read, writeToken):
    identifier = re.compile(r"[A-Za-z_][A-Za-z_0-9]*")
    digit = re.compile(r"[0-9]+")
    symbol = re.compile("\\+|\\-|\\*|\\/|\\(|\\)|\\;|\\:=")
    unusedSymb = re.compile("[\\@|\\!|\\#|\\$|\\%|\\^|\\&|\\<|\\>|\\?|\\}|\\{|\\~]")
    #keyWord = ["if","then","else","endif","while","do","endwhile","skip"]
    #zkeyWord = re.compile("if|then|else|endif|while|do|endwhile|skip")
    #Finds all identifier, digit, and symbol tokens in the line, also splits based on whitespace
    identReg = [x.strip() for x in re.findall(identifier, read) if x]
    symReg = [x.strip() for x in re.findall(symbol, read) if x]
    #keyReg = [x.strip() for x in re.findall(keyWord, read) if x]
    digReg = re.findall(digit, read)
    unusedSymbReg = [x.strip() for x in re.findall(unusedSymb, read) if x]

    c = []
    stri = []
    foundToken = []
    newString = []
    newWord = ""
    breaks = False
    i = 0

    for word in read.split():
        length = len(word)

        #if words fit the criteria right away, they go here since they don't need to be checked for every letter
        if word in digReg:
            print(word, " :NUMBER")
            writeToken.write("{}\n".format(word + " :NUMBER"))
        elif word in symReg:
            print(word, " :SYMBOL")
            writeToken.write("{}\n".format(word + " :SYMBOL"))
        elif word == 'if' or word =='then' or word =='else' or word =='endif' or word == 'endwhile' or word == 'while' or word == 'do' or word == 'skip':
            print(word, " :KEYWORD")
            writeToken.write("{}\n".format(word + " :KEYWORD"))
        elif word in unusedSymbReg:
            print("ERROR READING ", word)
            writeToken.write("{}\n".format("ERROR READING " + word))
            break
        #If a word don't automatically, search through the letters of the word and split it as soon as possible and apply principle of longest string
        else:
            for letter in word: #reads each letter of the word
                c = [letter]
                newString.extend(stri)
                stri.extend(c)

                newWord =''.join(stri) #current word
                newWord2 = ''.join(newString) #old word
                
                if re.match(digit, newWord):
                    if newWord2.isdigit() or (newWord.isdigit() and newWord in digReg):
                        print(newWord, " :NUMBER")
                        writeToken.write("{}\n".format(newWord + " :NUMBER"))
                        newString.clear()
                        stri.clear()

                elif newWord in identReg:
                    print(newWord, " :IDENTIFIER")
                    writeToken.write("{}\n".format(newWord + " :IDENTIFIER"))
                    newString.clear()
                    stri.clear()

                elif newWord in symReg:
                    print(newWord, " :SYMBOL")
                    writeToken.write("{}\n".format(newWord + " :SYMBOL"))
                    newString.clear()
                    stri.clear()

                elif newWord in unusedSymbReg:
                    print("ERROR READING ", newWord)
                    writeToken.write("{}\n".format("ERROR READING " + newWord))
                    breaks = True
                    break

            if (breaks is True):
                break

def testDriver ():
    with open(sys.argv[1], "r") as infile, open(sys.argv[2], 'w') as outPut:
        line = infile.readline().strip() #Reads the lines and strips the white spaces
        print("LINE: " + line)
        outPut.write("LINE: " + line + '\n')

        scanner(line, outPut)
        count = 0

        while line:
            line = infile.readline().strip()
            print("LINE: " + line)
            outPut.write("LINE: " + line + '\n')
            scanner(line, outPut)
            count += 1

    infile.close()
    outPut.close()

if __name__ == "__main__":
        testDriver()