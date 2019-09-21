# comment

const num1   0xff
const num2   0x0f
const myaddr 0xf000

main:
    # some useless constants
    mov     r0      num1    # move num1 (0xff) into r0
    mov     r1      num2    # move num2 (0x0f) into r1

    # function call to makearr
    call    makearr
    
    ret

makearr:
    # for 10 clock cycles
    mov     r4      10
loop:
    # array of [9, 8, 7, ... 2, 1, 0]
    # at address myaddr[0 to 9]
    dec     r4
    sw      r4      myaddr[r4]
    
    cmp     r4      zero
    reteq           # return if r4 is zero
    bne     loop    # loop if r4 isn't zero
