.ORIG x3000

LD R6, STACK_START
LD R0, INIT_VALUE
STR R0, R6, #0
JSR FACTORIAL
HALT

FACTORIAL
; callee setup
ADD R6, R6, #-4
STR R5, R6, #1
ADD R5, R6, #0
STR R7, R5, #2

; if (n <= 1)
LDR R0, R5, #4
ADD R1, R0, #-1
BRnz FACTORIAL_RET_1

; factorial(n-1)
; caller setup: push n-1
ADD R6, R6, #-1
STR R1, R6, #0
JSR FACTORIAL
; caller teardown
LDR R0, R6, #0 ; factorial(n-1) -> R0
ADD R6, R6, #2
STR R0, R5, #0

; caller setup
LDR R0, R5, #0
ADD R6, R6, #-2
STR R0, R6, #1
LDR R0, R5, #4
STR R0, R6, #0
JSR MULTIPLY
LDR R0, R6, #0 ; n*tmp -> R0
ADD R6, R6, #3
BRnzp FACTORIAL_RET_R0

; tmp <- R5+0 <- R6
; R5 save (cfp) <- +1
; R7 save (ra)  <- +2
; return value  <- +3
; n             <- +4

FACTORIAL_RET_1
AND R0, R0, #0
ADD R0, R0, #1

FACTORIAL_RET_R0
STR R0, R5, #3
; callee teardown
LDR R7, R5, #2
LDR R5, R5, #1
ADD R6, R6, #3
RET

MULTIPLY
; repeated bitshifts of second number
; either add that bitshifted value or don't
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
; Symbol Table
;   a int R5 +4 fact [leftmost param is ALWAYS R5+4]
;   b int R5 +5 fact

; callee setup -- push locals & bookkeeping
    ADD R6, R6, #-1 ; make space for return value
    ADD R6, R6, #-1 ; make space for return address R7 save
    STR R7, R6, #0
    ADD R6, R6, #-1 ; make space for caller frame pointer R5 save
    STR R5, R6, #0
    ADD R5, R6, #-1 ; set the frame pointer

    LDR R0, R5, #4 ; load a into R0
    LDR R1, R5, #5 ; load b into R1

; we have some voodoo black magic that multiplies R0*R1 -> R0 

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

    ; magically R0 has the answer we want
    STR R0, R5, #3

; callee teardown
    ; pop FP
    LDR R5, R6, #0
    ADD R6, R6, #1
    ; pop RA
    LDR R7, R6, #0
    ADD R6, R6, #1

    RET


INIT_VALUE .FILL #5
STACK_START .FILL x4000


.END
