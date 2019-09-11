# Virtual Machine
A virtual processor which has similar characteristics to an ARM processor. Written in C++.
## Registers
* 32 64-bit registers
  * r0, r1, r2, r3, r4, r5, r6, r7, r8
  * t0, t1, t2, t3, t4, t5, t6, t7, t8
  * a0, a1, a2, a3
  * v0, v1
  * s0, s1, s2, s3, s4, s5, s6, s7, s8
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
  * Automatically resizing memory as needed by the program.
  * Maximum of 2^64 words
* Stack
## Instructions
* 256 possible instructions, 2^8

| Inst Type | Format |
|------------------|--------|
| Register | opcode(8) - status(8) - suffix(5) - target(5) - register1(5) - register2(5) - shift(6) - alufn(21)
| Immediate | opcode(8) - status(8) - suffix(5) - target(5) - immediate(38)
| Branch | opcode(8) - status(8) - address(48)
|

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
| set | immediate | set the register to 1
| clr | immediate | clear the register to 0
| ww | immediate | write word to data memory
| rw | immediate | read word from data memory
| b | branch | branch to the label
| call | branch | branch to a function and return afterwards
| ret | branch | return to link at top of link stack if there is something to pop
|

## [ARM Suffix Reference](http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0473c/CEGBHJCJ.html)
* 32 possible suffixes, 2^5

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
|
