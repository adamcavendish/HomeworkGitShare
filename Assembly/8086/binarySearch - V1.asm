;	AUTHOR		Adam Basfop Cavendish
;	DATE		2012/05/02
;	VERSION		1.00
;	FILE		binarySearch.ASM

;	@file		/binarySearch.asm
;	二分查找，先对数据进行冒泡排序，再进行二分查找
;


;Data Segment
DATAS SEGMENT
											;	ARR用于记录需要排序的数组
	ARR		DB	"3581769042", '$'			;
	ARRSize		EQU	10						;	用于记录ARR数组的大小
	NUM		DB	'7'							;	NUM表示需要寻找的值
											;
											;	FoundText表示找到，修改第16个位置可以输出查找到的位置
											;	NFoundText表示没有找到，不用修改
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
	XOR	CL, CL								;	CL stands for "low", init for 0
	LEA	BX, ARR								;	BX = ARR[0]
	MOV	AL, NUM								;	AL = NUM
	CMP	AL, [BX]							;
	JE	binarySearch_FoundBL				;	Providentially, We found it!!
	JG	OutputNFound						;	NUM > ARR[0], can't be found，exit
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
