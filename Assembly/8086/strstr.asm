TITLE   8086 Code Template (for EXE file)

;       AUTHOR          emu8086
;       DATE            ?
;       VERSION         1.00
;       FILE            ?.ASM

; 8086 Code Template

; Directive to make EXE output:
       #MAKE_EXE#

DSEG    SEGMENT 'DATA'

szHint1			db	'Please Input String1:', 10, 13, '$'
szHint2			db	'Please Input String2:', 10, 13, '$'
szNextLine		db	10, 13, '$'

MaxLenString1	db	31
ActLenString1	db	?
String1			db	31 dup(?)

MaxLenString2	db	31
ActLenString2	db	?
String2			db	31 dup(?)

szFound1		db	'The String2 is found ', '$'
szFound2		db	' times in String1', 10, 13, '$'
szNotFound		db	'Sorry, the String2 is not found in String1.', 10, 13, '$'
dbCounter		db	0

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


; TODO: add your code here!!!!
	
	;read in the String1 and String2
	lea		dx, szHint1
	mov		ah, 09H
	int		21H
	lea		dx, MaxLenString1
	mov		ah, 0AH
	int		21H
	lea		dx, szNextLine
	mov		ah, 09H
	int		21H
	lea		dx, szHint2
	mov		ah, 09H
	int		21H
	lea		dx, MaxLenString2
	mov		ah, 0AH
	int		21H
	lea		dx, szNextLine
	mov		ah, 09H
	int		21H
	
;init
	xor		bx, bx					;pointer to String1
	dec		bx
	xor		di, di					;pointer to String2
	xor		ah, ah					;counter = 0
	xor		dx, dx					;clear temp register
L2:
	mov		al, String2[di]
	mov		dl, ActLenString1		;End of String1?
	dec		dl
L4:
	cmp		bx, dx
	jz		SearchEnd
	inc		bx
	cmp		String1[bx], al			;if String2[di] == String1[bx]
	jnz		L4

	push	bx
L1:
	mov		dl, ActLenString2		;End of String2?
	dec		dl
	cmp		di, dx
	jnz		L3
	inc		ah						;String2 is found. counter++
	xor		di, di					;clear String2 pointer
	jmp		L2
L3:
	inc		di
	inc		bx
	
	mov		al, String2[di]
	cmp		String1[bx], al
	jz		L1
	pop		bx						;recover the bx
	xor		di, di
	jmp		L2
	
SearchEnd:
	mov		dbCounter, ah
	cmp		ah, 0
	jz		NFound
	lea		dx, szFound1
	mov		ah, 09H
	int		21H
	mov		dl, dbCounter
	add		dl, 30H
	mov		ah, 02H
	int		21H
	lea		dx, szFound2
	mov		ah, 09H
	int		21H
	jmp		endProgram
NFound:
	lea		dx, szNotFound
	mov		ah, 09H
	int		21H
endProgram:
; return to operating system:
    RET
START   ENDP

;*******************************************

CSEG    ENDS 

        END    START    ; set entry point.

