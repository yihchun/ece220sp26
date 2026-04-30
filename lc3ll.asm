.ORIG x3000

; caller setup
LD R6, STACK_START

JSR MALLOC2
JSR MALLOC2
JSR FREE2      ; free(malloc(2));
ADD R6, R6, #2 ; tear them down together
JSR FREE2      ; free(malloc(2));
ADD R6, R6, #2 ; tear them down together

MAIN_LOOP
LD R0, LLPTR        ; grab the head pointer
STR R0, R6, #0
JSR LL_PRINT
ADD R6, R6, #2
IN
ADD R0, R0, #-16
ADD R0, R0, #-16
ADD R0, R0, #-16
ADD R6, R6, #-2
STR R0, R6, #1
LEA R0, LLPTR       ; the address of the head pointer (&head)
STR R0, R6, #0
JSR INSERT_HEAD
ADD R6, R6, #3
BRnzp MAIN_LOOP
HALT

LL_PRINT
    ; callee setup
    ADD R6, R6, #-3
    STR R5, R6, #0
    ADD R5, R6, #-1
    STR R7, R5, #2

LL_PRINT_LOOP
    ; while (head)
    LDR R1, R5, #4          ; R1 <- head
    BRz LL_PRINT_LOOP_DONE  ; if (!head) break;
    LDR R0, R1, #0          ; R0 <- head->data
    ADD R0, R0, #15
    ADD R0, R0, #15
    ADD R0, R0, #15
    ADD R0, R0, #3          ; R0 <- head->data + '0'
    OUT
    AND R0, R0, #0
    ADD R0, R0, #15
    ADD R0, R0, #15
    ADD R0, R0, #2
    OUT                     ; output ' '
    LDR R0, R1, #1          ; R0 <- head->next
    STR R0, R5, #4
    BRnzp LL_PRINT_LOOP

LL_PRINT_LOOP_DONE
    AND R0, R0, #0
    ADD R0, R0, #10
    OUT                     ; output '\n'
    
    ; callee teardown
    LDR R7, R5, #2
    LDR R5, R5, #1
    ADD R6, R6, #2
    RET

INSERT_HEAD
    ; callee setup
    ADD R6, R6, #-4
    STR R5, R6, #1
    ADD R5, R6, #0
    STR R7, R5, #2

    JSR MALLOC2
    ; caller teardown
    LDR R0, R6, #0      ; R0 <- malloc(2)
    ADD R6, R6, #1
    STR R0, R6, #0      ; new_node = malloc(2)

    LDR R1, R5, #4      ; R1 <- head
    LDR R2, R1, #0      ; R2 <- *head
    STR R2, R0, #1      ; new_node->next = *head

    LDR R2, R5, #5      ; R2 <- data
    STR R2, R0, #0      ; new_node-> x = data

    STR R0, R1, #0      ; *head = new_node
    ; callee teardown
    LDR R7, R5, #2
    LDR R5, R5, #1
    ADD R6, R6, #3
    RET    

MALLOC2
    ADD R6, R6, #-1
    LD R0, HEAP_FREELIST
    BRz MALLOC2_NOFREELIST
    STR R0, R6, #0          ; return first element on the free list
    LDR R0, R0, #0          ; grab the next pointer
    ST R0, HEAP_FREELIST
    RET
MALLOC2_NOFREELIST
    LD R0, HEAP_FIRST_FREE
    STR R0, R6, #0          ; return HEAP_START
    ADD R0, R0, #2
    ST R0, HEAP_FIRST_FREE  ; increment HEAP_START
    RET

FREE2                       ; do nothing, will improve later
    ADD R6, R6, #-1
    LDR R0, R6, #1          ; R0 is the parameter
    LD R1, HEAP_FREELIST    ; R1 is currently the head of the free list
    STR R1, R0, #0          ; R0 now points to R1
    ST R0, HEAP_FREELIST    ; now R0 (freshly freed) is the head of the free list
    RET

STACK_START .FILL x4000
LLPTR .FILL TEST_LL
TEST_LL .FILL 1
        .FILL TEST_LL2
TEST_LL2 .FILL 2
         .FILL 0
HEAP_FIRST_FREE .FILL HEAP_START
HEAP_FREELIST .FILL 0
HEAP_START .FILL 0

.END
