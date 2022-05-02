#part 4 - Arrays

.globl main
.text

main:
	lw $s0, i 	#Loads value of i into s0
	la $s1, A 	#Loads start address of A into s1
	la $s2, B 	#Loads start address of B into s2
	lw $t2, C       # load C into some other register

For:
    bge $s0, 5, ForEnd        # Branch if i >= 5, go to ForEnd
    lw $t1,($s2)              #$t1=B[i]
    add $t1, $t1, $t2         #$t1=B[i]+C
    sw $t1,($s1)              #A[i]=B[i]+C
    addi $s1, $s1,4           #next element A[i+1]
    addi $s2, $s2,4           #next element B[i+1]
    addi $s0, $s0, 1          #Add immediate value 1 to i (i++)
    j For                     #Goes back on for

ForEnd:
    addi $s0, $s0, -1         #Add immediate value -1 to i (i--)
    addi $s1, $s1,-4          #previous element A[i-1]
    addi $s2, $s2,-4          #previous element B[i-1]
	
While:
    blt $s0, 0, While         #Branch While when (i < 0)
    lw $t2,($s1)              #$t0=A[i]
    mul $t3, $t2, 2           #$t3 = A[i] * 2
    sw $t3,($s1)              #A[i]=A[i]*2
    addi $s1, $s1,-4          #previous element A[i-1]
    addi $s2, $s2,-4          #previous element B[i-1]
    addi $s0, $s0, -1         #Add immediate value -1 to i (i--)
    j While                   #Goes back on While

WhileEnd:
print:                     
    li $s0, 0                 #i=0
    la $s1, A                 #$s1=A[0]
	
loopPrint:
    bge $s0, $t4, WhileEnd    # if i >=5 goto WhileEnd
    lw $a0, ($s1)             #  $a0 = A[i]
    li $v0, 1                 #function print integers          
    syscall
    la $a0, space             #print separator (1 space)
    li $v0, 4                 #function print strings               
    syscall
    addi $s1, $s1, 4          #next element A[i+1]
    addi $s0, $s0, 1          #i++
    b loopPrint

END:
    # Exit the program by means of a syscall.
	# There are many syscalls - pick the desired one
	# by placing its code in $v0. The code for exit is "10"
	li $v0, 10 # Sets $v0 to "10" to select exit syscall
	syscall # Exit
	
	# All memory structures are placed after the
	# .data assembler directive
	.data

	# The .word assembler directive reserves space
	# in memory for a single 4-byte word (or multiple 4-byte words)
	# and assigns that memory location an initial value
	# (or a comma separated list of initial values)
	
	A: .word 0:5 #Loads A with word integer 0:5
	B: .word 1 ,2 ,3 ,4 ,5 #Initializes memory with the integers 1, 2, 3, 4, 5 with the label B at the initial memory address
	C: .word 12 #Loads C with word integer 12
	i: .word 0 #Initial value of 1
	


