TITLE   8086 Code Template (for EXE file)

;       AUTHOR          emu8086
;       DATE            ?
;       VERSION         1.00
;       FILE            ?.ASM

; 8086 Code Template

; Directive to make EXE output:
       #MAKE_EXE#

DSEG    SEGMENT 'DATA'

	boardSize	equ		15
	boardInit	db		'01©°©Ð©Ð©Ð©Ð©Ð©Ð©Ð©Ð©Ð©Ð©Ð©Ð©Ð©´', 13, 10,
				db		'02©À©à©à©à©à©à©à©à©à©à©à©à©à©à©È', 10, 13,
				db		'03©À©à©à©à©à©à©à©à©à©à©à©à©à©à©È', 10, 13,
				db		'04©À©à©à¡ö©à©à©à©à©à©à©à¡ö©à©à©È', 10, 13,
				db		'05©À©à©à©à©à©à©à©à©à©à©à©à©à©à©È', 10, 13,
				db		'06©À©à©à©à©à©à©à©à©à©à©à©à©à©à©È', 10, 13,
				db		'07©À©à©à©à©à©à©à©à©à©à©à©à©à©à©È', 10, 13,
				db		'08©À©à©à©à©à©à©à¡ö©à©à©à©à©à©à©È', 10, 13,
				db		'09©À©à©à©à©à©à©à©à©à©à©à©à©à©à©È', 10, 13,
				db		'10©À©à©à©à©à©à©à©à©à©à©à©à©à©à©È', 10, 13,
				db		'11©À©à©à©à©à©à©à©à©à©à©à©à©à©à©È', 10, 13,
				db		'12©À©à©à¡ö©à©à©à©à©à©à©à¡ö©à©à©È', 10, 13,
				db		'13©À©à©à©à©à©à©à©à©à©à©à©à©à©à©È', 10, 13,
				db		'14©À©à©à©à©à©à©à©à©à©à©à©à©à©à©È', 10, 13,
				db		'15©¸©Ø©Ø©Ø©Ø©Ø©Ø©Ø©Ø©Ø©Ø©Ø©Ø©Ø©¼', 10, 13,
				db		'$'

DSEG    ENDS

SSEG    SEGMENT STACK   'STACK'
        DW      100h    DUP(?)
SSEG    ENDS

CSEG    SEGMENT 'CODE'

;MAIN Part Of the Program.
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

	call	Init
; return to operating system:
    RET
START   ENDP
;*******************************************

;Init. Used to initiate the Program
;*******************************************
Init	proc	near
	push	ax
	push	dx
	mov		ah, 09H
	mov		dx, offset boardInit
	int		21H
	
	pop		ax
	pop		dx
	ret
Init	endp
;*******************************************


;*******************************************
;*******************************************
CSEG    ENDS 

        END    START    ; set entry point.

