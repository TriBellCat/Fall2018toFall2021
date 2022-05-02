#Part 3 - Loops

.globl main
.text

main:
	lw $t0, Z #sets $t0 to word Z
	lw $t1, i #sets $t0 to word i
		
while:
	bgt $t1,20, do #if $t1 is greater than 20, go to do
	addi $t0, $t0, 1 #Changes $t0 by adding 1 to it
	addi $t1, $t1, 1 #Changes $t1 by adding 1 to it
	j while #Recurses while
do:
	addi $t0, $t0, 1 #Changes $t0 by adding 1 to it
	bge $t0, 100, while2 #if $t0 is greater than or equal to 100, go to while2
	j do #Recurses do
while2:
	ble $t1, 0, finish #If $t1 is less than or equal to 0, go to done
	sub $t0, $t0, 1 #Changes $t0 by subtracting 1 to it
	sub $t1, $t1, 1 #Changes $t1 by subtracting 1 to it
	j while2 #Recurses while2	
finish:
	sw $t0, Z #stores $t0 to word Z
	sw $t1 i #stores $t1 to word i

	# Exit the program by means of a syscall.
	# There are many syscalls - pick the desired one
	# by placing its code in $v0. The code for exit is "10"
	li $v0, 10 # Sets $v0 to "10" to select exit syscall
	syscall #Exit
	
	
# All memory structures are placed after the
# .data assembler directive
.data

# The .word assembler directive reserves space
# in memory for a single 4-byte word (or multiple 4-byte words)
# and assigns that memory location an initial value
# (or a comma separated list of initial values)
Z : .word 2 #sets Z to word integer 1
i : .word 0 #sets Z to word integer 0
