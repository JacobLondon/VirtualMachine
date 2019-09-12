# Virtual Machine
A virtual processor which has similar characteristics to an ARM processor. Written in C++. Due to the nature of the processor being in software, the instructions will not follow fixed length formats. Additionally, the virtual machine will be a single cycle system; parallelism is not planned for at this stage. The virtual machine will be a 64-bit system; therefore the host machine must be able to support 64-bit C++ operations.
## Registers
* 32 64-bit integer registers
  * r0 - r31
* 16 64-bit floating point registers
  * f0-f15
* 2 64-bit special registers
  * zero, pc
* Flag Register (8-bit)
  * 0x1 - Overflow
  * 0x2 - Carry
  * 0x4 - Zero
  * 0x8 - Negative
## Memory - Harvard Architecture
* Instruction Memory
  * On initialization, set to the needed size
  * Maximum of 2^64 instructions
* Data Memory
  * Initialized to the size specified on creation.
  * (Planned) Automatically resizing memory as needed by the program.
  * Maximum of 2^64 words (64-bit length words).
* Stack
  * Function calls.
## Instructions
* 256 possible instructions, 2^8

| Inst Type | Format |
|-----------|--------|
| Register | opcode(8) - status(8) - suffix(8) - target(8) - register1(8) - register2(8)
| Immediate | opcode(8) - status(8) - suffix(8) - target(8) - immediate(64)
| Branch | opcode(8) - status(8) - address(64)

| Instruction | Type | Description |
|-------------|------|-------------|
| fadd | register | floating point addition
| add | register | addition
| fsub | register | floating point subtract
| sub | register | subtraction
| fmul | register | floating point multiply
| mul | register | multiply
| fdiv | register | floating point divide
| div | register | divide
| mod | register | modulus
| nand | register | logical nand
| and | register | logical and
| xnor | register | logical exclusive nor
| xor | register | logical exclusive or
| nor | register | logical nor
| or | register | logical or
| shr | register | logical shift right
| sra | register | arithmetic shift right
| shl | register | logical shift left
| ror | register | rotate right
| rol | register | rotate left
| cmp | register | compare and set status register
| swp | register | swap two registers' data
| mov | register | move one register's data into another
| li | immediate | load an integer number into the register
| lf | immediate | load a floating point number into the register
| set | immediate | set all the register's bits to 1
| clr | immediate | clear all the register's bits to 0
| sw | immediate | store (write) register to data memory
| lw | immediate | load register (read) from data memory
| b | jump | branch to the label
| call | jump | branch to a function and link, used in conjunction with ret
| ret | jump | return to link at top of link stack if there is something to pop

## [ARM Suffix Reference](http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0473c/CEGBHJCJ.html)
* Allocating unsigned 8-bit integers, so 2^8 suffices possible

| Suffix | Flags | Meaning |
|--------|-------|---------|
| EQ | Z set | Equal (==)
| NE | Z clear | Not Equal (!=)
| CS or HS | C set | Higher, Same (unsigned >=)
| CC or LO | C clear | Lower (unsigned <)
| MI | N set | Negative
| PL | N clear | Positive or zero
| VS | V set | Overflow
| VC | V clear | No overflow
| HI | V set and Z clear | Higher (unsigned >)
| LS | C clear or Z set | Lower or same (unsigned <=)
| GE | N and V the same | Signed >=
| LT | N and V differ | Signed <
| GT | Z clear, N and V the same | Signed >
| LE | Z set, N and V differ | Signed <=
| AL | Any | Always. Normally omitted.
