# TA Virtual Machine documentation
* TAVM is 64bits


## Instruction format :
* 1 instruction is 11 bytes :
	* First byte : opcode
	* Second byte : condition and 1st register
	* Second byte : 2nd and 3rd registers
	* Third to 10th bytes : variable

## Registers
* R0/IP : instruction pointer (0x0)
* R1/SP : stack pointer (0x1)
* R2/CP : configuration pointer (0x2) (*see lower for more informations*)
* R3/ER : error register (0x3)
* R4 : condition register (0x4) (*see lower for more informations*)
* R5 to R15 : generic registers (0x5 to 0xF)

## Condition bits :
* The condition bits are the first 4 bits of the 2nd byte of an instruction. If thir value is different of 0x0, the instruction will only be executed if R4 (condition register) is himself different of 0.

## Instruction set :

### 0x0X : data management 
* 0x00 : set (if [register 3]==0 : set value stored in memory at [variable] to [register1] --- if [register 3]!=0 : set value stored in memory at [register 2] to [register 1])
* 0x01 : load (if [register 3]==0 : load value stored in memory at [variable] in [register1] --- if [register 3]!=0 : load the value stored in memory at [register 2] in [register 1])
* 0x02 : move (set [register 1] to [register 2])
* 0x03 : define (set [register 1] to [variable])
* 0x04 : push (push [register 1] on the stack)
* 0x04 : pop (pop the first value on the stack in [register 1])

### 0x1X : bit-wise operator
* 0x10 : left shift (set [register 1] to [register 2]<<[register 3])
* 0x11 : right shift (set [register 1] to [register 2]<<[register 3])
* 0x12 : not (set [register 1] to ![register 2])
* 0x13 : and (set [register 1] to [register 2]&[register 3])
* 0x14 : or (set [register 1] to [register 2]|[register 3])
* 0x15 : xor (set [register 1] to [register 2]^[register 3])

### 0x2X : operations on integers
* 0x21 : incrementation (set [register 1] to [register 2]+1)
* 0x22 : decrementation (set [register 1] to [register 2]-1)
* 0x23 : addition (set [register 1] to [register 2] + [register 3])
* 0x24 : substraction (set [register 1] to the absolute value of [register 2]-[register 3]) *note : if [register 2]<[register3], then 1 gonna be pushed automatically on the stack if it as been defined. If [register 2]>=[register 3], it gonna push 1*
* 0x25 : multiplication (set [register 1] to [register 2]*[register 3])
* 0x26 : euclidian division (set [register 1] to [register 2]/[register 3] and push the rest on the stack if it as been defined])
* 0x27 : modulo (set [register 1] to [register 2]%[register 3])

### 0x3X : conditions
* 0x30 : true (set R4 to 1)
* 0x31 : false (set R4 to 0)
* 0x32 : equal (set R4 to 1 if [register 1]=[register 2]
* 0x33 : not equal (set R4 to 1 if [register 1]=![register 2])
* 0x34 : higher (set R4 to 1 if [register 1]>[register 2])
* 0x35 : higher or equal (set R4 to 1 if [register 1]>=[register 2])
* 0x36 : lower (set R4 to 1 if [register 1]<[register 2])
* 0x37 : lower or equal (set R4 to 1 [register 1]=<[register 1])

### 0x4X : io *(not supported yet)*
* 0x40 : send (send to the output port number [register 1] the value stored in memory at the address binded with the port)
* 0x41 : read (read in input port number [register 1] and store the value in memory at the address binded with the port)
* 0x42 : bind op (bind the output port number [register 1] to the address [register 2])
* 0x43 : bind ip (bind the input port number [register 1] to the address [register 2])

### 0xFF : break
* 0xFF : break (shut down the virtual machine)

## Errors 
* The error register can tak 16 differents values :
	* 0x0 : no error :)
	* 0x1 : division by zero
	* 0x2 : reading or writing out of memory (not supported yet)
