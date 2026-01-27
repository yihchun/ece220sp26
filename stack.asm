.ORIG x3000

LD R6, STACK_TOP
LEA R1, TEST_STRING ; load a test string to push each character in turn

TESTLOOP
    LDR R0, R1, #0 ; get the next character
    BRz NEXTLOOP   ; done with the string?
    JSR PUSH       ; push the char
    ADD R5, R5, #0 ; check if overflow
    BRp NEXTLOOP   ; if overflow, start popping
    ADD R1, R1, #1 ; go to next character
    BRnzp TESTLOOP

NEXTLOOP
    JSR POP        ; pop
    ADD R5, R5, #0 ; check if we ran out
    BRp DONE       ; we ran out, done
    OUT            ; else output
    BRnzp NEXTLOOP ; next stack element

DONE
HALT

TEST_STRING .STRINGZ "abcdefghijklmnopqrstuvwxyz"

PUSH
; in: R0, out R5: 1 fail, 0 success
; R6 STACK_TOP R3 STACK_END
; callee-save registers
ST R1, PUSH_SAVE_R1
ST R2, PUSH_SAVE_R2
ST R3, PUSH_SAVE_R3

; check for overflow
LD R3, STACK_END

; R6-R3, if nz overflow
NOT R3, R3
ADD R3, R3, #1
ADD R3, R6, R3
BRnz PUSH_OVERFLOW

; not overflow
ADD R6, R6, #-1 ; store value
STR R0, R6, #0  ;;
AND R5, R5, #0  ; clear R5
BRnzp PUSH_RETURNS

PUSH_OVERFLOW
AND R5, R5, #0  ; set R5 to 1
ADD R5, R5, #1

PUSH_RETURNS
; restore and return
LD R1, PUSH_SAVE_R1
LD R2, PUSH_SAVE_R2
LD R3, PUSH_SAVE_R3
RET

POP
; out: R0, out R5: 1 fail, 0 success
; R6 STACK_TOP R3 STACK_END
; callee-save registers
ST R1, PUSH_SAVE_R1
ST R2, PUSH_SAVE_R2
ST R3, PUSH_SAVE_R3

LD R3, STACK_TOP
NOT R3, R3
ADD R3, R3, #1
ADD R3, R6, R3
BRzp POP_UNDERFLOW

LDR R0, R6, #0 ; pop
ADD R6, R6, #1
AND R5, R5, #0  ; set R5 to 0
BRnzp POP_RETURNS

POP_UNDERFLOW
AND R5, R5, #0  ; set R5 to 1
ADD R5, R5, #1

POP_RETURNS
; restore and return
LD R1, PUSH_SAVE_R1
LD R2, PUSH_SAVE_R2
LD R3, PUSH_SAVE_R3
RET


PUSH_SAVE_R1 .FILL #0
PUSH_SAVE_R2 .FILL #0
PUSH_SAVE_R3 .FILL #0
STACK_TOP .FILL x4000
STACK_END .FILL x3FF0

.END