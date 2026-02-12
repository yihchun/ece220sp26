.ORIG x3000

; call fact(5)
LD R6, STACK_INIT
AND R0, R0, #0
ADD R0, R0, #5
ADD R6, R6, #-1
STR R0, R6, #0
JSR FACT
HALT

MULTIPLY
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

FACT
; callee setup (general)
    ADD R6, R6, #-5  ; # of LV + 3
    STR R5, R6, #2   ; # of LV
    ADD R5, R6, #1   ; # of LV - 1
    STR R7, R5, #2

    ; accum = 1;
    AND R0, R0, #0
    ADD R0, R0, #1
    STR R0, R5, #-1

    ; i = a;
    LDR R0, R5, #4
    STR R0, R5, #0

FACT_LOOPTOP
    ; terminate loop if !i
    LDR R0, R5, #0
    BRz FACT_ENDLOOP
    ; caller setup multiply(accum,i)
    ; push i
    ADD R6, R6, #-2
    STR R0, R6, #1
    LDR R0, R5, #-1
    STR R0, R6, #0
    JSR MULTIPLY
    ; caller teardown
    LDR R0, R6, #0
    ADD R6, R6, #3  ; pop RV, accum, i
    STR R0, R5, #-1
    ; i--
    LDR R0, R5, #0
    ADD R0, R0, #-1
    STR R0, R5, #0
    BRnzp FACT_LOOPTOP

FACT_ENDLOOP
    LDR R0, R5, #-1
    STR R0, R5, #3
    ; callee teardown (general)
    LDR R7, R5, #2
    LDR R5, R5, #1
    ADD R6, R6, #4 ; #LV + 2
    RET

STACK_INIT .FILL x4000

.END