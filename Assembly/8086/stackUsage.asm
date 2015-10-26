TITLE   8086 Code Template (for EXE file)

;       AUTHOR          emu8086
;       DATE            ?
;       VERSION         1.00
;       FILE            ?.ASM

; 8086 Code Template

; Directive to make EXE output:
       #MAKE_EXE#

DSEG    SEGMENT 'DATA'

; TODO: add your data here!!!!

DSEG    ENDS

SSEG    SEGMENT STACK   'STACK'
	DW	100h	DUP(?)
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
	MOV		AX, SSEG
	MOV		SS, ax
	
	xor		ax, ax
	push	ax
	mov		ax, 1
	push	ax
	xor		ax, 2
	push	ax
	call 	sub1
	xor		ax, ax




; return to operating system:
    RET
START   ENDP

;*******************************************


SUB1	proc	near
;store arguments
	push	bp
	mov		bp, sp
	sub		sp, 8H
	push	ax
	push	dx
	mov		ah, 02H
	pop		dx
	add		dl, 30H
	int 	21H
	pop		dx
	add		dl, 30H
	int 	21H
	pop		dx
	add		dl, 30H
	int 	21H
	
	ret
SUB1	endp

CSEG    ENDS 

        END    START    ; set entry point.

