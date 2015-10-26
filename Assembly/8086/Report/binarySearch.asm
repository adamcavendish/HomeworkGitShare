;Data Segment
DATAS SEGMENT
											;	ARR���ڼ�¼��Ҫ���������
	ARR		DB	'3','2','5','7','4','8','1','6','9','0', '$'
	ARRSize		EQU	10						;	���ڼ�¼ARR����Ĵ�С
	NUM		DB	'7'							;	NUM��ʾ��ҪѰ�ҵ�ֵ
											;
	ARRLOW	DW	'$'							;	���ַ�����ָ��
	ARRHIGH	DW	'$'							;	���ַ�����ָ��											
											;	FoundText��ʾ�ҵ����޸ĵ�16��λ�ÿ���������ҵ���λ��
											;	NFoundText��ʾû���ҵ��������޸�
	FoundText	DB	"FOUND!", 10, '$'
	NFoundText	DB	"NOT FOUND!", 10, '$'
DATAS ENDS
											;
;Code Segment
CODES SEGMENT
start:
	ASSUME CS:CODES, DS:DATAS				;	Assembly Init
	MOV 	AX, DATAS						;
	MOV 	DS, AX							;
											;	Algorithm: First Do the bubbleSort descending, then the binarySearch
	MOV	CX, ARRSize							;	bubbleSort--OuterLoop
	DEC	CX									;	Don't have to the first time
	XOR	AH, AH								;	INIT AH, AH = 0����AH��Ϊ��ѭ�����Ƿ���й������ı�־
BubbleSortOuterLoop:						;
	MOV	DX, CX								;	InnerLoop counter DX
	LEA	BX, ARR								;	BX = ARR[0]
	CMP	AH, 1								;	AH��ΪInnerLoop���Ƿ�swap�ı�־��
	JE	binarySearch						;���Ϊ1, ��no swap�����Ϊ0��swapped��
	MOV	AH, 1								;��AHΪ1ʱֱ��End Sorting. ÿ�ν���InnerLoop����1							
BubbleSortInnerLoop:						;
	MOV	AL, [BX]							;	AL����ʱ���������ڱȽ�
	CMP	AL, [BX+1]							;	compare([BX],[BX+1]). 1[BX]��[BX+1]�÷�һ��
	JGE	NExchange							;	no swap when ">="
	XCHG	AL, [BX+1]						;	swap([BX], [BX+1])
	MOV	[BX], AL							;	���������ʱ����д���ڴ�
	XOR	AH, AH								;	��ѭ�������˽��������ǽ�AH��0����Ҫ������һ����ѭ��
NExchange:									;
	INC	BX									;	BX -> ++ARR
	DEC	DX									;	jump to the InnerLoop
	JNZ	BubbleSortInnerLoop					;
	DEC	CX									;	jump to the OuterLoop
	JNZ	BubbleSortOuterLoop					;
binarySearch:								;	binarySearch, Initiation
	MOV	AX, 0								;	init ARRLOW
	MOV	ARRLOW, AX							;
	MOV	AX, ARRSize-1						;	init ARRHIGH
	MOV ARRHIGH, AX							;
	MOV	AL, NUM								;	AL = NUM
	MOV	BX, ARRLOW								;
	CMP	AL, [ARR+BX]						;	if	NUM == ARR[0]
	JE	binarySearch_Found					;	Providentially, We found it!!
	JG	OutputNFound						;	if NUM > ARR[0], can't be found, exit
	ADD	BX, ARRHIGH							;
	CMP	AL, [ARR+BX]						;	if NUM == ARR[ARRSize-1]
	JE	binarySearch_Found					;	Clairvoyant!!
	JL	OutputNFound						;	if NUM < ARR[ARRSize-1], can't be found, exit
	SHR	BX, 1								;	BX means Mid = (ARRLOW + ARRHIGH)/2
binarySearch_L1:							;
	CMP	AL, [ARR+BX]						;	Compare NUM and ARR[dwMid]
	JE	binarySearch_Found					;	if Found jump to Edit the found location
	JG	binarySearch_Greater				;	if NUM > ARR[Mid], jump
;	if dwNUM < dwARR[dwMid]
	INC	BX									;	if NUM < ARR[Mid], then ARRLOW = Mid + 1
	MOV	ARRLOW, BX							;
	ADD	BX, ARRHIGH							;	then Mid = (ARRLOW + ARRHIGH) / 2
	SHR	BX, 1								;
	MOV	DX, ARRLOW								;	if ARRLOW > ARRHIGH then exit
	CMP	DX, ARRHIGH							;
	JG	OutputNFound						;
	JMP	binarySearch_L1						;
binarySearch_Greater:						;
	DEC	BX									;	if NUM > ARR[dwMid], then ARRHIGH = Mid - 1
	MOV	ARRHIGH, BX							;
	ADD	BX, ARRLOW								;	then Mid = (ARRHIGH + ARRLOW) / 2
	SHR	BX, 1								;
	MOV	DX, ARRLOW								;	if ARRLOW > ARRHIGH then exit
	CMP	DX, ARRHIGH							;
	JG	OutputNFound						;
	JMP	binarySearch_L1						;
binarySearch_Found:							;
	LEA	DX, FoundText						;	Output Found
	JMP	Output								;
OutputNFound:								;	Output Not Found
	LEA	DX, NFoundText						;
	
Output:										;	Output
	MOV	AH, 09H								;
	INT	21H									;
	MOV	AH, 4CH								;	Program ENDS Here
	INT	21H									;
CODES ENDS
	end start



