#part 2 - Branches

.globl main
.text

main: #starting point
	lw $t0, A #loads word A to $t0
	lw $t1, B #loads word B to $t1
	lw $t2, C #loads word C to $t2
	lw $t3, Z #loads word Z to $t3
	
	bgt $t0,$t1,zOne #if $t0 is greater than $t1 (A>B), go to zOne
	blt $t2,5,zOne #if $t2 is less than 5 (C < 5), go to zOne
	
	bgt $t0, $t1, elif #else if $t0 is greater than $t1 (A>B), go to elif
	j zThree #else, go to else
		
elif: #tries to recreate: else if((A > B) && ((C+1) == 7))
	addi $t2, $t2, 1 # changes $t2 by adding 1 to $t2 (C = C+1)
	beq $t2, 7, zTwo #If $t2 is equal to 7, go to zTwo
	j zThree #go to else

zOne:
	li $t3,1 #sets $t3 = 1
	j switch # go to switch

zTwo:
	li $t3,2 #sets $t3 = 2
	j switch # go to switch
	
zThree:
	li $t3,3 #sets $t3 = 3
	j switch # go to switch
	
switch: 
	beq $t3, 1, c1 #if $t3 = 1, go to case 1
	beq $t3, 2, c2 #if $t3 = 2, go to case 2
	beq $t3, 3, c3 #if $t3 = 3, go to case 3
	j c3 # goes to c3
c1:
	li $t3,-1 #sets $t3 = -1
	j finish # go to finish
c2:
	sub $t3, $t3, 2 #Changes and subtracts $t3 by 2
	j finish  # go to finish
c3:
	li $t3,0 #sets $t3 = 0
	j finish # go to finish
finish:
	sw $t3, Z #stores t3 in Z
	
	

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
A : .word 10 #sets A to word integer 10
B : .word 15 #sets B to word integer 15
C : .word 6 #sets C to word integer 6
Z : .word 0 #sets Z to word integer 0
