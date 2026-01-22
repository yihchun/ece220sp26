.ORIG x3000

; populate trap vector table at x10 to be MUL_TRAP
LEA R0, MUL_TRAP
STI R0, MUL_TRAP_LOC

; multiply 3*4 using TRAP x10
AND R0, R0, #0
ADD R0, R0, #3
ADD R1, R0, #-7
TRAP x10
HALT
; just this once, be good about saving registers
; multiplies R0 * R1 -> R0
MUL_TRAP
    ST R1, MUL_TRAP_R1
    ST R2, MUL_TRAP_R2
    ST R3, MUL_TRAP_R3

    AND R2, R2, #0
    
MUL_LOOP_TOP
    ADD R2, R2, R0
    ADD R1, R1, #-1
    BRnp MUL_LOOP_TOP

    ADD R0, R2, #0
    LD R1, MUL_TRAP_R1
    LD R2, MUL_TRAP_R2
    LD R3, MUL_TRAP_R3
    RET

MUL_TRAP_LOC .FILL x10
MUL_TRAP_R1 .FILL #0
MUL_TRAP_R2 .FILL #0
MUL_TRAP_R3 .FILL #0
.END