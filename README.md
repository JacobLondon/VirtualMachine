# Virtual Machine
A virtual processor which has similar characteristics to an ARM processor. Written in C++. Due to the nature of the processor being in software, the instructions will not follow fixed length formats. Additionally, the virtual machine will be a single cycle system; parallelism is not planned for at this stage. The virtual machine will be a 64-bit system; therefore the host machine must be able to support 64-bit C++ operations.
## Registers
* 32 64-bit integer registers
  * r0 - r31
* 32 64-bit floating point registers
  * f0-f31
* 2 64-bit special registers
  * zero, pc
* Flag Register (8-bit)
  * 0x1 - Overflow (v)
  * 0x2 - Carry (c)
  * 0x4 - Zero (z)
  * 0x8 - Negative (n)
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

| Instruction Type | Format |
|------------------|--------|
| Register  | opcode(16) - status(8) - suffix(8) - target(8) - register1(8) - register2(8)
| Immediate | opcode(16) - suffix(8) - target(8) - register(8) - immediate(64)
| Branch    | opcode(16) - suffix(8) - target(8) - register(8) - immediate(64)

| Letter | Fix  | Description |
|--------|------|-------------|
| f      | Pre  | floating point operation (rather than integer)
| b      | Pre  | bitwise operation (rather than logical)
| i      | Post | immediate operation (rather than register)

| Operation Type   | Example |     Immediate Usage      |
|------------------|---------|--------------------------|
| register         | add     | op target reg1 reg2      |
| immediate        | addi    | op target reg1 immediate |
| jump             | b       | op (register) address (label / offset) |

| Instruction | Type | Valid Fixes |          Uses              |  Description     |
|-------------|------|-------------|----------------------------|------------------|
| add         | r    | f, i        | faddi, fadd, addi, add     | addition         |
| sub         | r    | f, i        | fsubi, fsub, subi, sub     | subtraction      |
| mul         | r    | f, i        | fmuli, fmul, muli, mul     | multiplication   |
| div         | r    | f, i        | fdivi, fdiv, divi, div     | division         |
| mod         | r    | i           | modi, mod                  | modulus          |
| nand        | r    | b, i        | bnandi, bnand, nandi, nand | not and          |
| and         | r    | b, i        | bandi, band, andi, and     | and              |
| xnor        | r    | b, i        | bxnori, bxnor, xnori, xnor | exclusive nor    |
| xor         | r    | b, i        | bxori, bxor, xori, xor     | exclusive or     |
| nor         | r    | b, i        | bnori, bnor, nori, nor     | not or           |
| or          | r    | b, i        | bori, bor, ori, or         | or               |
| not         | r    |             | not                        | logical not      |
| comp        | r    |             | comp                       | one's complement |
| shr         | r    | i           | shri, shr                  | shift right      |
| shl         | r    | i           | shli, shl                  | shift left       |
| cmp         | r    | f, i        | fcmpi, fcmp, cmpi, cmp     | compare and set status register |
| swp         | r    | f           | fswp, swp                  | swap two registers' data |
| mov         | r    | f, i        | fmovi, fmov, movi, mov     | move data into target |
| set         | r    | f           | fset, set                  | set the register to max value |
| clr         | r    | f           | fclr, clr                  | clear the register to zero |
| sw          | i    |             | sw                         | store register to data memory |
| lw          | i    |             | lw                         | load register from data memory |
| inc         | i    |             | inc                        | pre increment |
| dec         | i    |             | dec                        | pre decrement |
| push        | r    | i           | push, pushi                | push register or immediate to data stack |
| pop         | r    |             | pop                        | pop data stack into register |
| b           | j    |             | b                          | branch to a register's value + immediate offset
| call        | j    |             | call                       | branch to a function and link, used with ret |
| ret         | j    |             | ret                        | return to link at top of link stack |

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
