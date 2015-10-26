TITLE   8086 Code Template (for EXE file)

;       AUTHOR          emu8086
;       DATE            ?
;       VERSION         1.00
;       FILE            ?.ASM

; 8086 Code Template

; Directive to make EXE output:
       #MAKE_EXE#

DSEG    SEGMENT 'DATA'

	A1	db	37
	A2	db	?
	A3	db	37 dup(?)
	A4	db	'Input String: ', '$'

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

	;open a window
	mov ah, 6
	mov al, 0
	mov bh, 70
	mov ch, 5
	mov cl, 5
	mov	dh, 15
	mov	dl, 40
	int 10H
	;set cursor
	mov	ah, 2
	mov bh, 0
	mov dh, 5
	mov dl, 5
	int 10H
	;show mes
	mov ah, 9
	lea dx, a4
	int 21H
	;set cursor
	mov ah, 2
	mov bh, 0
	mov dh, 6
	mov dl, 5
	int 10h
	;input
	mov ah, 0ah
	lea dx, a1
	int	21h
	


; return to operating system:
    RET
START   ENDP

;*******************************************

CSEG    ENDS 

        END    START    ; set entry point.

