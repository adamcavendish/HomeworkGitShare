;Data Segment
DATAS SEGMENT
											;	ARR用于记录需要排序的数组
	ARR		DB	'3','2','5','7','4','8','1','6','9','0', '$'
	ARRSize		EQU	10						;	用于记录ARR数组的大小
	NUM		DB	'7'							;	NUM表示需要寻找的值
											;
	ARRLOW	DW	'$'							;	二分法的左指针
	ARRHIGH	DW	'$'							;	二分法的右指针											
											;	FoundText表示找到，修改第16个位置可以输出查找到的位置
											;	NFoundText表示没有找到，不用修改
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
	XOR	AH, AH								;	INIT AH, AH = 0，将AH作为内循环中是否进行过交换的标志
BubbleSortOuterLoop:						;
	MOV	DX, CX								;	InnerLoop counter DX
	LEA	BX, ARR								;	BX = ARR[0]
	CMP	AH, 1								;	AH作为InnerLoop中是否swap的标志，
	JE	binarySearch						;如果为1, 则no swap，如果为0则swapped。
	MOV	AH, 1								;当AH为1时直接End Sorting. 每次进入InnerLoop先置1							
BubbleSortInnerLoop:						;
	MOV	AL, [BX]							;	AL是临时变量，用于比较
	CMP	AL, [BX+1]							;	compare([BX],[BX+1]). 1[BX]与[BX+1]用法一致
	JGE	NExchange							;	no swap when ">="
	XCHG	AL, [BX+1]						;	swap([BX], [BX+1])
	MOV	[BX], AL							;	交换后的临时变量写入内存
	XOR	AH, AH								;	内循环进行了交换，于是将AH置0，需要进行下一次外循环
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



