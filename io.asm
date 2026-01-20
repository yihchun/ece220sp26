.ORIG x3000

; read a keystroke and put the ASCII code in R0
LDI R0, KBSR
BRzp #-2
LDI R0, KBDR

; output R0 to the display
LDI R1, DSR
BRzp #-2
STI R0, DDR

HALT
KBSR .FILL xFE00
KBDR .FILL xFE02
DSR .FILL xFE04
DDR .FILL xFE06
.END