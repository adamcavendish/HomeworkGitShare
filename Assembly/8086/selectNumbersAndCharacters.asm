TITLE	8086 Code Template (for EXE file)

;	AUTHOR		Adam Basfop Cavendish
;	DATE		2012/05/02
;	VERSION		1.00
;	FILE		selectNumbersAndCharacters.ASM

; 8086 Code Template

; Directive to make EXE output:
	#MAKE_EXE#

DSEG	SEGMENT 'DATA'

								;	bARR is for input
	bARR		DB	'1',10,15,13,7,9,8,0,'2',',','a','9','z','7','.','/','9','4','8','t'
								;	bARRSize is the size of bARR
	bARRSize	EQU	20
								;	bOutARR is for output
	bOutARR		DB	20 DUP(?)
								;	bOutSize is for output size
	bOutSize	DB	0

DSEG	ENDS

CSEG	SEGMENT 'CODE'

;*******************************************

START	PROC	FAR
								;	Store return address to OS:
	PUSH	DS					;
	MOV		AX, 0				;
	PUSH	AX					;
    							;
								;	set segment registers:
	MOV	AX, DSEG				;
	MOV	DS, AX					;
	MOV	ES, AX					;
								;--------ALGORITHM PART--------
								;
	XOR	BX, BX					;	BX = 0
	MOV	DH, 0					;	bARR pointer
	MOV	DL, 0					;	bOutARR pointer = bOutSize
	MOV	CX, bARRSize			;	CX = bARRSize for loop times
								;
JUDGE_NUMBER:					;	JUDGE whether it is a number. if(bARR[now] >= '0' && bARR[now] <= '9')
								;	'0' stands for 48, '9' stands for 57.
	MOV	BL, DH					;	BX->bARR[now]
	CMP	[bARR+BX], '0'			;	
	JL	EXIT_JUDGE				;	if bARR[now] < '0', can't be a number or a character, exit
	CMP	[bARR+BX], '9'			;
	JG	JUDGE_UPCASE_CHARACTER	;	if bARR[now] > '9' then judge whether it's a upper case character
	MOV	AL, [bARR+BX]			;	AL is for temporary register
	MOV	BL, DL					;	BX->bOutARR[now]
	MOV	[bOutARR+BX], AL		;	Put bARR[now] into bOutARR
	INC	DL						;	bOutSize++
	JMP	EXIT_JUDGE				;	endif
JUDGE_UPCASE_CHARACTER:			;	JUDGE whether it is a upper case character. if(bARR[now] >= 'A' && bARR[now] <= 'Z')
								;	'A' stands for 65, 'Z' stands for 87
	MOV	BL, DH					;	BX->bARR[now]
	CMP	[bARR+BX], 'A'			;
	JL	EXIT_JUDGE				;	if bARR[now] > '9' && bARR[now] < 'A' then it can't be a number or a character, exit
	CMP	[bARR+BX], 'Z'			;
	JG	JUDGE_LOWCASE_CHARACTER	;	if bARR[now] > 'Z' then judge whethre it's a lower case character
	MOV	AL, [bARR+BX]			;	AL is for temporary register
	MOV	BL, DL					;	BX->bOutARR[now]
	MOV	[bOutARR+BX], AL		;	Put bARR[now] into bOutARR
	INC	DL						;	bOutSize++
	JMP	EXIT_JUDGE				;	endif
JUDGE_LOWCASE_CHARACTER:		;	JUDGE whether it is a lower case character. if(bARR[now] >= 'a' && bARR[now] <= 'z');
								;	'a' stands for 97, 'z' stands for 122
	MOV	BL, DH					;	BX->bARR[now]
	CMP	[bARR+BX], 'a'			;
	JL	EXIT_JUDGE				;	if bARR[now] > 'Z' && bARR[now] < 'a' then it can't be a number or a character, exit
	CMP	[bARR+BX], 'z'			;
	JG	EXIT_JUDGE				;	if bARR[now] > 'z' then it can't be number or a character, exit
	MOV	AL, [bARR+BX]			;	AL is for temporary register
	MOV	BL, DL					;	BX->bOutARR[now]
	MOV	[bOutARR+BX], AL		;	Put bARR[now] into bOutARR
	INC	DX						;	bOutSize++
EXIT_JUDGE:						;	endif
	INC	DH						;	next bARR
	DEC	CX						;
	JNZ	JUDGE_NUMBER			;	if not finished, loop
								;
PRINT:							;	print the bOutARR
	MOV	bOutSize, DL			;	Modify the bOutSize
	MOV	CL, bOutSize			;	the size to print
	LEA	BX, bOutARR				;	BX->bOutARR[0]
PRINT_DIGIT:
	MOV	DX, [BX]				;	DX is the number for printing
	INC	BX						;	BX->bOutARR[NEXT]
	MOV	AH, 02H					;	Call print in BIOS
	INT	21H						;	Print [BX]
	DEC	CL						;
	JNZ	PRINT_DIGIT				;	if not fin, loop
	
	
; return to operating system:
	RET
START	ENDP

;*******************************************

CSEG	ENDS 

	END	START    ; set entry point.
