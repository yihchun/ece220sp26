.ORIG x3000

LD R6, STACK_START
; b.bar()
; if non-virtual JSR BAR_BAR
LEA R0, B
ADD R6, R6, #-1
STR R0, R6, #0   ; push this to the stack
LD R0, B
LDR R0, R0, #0
JSRR R0
ADD R6, R6, #2

; f->bar()
; if non-virtual JSR FOO_BAR
LD R0, F
LDR R0, R0, #0
LDR R0, R0, #0
JSRR R0
ADD R6, R6, #1

; x.bar()
; if non-virtual JSR FOO_BAR
LD R0, X
LDR R0, R0, #0
JSRR R0
ADD R6, R6, #1
HALT


FOO_BAR   ; Foo::bar()
ADD R6, R6, #-1
STR R7, R6, #0
LEA R0, FOO_MSG
PUTS
LDR R7, R6, #0
RET

BAR_BAR   ; Bar::bar()
ADD R6, R6, #-1
STR R7, R6, #0
LEA R0, BAR_MSG
PUTS
LDR R7, R6, #0
RET

FOO_VFT .FILL FOO_BAR
BAR_VFT .FILL BAR_BAR
FOO_MSG .STRINGZ "I'm a Foo\n"
BAR_MSG .STRINGZ "I'm a Bar\n"
B .FILL BAR_VFT
F .FILL B
X .FILL FOO_VFT

STACK_START .FILL x4000

.END
