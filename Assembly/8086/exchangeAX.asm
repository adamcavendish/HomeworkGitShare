DATAS SEGMENT
	BC DB "Before Change",13,10,'$'
	AC DB "After Change",13,10,'$'
	;NUM DB 0ABCDH
DATAS ENDS

STACKS SEGMENT
	
STACKS ENDS

CODES SEGMENT
	ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
	;INIT
	MOV AX,DATAS
	MOV DS,AX

	MOV AX, 0ABCDH
	XCHG AH, AL
	MOV CL, 4
	ROL AH, CL
	ROL AL, CL
	;Code Ends
	MOV AH,4CH
	INT 21H
CODES ENDS
	END START





