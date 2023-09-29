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

## Condition bits (*not supported yet*):
* The condition bits are the first 4 bits of the 2nd byte of an instruction. If thir value is different of 0x0, the instruction will only be executed if R4 (condition register) is himself different of 0.

## Instruction set :

### 0x0X : data management 
* 0x00 : set (set value stored in memory at [variable] to [register1])
* 0x01 : load (load value stored in memory at [variable] in [register1])
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

### 0xFF : break
* 0xFF : break (shut down the virtual machine)

## Configuration
* The configuration structure contains some important parameters. It is 32 bytes long :
	* Firsts 8 bytes : size of ram
	* Next 4 bytes : number of input ports 
	* Next 4 bytes : number of output ports
	* Next 8 bytes : address of 1st input port (*more informations lower*)
	* Next 8 bytes : address of memory configuration structure (*more informations lower*)
* The configuration structure is stored in the ram. The first address of the configuration structure is stored in the configuration pointer (R2/CP).
* The default address of config structure is as high as possible, so the ram size -32 
* The default configuration is :
	* Size of the ram : *size of ram* 
	* Number of input ports : 8
	* Number of output ports : 8
	* Address of 1st i/o port : 0x0
	* Address of memory configuration structure : 0x10
> Tip : if you want to change the place of the config structure in he ram, first load the new structure, then move the CP, and finally remove the first structure. Else the vm will cry.
> Tip 2 : i highly recomand you to never change the content of the *size of ram* parameter. Else it gonna cry again.

## I/O ports
* To use external devices, you have to use I/O ports :
	* an input port is just a memory address where external devices can write;
	* an output port is just a memory address where external devices can read (and where you can write) 
* The config structure define the address of the number of imput/output ports and the address of the first input port. The first output port come after the last input port.
> Tip : don't write in input port, else it will be angry

## Memory configuration structure
* The memory configuration structure is a bit like the GDT in x86_64, it is here to manage memory permissions. The lenght of this structure depends of the number of entries it contain (at least 1). 
* The first byte of the memory config structure is the number of entries (size byte). 
* The address of the first byte is in the config structure.
* The first byte of the first entry come just after the size bye. The first byte of any other entry.
* One entry is 3 bytes long :
	* 1st byte : 
		* read permission value (4 first bits, so 1 value from 0x0 to 0xF) : code from a segment can only read the content of a segment that the read permission is lower or equal to its one
		* write permission value (4 next bits, 0x0 to 0xF too) : code from a segment can only  write in a segment where it is able to read and that the write permission is strictly lower than its one (+in itself) (so a 0xF to this value mean that the segment can only be modified by itself)
		* sepcial values : 0x0F
	* 2nd byte : size of the segment
	* 3rd byte : address of the beginning of the segment
> Tip : never forget to map a part of a memory, else it gonna cry
* Default setting : 1 0xFF entry

## Errors 
* The error register can tak 16 differents values :
	* 0x0 : no error :)
	* 0x1 : division by zero
	* 0x2 : reading or writing out of memory (not supported yet)
