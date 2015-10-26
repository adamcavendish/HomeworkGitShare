;删除数组中一元素的程序

;Delete the value in AX from an unordered list in the extra
;	segment, if that value is in the list.
;Inputs: (DI)=starting address of the list
;	First location of the list = Length of list(words)

DATAS SEGMENT
		ARR			DB	1,3,2,4,5,6,7,9,8,0
		LEN			DB	10
		NUM			DB	3
		DEL			DB	"Number Deleted!",10,'$'
		NOTFOUND	DB	"Number Not Found!",10,'$'
DATAS ENDS

CODES SEGMENT
		ASSUME CS:CODES, DS:DATAS
START:
		;INIT
		MOV	AX,DATAS
		MOV	DS,AX
		;Get the length of the array
		MOV CL,LEN
		;Get the pointer to the array
		MOV AL,ARR
		INC AL
		
		ADD AL,30H
		MOV DL,AL
		MOV AH,02H
		INT 21H
		
		MOV AH,4CH
		INT 21H
	
CODES ENDS
	END START







