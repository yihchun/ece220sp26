.ORIG x3000

LD R6, STACK_TOP   ; initialize R6 to x4000
LEA R1, IN_ORDER   ; pointer to the next car inbound
LEA R2, OUT_ORDER  ; pointer to the next car outbound

LOOPTOP
; if next car is next out (h)
; if r6 < x4000 and if top of the stack is next out (o)
; push (u)

LDR R4, R1, #0 ; in
LDR R5, R2, #0 ; out
BRz DONE       ; if we reach the end of the output, we are done
NOT R5, R5
ADD R5, R5, #1 ; negating out (R5 holds -out)
ADD R0, R4, R5 ; compute in-out
BRz DO_THROUGH ; they are equal, go through
LD R0, NEGATIVE_TOP ; make sure there's something on the stack
ADD R0, R0, R6
BRz DO_PUSH    ; if stack is empty, we push
; stack is not empty
LDR R4, R6, #0 ; peek
ADD R0, R4, R5 ; compute peek-out
BRz DO_POP     ; next output train is the one on the top of the stack, pop
DO_PUSH        ; through, pop doesn't work, so push
LD R0, CMD_PUSH ; tell the user to push
OUT
ADD R6, R6, #-1 ; push the car onto the stack
LDR R4, R1, #0  ;; in
STR R4, R6, #0  ;; push(in)
ADD R1, R1, #1  ; we took care of 1 input car
BRnzp LOOPTOP   ; work on the next car pair

DO_THROUGH
LD R0, CMD_THROUGH ; tell the user to send the car through
OUT
ADD R1, R1, #1 ; we took care of 1 input car
ADD R2, R2, #1 ; we took care of 1 output car
BRnzp LOOPTOP  ; work on the next pair

DO_POP
LD R0, CMD_POP ; tell the user to pop car off the spur
OUT
ADD R6, R6, #1 ; pop
ADD R2, R2, #1 ; we took care of 1 output car
BRnzp LOOPTOP  ; work on the next pair

DONE
HALT ; reached the end of the output, we're done for today.

STACK_TOP .FILL x4000
NEGATIVE_TOP .FILL xC000
IN_ORDER .STRINGZ "ZYXWVUTSR"
OUT_ORDER .STRINGZ "YXVUWZSRT"
CMD_THROUGH .STRINGZ "h"
CMD_PUSH .STRINGZ "u"
CMD_POP .STRINGZ "o"

.END