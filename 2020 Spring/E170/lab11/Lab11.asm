#Lab 11

.globl main
.text

random_in_range:
	addi $sp,$sp,-8     # allocates space for saving registers in the stack
	sw $ra,0($sp)       # saves return address register in the stack
	sw $s0,4($sp)       # saves $s0 register in the stack
	sub $s0,$a1,$a0     # uint32_t range = high-low+1;
	addi $s0,$s0,1      # $s0 holds the range 
	jal get_random      # uint32_t rand_num = get_random();
	divu $v0,$s0        # return (rand_num % range) + low;
	mfhi $v0            # gets rand_num % range
	add $v0,$v0,$a0     # adds low ($v0 = $v0 + $a0)
	lw $ra,0($sp)       # restore contents of $ra from the stack
	lw $s0,4($sp)       # restore $s0 register from the stack
	addi $sp,$sp,8      # restores stack pointer
	jr $ra		    # transfers control back to the caller			
	
get_random:

	#m_z = 36969 * (m_z & 65535) + (m_z >> 16);
	li $t0,36969        # $t0 is loaded with immediate value 36969
	la $t1,m_z          # $t1 is loaded with address of m_z
	lw $t2,($t1)        # $t2 is loaded with the value of $t1, or m_z
	andi $t3,$t2,65535  # m_z & 65535
	multu $t0,$t3       # 36969 * (m_z & 65535)
	mflo $t0            # $t0 has the multiplication result moved into it
	srl $t3,$t2,16      # m_z >> 16
	addu $t0,$t0,$t3    # 36969 * (m_z & 65535) + (m_z >> 16);
	sw $t0,($t1)        # result is saved in m_z
	
	#m_w = 18000 * (m_w & 65535) + (m_w >> 16);
	li $t0,18000        # $t0 is loaded with immediate value 1800
	la $t1,m_w          # $t1 is loaded with address of m_w
	lw $t2,($t1)        # $t2 is loaded with the value of $t1 or m_w
	andi $t3,$t2,65535  # m_w & 65535
	multu $t0,$t3       # 18000 * (m_w & 65535)
	mflo $t0            # $t0 has the multiplication result moved into it
	srl $t3,$t2,16      # m_w >> 16
	addu $t0,$t0,$t3    # 18000 * (m_w & 65535) + (m_w >> 16);
	sw $t0,($t1)        # result is saved in m_w
	la $t0,m_z          # get address of m_z in $t0
	lw $t0,($t0)        # t0 = m_z
	la $t1,m_w          # get address of m_w in $t1
	lw $t1,($t1)        # t1 = m_w
	
	# result = (m_z << 16) + m_w;
	sll $t0,$t0,16      # m_z << 16
	addu $t0,$t0,$t1    # (m_z << 16) + m_w
	move $v0,$t0        # returns the result;
	jr $ra		    # transfers control back to the caller
	
main:
	li $s0,0            # $s0 will be used as i
	la $s1,0            # $s1 will be n1
	la $s2,0	    # $s2 will be n2

for:               		#   for(int i=0; i<10; i++)
	bge $s0,10,endfor 	#{

	li $a0,1
	li $a1,10000
	jal random_in_range #  n1 = random_in_range(1,100000);
	move $t4,$v0        #saves value in $t0 for n1 to print for later

	li $a0,1
	li $a1,10000
	jal random_in_range #  n2 = random_in_range(1,100000);
	move $t1,$v0      #saves value in $t0 for n2 to print for later

	
	la $a0, msg1	    #loads address of msg1 to print
	li $v0,4            # use syscall number 4, print string
	syscall             # printf("\n G.C.D of "
	
	move $a0, $t4       # load current value of n1 in a0
	li $v0,1            # use syscall number 1, print number
	syscall 	    # prints n1
	
	la $a0, msg2	    #loads address of msg2 to print
	li $v0,4            # use syscall number 4, print string
	syscall             # " and "
	
	move $a0, $t1       # load current value of n2 in a0
	li $v0,1            # use syscall number 1, print number
	syscall 	    # prints n2
	
	la $a0, msg3	    #loads address of msg3 to print
	li $v0,4            # use syscall number 4, print string
	syscall             # " is "
	
	move $a0,$t4  	    # loads value of n1 into $a0
   	move $a1,$t1 	    # loads value of n1 into $a0
   	jal GCD 	    # gcd(n1,n2)

    	add $a0,$v0,$zero   
    	li $v0,1
    	syscall 	    # prints gcd(n1,n2)

	addi $s0,$s0,1      # i++
	
	b for	            #}

endfor:
# Exit the program by means of a syscall.
# There are many syscalls - pick the desired one
# by placing its code in $v0. The code for exit is "10"
	li $v0, 10 # Sets $v0 to "10" to select exit syscall
	syscall #Exit
	
GCD:
    addi $sp, $sp, -12
    sw $ra, 0($sp) # saves function into stack
    sw $s0, 4($sp) # saves value $s0 into stack 
    sw $s1, 8($sp) # saves value $s1 into stack 

    add $s0, $a0, $zero # s0 = a0
    add $s1, $a1, $zero # s1 = a1 

    addi $t1, $zero, 0 # $t1 = 0
    beq $s1, $t1, return # if s1 == 0 return

    add $a0, $zero, $s1 # $a0 = $s1
    div $s0, $s1 # n1/n2
    mfhi $a1 # remainder of n1/n2 or n1%n2

    jal GCD #recurses the GCD function

exitGCD:
    lw $ra, 0 ($sp)     # read registers from stack
    lw $s0, 4 ($sp)     # read registers from stack
    lw $s1, 8 ($sp)     # read registers from stack
    addi $sp,$sp , 12   # bring back stack pointer
    jr $ra		# transfers control back to the caller

return:
    add $v0, $zero, $s0 # return $v0 = $s0 ( n1)
    j exitGCD		#jumps into exitGCD
	
# All memory structures are placed after the
# .data assembler directive
.data

# The .word assembler directive reserves space
# in memory for a single 4-byte word (or multiple 4-byte words)
# and assigns that memory location an initial value
# (or a comma separated list of initial values)
m_w: .word 50000
m_z: .word 60000
msg1: .asciiz "\n Sorted G.C.D of "
msg2: .asciiz " and "
msg3: .asciiz " is "
