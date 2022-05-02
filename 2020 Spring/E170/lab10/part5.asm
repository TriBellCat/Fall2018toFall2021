.globl main
.text   
main:
   la $s0, string  #$s0 : base address string, loads address to string
   addi $s1, $zero, 0 #$s1 : i
   addi $s2, $zero, 0 #*result = null  

   #get input from user
   li $v0 ,8 # takes input
   la $a0, string # load byte space into address
   li $a1, 256 #allot the byte space for string
   move $t0, $v0 # # syscall results returned in $v0
   syscall
  
   addi $t9, $s0, $s1 # &string[i]
   lb $t8,0($t9) #t8 = string [i]

while: beq $t8 , 0, outsidewhile # if string[i] == '\0'
   beq $t8, 101, body # if string i == 'e'
   add $s1, $s1, 1 #i++
   j while #goes back to while

body:
   add $t2, $t9, $zero #result = &string[i];   
   j outsidewhile #goes to outside of the while loop

outsidewhile :
   beq $s2, 0, printaddress # if(result != NULL)
   # leads to printf("No match found\n");
   li $v0,4
   la $a0, msg2      
   li $v0,4
   la $a0, newline 
 
printaddress:
   #printf("First match at address %d\n", result);

   li $v0,4
   la $a0, msg
   li $v0,4
   la $a0, $t2 # print result
   #printf("The matching character is %c\n", *result);      
   li $v0,4
   la $a0, msg1
   li $v0,4
   la $a0, $s2 #    print *result  
li $v0, 10
syscall

.data
string: .space 256
msg: .asciiz "First match at address "
msg1: .asciiz "The matching character is "
msg2: .asciiz "No match found"
endstring: .asciiz "\0"
newline: .asciiz "\n"
