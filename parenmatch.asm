.ORIG x3000

; Register Allocation Table
; R0 - current character
; R1 - position in the string
; R2 - character against which we are currently checking
; R3 - negative of current character
; R6 - stack pointer

LEA R1, CHECK_ME    ; string pointer
LD R6, STACK_START  ; initialize stac pointer

CHECK_LOOP
    LDR R0, R1, #0  ; get next character
    BRz END_OF_STRING ; check for end

    NOT R3, R0     ; invert current character
    ADD R3, R3, #1 ;;

    LD R2, OPENPAREN
    ADD R2, R3, R2 ; check for input being (
    BRnp #2 ; not (, skip the hacky logic
    ADD R0, R0, #-1 ; -1 now so that +2 later and get +1
                    ; because ( is the only parenthesis 1 away from the close
    BRnzp DO_PUSH   ; push ) onto the stack

    ; not (
    ; is it ) -- if so, R2 == -1
    ADD R2, R2, #1
    BRz K_POP      ; this is a ), so we should pop and verify

    ; is it <
    LD R2, OPENANGLE
    ADD R2, R3, R2
    BRz DO_PUSH
    ADD R2, R2, #2 ; is it >
    BRz K_POP

    LD R2, OPENBRACKET
    ADD R2, R3, R2
    BRz DO_PUSH
    ADD R2, R2, #2
    BRz K_POP

    LD R2, OPENCURLY
    ADD R2, R3, R2
    BRz DO_PUSH
    ADD R2, R2, #2
    BRz K_POP

    ; neither ( or ) so skip it
    ADD R1, R1, #1
    BRnzp CHECK_LOOP

DO_PUSH
    ADD R0, R0, #2  ; create the closed parenthesis
    ADD R6, R6, #-1 ; push the closed parenthesis
    STR R0, R6, #0  ;;
    ADD R1, R1, #1  ; go to next character
    BRnzp CHECK_LOOP

K_POP
    LD R2, HACKY_STACK_CHECK  ; check for empty
    AND R2, R2, R6            ;;
    BRz DOES_NOT_MATCH        ;; if empty, fail
    LDR R2, R6, #0  ; pop
    ADD R6, R6, #1  ;;
    ADD R2, R2, R3  ; expected_close - input
    BRnp DOES_NOT_MATCH  ; if comparison !=, we do not match
    ADD R1, R1, #1  ; next character
    BRnzp CHECK_LOOP

END_OF_STRING
    LD R2, HACKY_STACK_CHECK  ; check for empty
    AND R2, R2, R6            ;;
    BRp DOES_NOT_MATCH        ;;
    LEA R0, WINSTRING
    PUTS
    HALT

DOES_NOT_MATCH
    LEA R0, FAILSTRING
    PUTS
    HALT

OPENPAREN .FILL #40
OPENANGLE .FILL x3C
OPENBRACKET .FILL x5B
OPENCURLY   .FILL x7B
STACK_START .FILL x4000
HACKY_STACK_CHECK .FILL x3000
CHECK_ME .STRINGZ "([{{()<>[}}}])"
FAILSTRING .STRINGZ "Your parentheses do not match"
WINSTRING .STRINGZ "Your parentheses match!"
.END