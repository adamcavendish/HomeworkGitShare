TITLE   8086 Code Template (for EXE file)

;       AUTHOR          emu8086
;       DATE            ?
;       VERSION         1.00
;       FILE            ?.ASM

; 8086 Code Template

; Directive to make EXE output:
       #MAKE_EXE#

DSEG    SEGMENT 'DATA'
	A1	DB	10 DUP (?)
; TODO: add your data here!!!!

DSEG    ENDS

SSEG    SEGMENT STACK   'STACK'
        DW      100h    DUP(?)
SSEG    ENDS

CSEG    SEGMENT 'CODE'

;*******************************************

START   PROC    FAR

; Store return address to OS:
    PUSH    DS
    MOV     AX, 0
    PUSH    AX

; set segment registers:
    MOV     AX, DSEG
    MOV     DS, AX
    MOV     ES, AX
	
	mov		bx, 0
	mov		cl, 10
input:
	MOV		AH, 1H
	INT		21H
	mov		A1[bx], al
	inc		bx
	dec		cl
	jnz		input
	
	mov		dl, 13
	mov		ah, 2h
	int		21h
	mov		dl, 10
	mov 	ah, 2h
	int		21h
	
	mov		cl, 10
	mov		bx, 0
output:
	MOV		AH, 2H
	MOV		DL, A1[bx]
	INT		21H
	inc		bx
	dec		cl
	jnz		output




; return to operating system:
    RET
START   ENDP

;*******************************************

CSEG    ENDS 

        END    START    ; set entry point.

