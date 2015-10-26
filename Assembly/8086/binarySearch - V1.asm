;	AUTHOR		Adam Basfop Cavendish
;	DATE		2012/05/02
;	VERSION		1.00
;	FILE		binarySearch.ASM

;	@file		/binarySearch.asm
;	���ֲ��ң��ȶ����ݽ���ð�������ٽ��ж��ֲ���
;


;Data Segment
DATAS SEGMENT
											;	ARR���ڼ�¼��Ҫ���������
	ARR		DB	"3581769042", '$'			;
	ARRSize		EQU	10						;	���ڼ�¼ARR����Ĵ�С
	NUM		DB	'7'							;	NUM��ʾ��ҪѰ�ҵ�ֵ
											;
											;	FoundText��ʾ�ҵ����޸ĵ�16��λ�ÿ���������ҵ���λ��
											;	NFoundText��ʾû���ҵ��������޸�
	FoundText	DB	"FOUND! It's at  ", 10, '$'
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
	XOR	CL, CL								;	CL stands for "low", init for 0
	LEA	BX, ARR								;	BX = ARR[0]
	MOV	AL, NUM								;	AL = NUM
	CMP	AL, [BX]							;
	JE	binarySearch_FoundBL				;	Providentially, We found it!!
	JG	OutputNFound						;	NUM > ARR[0], can't be found��exit
	MOV	CH, ARRSize-1						;	CH stands for "high", init for ARRSize-1
	MOV	BL, CH								;
	CMP	AL, [BX]							;
	JE	binarySearch_FoundBL				;	Clairvoyant!!!!
	JL	OutputNFound						;	NUM < ARR[ARRSize-1], can't be found, exit
											;
	ADD	BL, CH								;	BL stands for "mid"
	SHR	BL, 1								;	mid = (low + high) / 2
binarySearch_L1:							;
	CMP	AL, [BX]							;	Compare NUM and ARR[mid]
	JE	binarySearch_FoundBL				;	if Found jump to Edit the found location
	JG	binarySearch_Greater				;	if NUM > ARR[mid], jump
	MOV	CL, BL								;	if NUM < ARR[mid], then low = mid + 1
	INC	CL									;
	ADD	BL, CH								;	then mid = (low + high) / 2
	SHR	BL, 1								;
	CMP	CL, CH								;	if low > high then exit
	JG	OutputNFound						;
	JMP	binarySearch_L1						;
binarySearch_Greater:						;
	MOV	CH, BL								;	if NUM > ARR[mid], then high = mid - 1
	DEC	CH									;
	ADD	BL, CL								;	then mid = (high + low) / 2
	SHR	BL, 1								;
	CMP	CL, CH								;	if low > high then exit
	JG	OutputNFound						;
	JMP	binarySearch_L1						;
binarySearch_FoundBL:						;
	ADD	BL, 30H								;	Turn BL into ASCII
	MOV	[FoundText+16], BL					;	Edit the Found Location for Output
	LEA	DX, FoundText						;	Output Found
	JMP	Output								;
OutputNFound:								;
	LEA	DX, NFoundText						;	Output Not Found
Output:										;	Output
	MOV	AH, 09H								;
	INT	21H									;
	MOV	AH, 4CH								;	Program ENDS Here
	INT	21H									;
CODES ENDS
	end start
