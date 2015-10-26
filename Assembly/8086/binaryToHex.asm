DATAS SEGMENT
			NUM DW 0ABCDH
DATAS ENDS

CODES SEGMENT
			ASSUME CS:CODES,DS:DATAS
START:
			;INIT
			MOV AX,DATAS
			MOV DS,AX
	
			MOV BX,NUM		;INIT BX
			MOV CH, 4		;INIT the times to loop
ROTATE:		MOV CL,4		;set count to 4 bits
			ROL BX,CL		;left digit to right
			MOV AL,BL		;move to AL
			AND AL,0FH		;mask off left digit
			ADD AL,30H		;convert hex to ASCII
			CMP	AL,3AH		;is it > 9?
			JL	PRINTIT		;if it is < 9.(JL jump if less. for signed)
			ADD AL,7H		;this digit is A to F
PRINTIT:	MOV	DL,AL		;put ASCII char in DL
			MOV	AH,2		;display output function
			INT 21H			;call DOS
			DEC CH			;done 4 digits?
			jnz rotate		;not yet
	
			;END
			MOV AH,4CH
    		INT 21H
CODES ENDS
			END START
