.ORIG x3000

AND R0, R0, #0
ADD R0, R0, #0
JSR FACT_SUBR
HALT


; repeated bitshifts of second number
; either add that bitshifted value or don't
; R0*R1 -> R0
; R1 is the bitshifted value
; R2 is the accumulator
; R3 is the bitmask starts as LSB
; R4 junk
; 100110 x 101101
;       R1              R3
;          101101 0        1
;         1011010 1       10
;        10110100 1      100
;       101101000 0     1000
;      1011010000 0    10000
;     10110100000 1   100000
;       101101
;     x 100110
; ------------
;      1011010
;     10110100
;  10110100000
; -------------
MUL_SUBR
    ST R1, MUL_TRAP_R1
    ST R2, MUL_TRAP_R2
    ST R3, MUL_TRAP_R3
    ST R4, MUL_TRAP_R4

    AND R2, R2, #0
    ADD R3, R2, #1

LOOPTOP
    AND R4, R0, R3
    BRz #1          ; don't add to accumulator because AND is 0
    ADD R2, R2, R1
    ADD R1, R1, R1
    ADD R3, R3, R3
    BRnp LOOPTOP
    ADD R0, R2, #0
    
    LD R1, MUL_TRAP_R1
    LD R2, MUL_TRAP_R2
    LD R3, MUL_TRAP_R3
    LD R4, MUL_TRAP_R4
    RET

MUL_TRAP_R1 .FILL #0
MUL_TRAP_R2 .FILL #0
MUL_TRAP_R3 .FILL #0
MUL_TRAP_R4 .FILL #0

; R0! -> R0
; R0 accumulator
; R1 something for MUL
; R2 parameter
; R3 
; R4 
FACT_SUBR
    ST R1, FACT_R1
    ST R2, FACT_R2
    ST R3, FACT_R3
    ST R4, FACT_R4
    ST R7, FACT_R7

    ADD R1, R0, #-1
    BRnz FACT_SPECIAL_CASE

FACT_LOOP_TOP
    JSR MUL_SUBR
    ADD R1, R1, #-1
    BRp FACT_LOOP_TOP

FACT_REG_RESTORE
    LD R1, FACT_R1
    LD R2, FACT_R2
    LD R3, FACT_R3
    LD R4, FACT_R4
    LD R7, FACT_R7
    RET

FACT_SPECIAL_CASE
    AND R0, R0, #0
    ADD R0, R0, #1
    BRnzp FACT_REG_RESTORE

FACT_R1 .FILL #0
FACT_R2 .FILL #0
FACT_R3 .FILL #0
FACT_R4 .FILL #0
FACT_R7 .FILL #0



.END