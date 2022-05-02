#part 1 - Arithmetic

.globl main
.text

main:
	lw $s0, A # Load immediate value (15) from A
	lw $s1, B # Load immediate value (10) from B
	lw $s2, C  # Load immediate value (7) from C
	lw $s3, D  # Load immediate value (2) from D
	lw $s4, E # Load immediate value (18) from E
	lw $s5, F # Load immediate value (-3) from F
	lw $s6, Z  # Load immediate value (0) from Z
	add $t0, $s0, $s1 #Adds $s0 (15) and $s1 (10) together
	sub $t1, $s2, $s3 #Subtracts $s2 (7) by $s3 (2) 
	add $t2, $s4, $s5 #Adds $s4 (18) and $s5 (-3) together
	sub $t3, $s0, $s2 #Subtracts $s0 (15) by $s2 (7)
	add $t4, $t0, $t1 #Adds $t0 (25) and $t1 (5) together
	add $t5, $t4, $t2 #Adds $t4 (30) and $t2 (15)
	sub $s6, $t5, $t3 #Subtracts $t5 (45) by $t3 (8)

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
C : .word 7 #sets C to word integer 7
D : .word 2 #sets D to word integer 2
E : .word 18 #sets E to word integer 18
F : .word -3 #sets F to word integer -3
Z : .word 0 #sets Z to word integer 0
	



