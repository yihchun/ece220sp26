.ORIG x3000

LD R6, STACK_START

LOOPTOP
    IN
    ; check for digit: between x30 and x39 (inclusive)
    ADD R1, R0, #-16 ; subtract x10
    ADD R1, R1, #-16 ; subtract another x10
    ADD R1, R1, #-16 ; subtract a final x10
    BRn NOT_A_NUMBER
    ADD R2, R1, #-9
    BRp NOT_A_NUMBER
    ; we have a digit, and the value is in R1
    ADD R6, R6, #-1 ; push
    STR R1, R6, #0
    ; handle the rest of the digit case
    BRnzp LOOPTOP

NOT_A_NUMBER
    ; handle +
    ADD R1, R1, #5
    BRz DO_ADD
    BRnzp LOOPTOP

DO_ADD
    JSR FETCH_OPERANDS
    ADD R0, R0, R1
    ADD R6, R6, #-1
    STR R0, R6, #0
    BRnzp LOOPTOP

FETCH_OPERANDS
    ; pop to R1
    LD R0, HACKY_STACK_CHECK  ; check for empty
    AND R0, R0, R6            ;;
    BRz NOT_ENOUGH_OPERANDS
    
    LDR R1, R6, #0
    ADD R6, R6, #1
    ; pop to R0
    LD R0, HACKY_STACK_CHECK  ; check for empty
    AND R0, R0, R6            ;;
    BRz NOT_ENOUGH_OPERANDS

    LDR R0, R6, #0
    ADD R6, R6, #1
    RET
    

NOT_ENOUGH_OPERANDS
    LEA R0, ERROR1
    PUTS
    HALT
    
HACKY_STACK_CHECK .FILL x3000
STACK_START .FILL x4000
ERROR1 .STRINGZ "Operator has too few operands"
.END