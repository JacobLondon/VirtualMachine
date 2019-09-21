# Virtual Machine
A virtual processor which has similar characteristics to an ARM processor. Written in C++. Due to the nature of the processor being in software, the instructions will not follow fixed length formats. Additionally, the virtual machine will be a single cycle system; parallelism is not planned for at this stage. The virtual machine will be a 64-bit system; therefore the host machine must be able to support 64-bit C++ operations.
## Requirements
* Must be able to link ncurses.h
* Due to an issue with ncurses' interaction with printing repeated characters, $TERM (on an Ubuntu system) must be set to `gnome`
  * `export TERM=gnome`
  * This issue may be different depending on the system.
## Registers
* 32 64-bit integer registers
  * r0 - r31
  * r0 = zero register (always 0)
  * r31 = pc register (contains the program counter)
* 32 64-bit floating point registers
  * f0-f31
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
| Jump      | opcode(16) - suffix(8) - target(8) - register(8) - immediate(64)

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
| mod         | r    | f, i        | fmodi, fmod, modi, mod     | modulus          |
| and         | r    | b, i        | bandi, band, andi, and     | and              |
| xor         | r    | i           | xori, xor                  | exclusive or     |
| or          | r    | b, i        | bori, bor, ori, or         | or               |
| not         | r    |             | not                        | logical not      |
| comp        | r    |             | comp                       | one's complement |
| shr         | r    | i           | shri, shr                  | shift right      |
| shl         | r    | i           | shli, shl                  | shift left       |
| cmp         | r    | i           | cmpi, cmp                  | compare and set status register |
| swp         | r    |             | swp                        | swap two registers' data |
| mov         | r    | i           | movi, mov                  | move data into target |
| set         | r    |             | set                        | set the register to max value |
| clr         | r    |             | clr                        | clear the register to zero |
| sw          | i    |             | sw                         | store register to data memory |
| lw          | i    |             | lw                         | load register from data memory |
| inc         | i    |             | inc                        | pre increment |
| dec         | i    |             | dec                        | pre decrement |
| push        | i    |             | push                       | push register or immediate to data stack |
| pop         | r    |             | pop                        | pop data stack into register |
| jmp         | j    |             | b                          | branch to a register's value + immediate offset
| call        | j    |             | call                       | branch to a function and link, used with ret |
| ret         | j    |             | ret                        | return to link at top of link stack |

## Suffixes
* Allocating unsigned 8-bit integers, so 2^8 suffices possible

| Suffix | Meaning |
|--------|---------|
| CS | Carry set
| CC | Carry clear
| ZS | Zero set
| ZC | Zero clear
| NS | Negative set
| NC | Negative clear
| EQ | Equal (==)
| NE | Not Equal (!=)
| GE | Signed >=
| LT | Signed <
| GT | Signed >
| LE | Signed <=
| AL | Any | Always. Normally omitted.
