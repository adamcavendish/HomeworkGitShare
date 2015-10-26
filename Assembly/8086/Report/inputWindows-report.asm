;TITLE   8086 Code Template (for EXE file)

;       AUTHOR          emu8086
;       DATE            ?
;       VERSION         1.00
;       FILE            ?.ASM

; 8086 Code Template

; Directive to make EXE output:
       ;#MAKE_EXE#

DSEG    SEGMENT

	titlebarSize		equ	1						;标题栏大小
	frameSize			equ	1						;边框大小
	titleOffsetVal		equ	2						;标题文字偏移量
	screenWidth			equ	80						;Dos窗口宽度
	screenHeight		equ	25						;Dos窗口高度

	Wnd1LeftTopRow		equ	3						;窗口1左上角行号
	Wnd1LeftTopCol		equ 3						;窗口1左上角列号
	Wnd1Width			equ 30						;窗口1宽度
	Wnd1Height			equ	5						;窗口1高度
	Wnd1Title			db	'Windows 1', '$'		;窗口1标题栏
	Wnd1CursorRow		db	Wnd1LeftTopRow			;窗口1光标行位置
	Wnd1CursorCol		db	Wnd1LeftTopCol			;窗口1光标列位置
	
	Wnd2LeftTopRow		equ	3						;窗口2左上角行号
	Wnd2LeftTopCol		equ 40						;窗口2左上角列号
	Wnd2Width			equ 30						;窗口2宽度
	Wnd2Height			equ	5						;窗口2高度
	Wnd2Title			db	'Windows 2', '$'		;窗口2标题栏
	Wnd2CursorRow		db	Wnd2LeftTopRow			;窗口2光标行位置
	Wnd2CursorCol		db	Wnd2LeftTopCol			;窗口2光标列位置
	
	Wnd3LeftTopRow		equ	14						;窗口3左上角行号
	Wnd3LeftTopCol		equ 3						;窗口3左上角列号
	Wnd3Width			equ 67						;窗口3宽度
	Wnd3Height			equ	8						;窗口3高度
	Wnd3Title			db	'Windows 3', '$'		;窗口3标题栏
	Wnd3CursorRow		db	Wnd3LeftTopRow			;窗口3光标行位置
	Wnd3CursorCol		db	Wnd3LeftTopCol			;窗口3光标列位置
	
	InputLetter			db	'$'						;输入的字符
	CurrentWnd			db	1						;现在所在的Window

	OpenWndLeftTopRow	db	'$'						;OpenWnd函数参数--左上角行号
	OpenWndLeftTopCol	db	'$'						;OpenWnd函数参数--左上角列号
	OpenWndWidth		db	'$'						;OpenWnd函数参数--窗口宽度
	OpenWndHeight		db	'$'						;OpenWnd函数参数--窗口高度
	pOpenWndTitle		dw	'$'						;OpenWnd函数参数--标题栏文字字符串指针

DSEG    ENDS

SSEG    SEGMENT
;
SSEG    ENDS

CSEG    SEGMENT

;*******************************************

START   PROC    FAR
	ASSUME CS:CSEG, DS:DSEG, SS:SSEG
; Store return address to OS:
    PUSH    DS
    MOV     AX, 0
    PUSH    AX

; set segment registers:
    MOV     AX, DSEG
    MOV     DS, AX
    MOV     ES, AX

;Init the DOS
	mov		ah, 06H
	mov		al, 0
	mov		ch, 0
	mov		cl, 0
	mov		dh, screenHeight-1
	mov		dl, screenWidth-1
	int		10H

;Draw first windows
	mov		al, Wnd1LeftTopRow					
	mov		OpenWndLeftTopRow, al
	mov		al, Wnd1LeftTopCol
	mov		OpenWndLeftTopCol, al
	mov		al, Wnd1Width
	mov		OpenWndWidth, al
	mov		al, Wnd1Height
	mov		OpenWndHeight, al
	mov		bx, offset Wnd1Title
	mov		pOpenWndTitle, bx
	call	OpenWnd
;Draw second windows
	mov		al, Wnd2LeftTopRow					
	mov		OpenWndLeftTopRow, al
	mov		al, Wnd2LeftTopCol
	mov		OpenWndLeftTopCol, al
	mov		al, Wnd2Width
	mov		OpenWndWidth, al
	mov		al, Wnd2Height
	mov		OpenWndHeight, al
	mov		bx, offset Wnd2Title
	mov		pOpenWndTitle, bx
	call	OpenWnd
;Draw third windows
	mov		al, Wnd3LeftTopRow					
	mov		OpenWndLeftTopRow, al
	mov		al, Wnd3LeftTopCol
	mov		OpenWndLeftTopCol, al
	mov		al, Wnd3Width
	mov		OpenWndWidth, al
	mov		al, Wnd3Height
	mov		OpenWndHeight, al
	mov		bx, offset Wnd3Title
	mov		pOpenWndTitle, bx
	call	OpenWnd
;set the cursor to Default position
	mov		ah, 02H
	mov		bh, 00H
	mov		dh, Wnd1CursorRow
	mov		dl, Wnd1CursorCol
	int		10H
;Input a character
input:
	call	GetLetter
	call	SyncLetter
	jmp		input
; return to operating system:
    RET
START   ENDP

;*******************************************

;*******************************************
;Open a window
;@param	OpenWndLeftTopRow	OpenWnd函数参数--左上角行号
;@param	OpenWndLeftTopCol	OpenWnd函数参数--左上角列号
;@param	OpenWndWidth		OpenWnd函数参数--窗口宽度
;@param	OpenWndHeight		OpenWnd函数参数--窗口高度
;@param	pOpenWndTitle		OpenWnd函数参数--标题栏文字字符串指针
OpenWnd	proc	near
	;*******************************************
	;Draw the frame
	;
	;BIOS窗口上卷清空调用 INT 10H -- AH = 06H
	;	AL=上卷行数(为0时清除窗口内容), BH=卷入行属性
	;	CH:CL=左上角行号:列号, DH:DL=右下角行号:列号
	mov		ah, 06H
	mov		al, 00H						;clear the frame
	mov		bh, 70H						;设置外框为背景灰色，前景白色
	mov		ch, OpenWndLeftTopRow
	sub		ch, frameSize
	mov		cl, OpenWndLeftTopCol
	sub		cl, frameSize
	mov		dh, OpenWndLeftTopRow
	add		dh, OpenWndHeight
	add		dh, frameSize
	mov		dl, OpenWndLeftTopCol
	add		dl, OpenWndWidth
	add		dl, frameSize
	int		10H
	;*******************************************
	;
	;*******************************************
	;Draw the titlebar
	mov		ah, 06H
	mov		al, 00H						;clear the titlebar
	mov		bh, 37H						;设置标题栏为背景湖蓝色，前景灰色
	mov		ch, OpenWndLeftTopRow
	sub		ch, frameSize
	sub		ch, titlebarSize
	mov		cl, OpenWndLeftTopCol
	sub		cl, frameSize
	mov		dh, OpenWndLeftTopRow
	sub		dh, frameSize
	dec		dh
	mov		dl, OpenWndLeftTopCol
	add		dl, OpenWndWidth
	add		dl, frameSize
	int		10H
	;*******************************************
	;
	;*******************************************
	;set the cursor
	;BIOS置光标位置调用 INT 10H -- AH = 02H
	;	BH=页号, DH=行号, DL=列号
	mov		ah, 02H
	mov		bh, 00H
	mov		dh, OpenWndLeftTopRow
	sub		dh, titlebarSize
	dec		dh
	mov		dl, OpenWndLeftTopCol
	add		dl, titleOffsetVal
	int		10H
	;*******************************************
	;
	;*******************************************
	;Print the title
	mov		ah, 09H
	mov		dx, pOpenWndTitle
	int		21H
	;*******************************************
	;
	;*******************************************
	;Draw the main part
	mov		ah, 06H
	mov		al, 00H							;clear the main part
	mov		bh, 0F0H						;设置主窗体部分为背景白色，前景黑色
	mov		ch, OpenWndLeftTopRow
	mov		cl, OpenWndLeftTopCol
	mov		dh, OpenWndLeftTopRow
	add		dh, OpenWndHeight
	mov		dl, OpenWndLeftTopCol
	add		dl, OpenWndWidth
	int		10H
	;*******************************************
	
	ret
OpenWnd	endp
;*******************************************

;*******************************************
GetLetter	proc	near
	mov		ah, 01H							;从键盘输入一个字符，不回显(支持Ctrl+C和Ctrl+Break跳出)；字符内容位于AL中
	int		21H
	call	TestLetter
	mov		InputLetter, al
	
	ret
GetLetter	endp
;*******************************************

;*******************************************
PrintLetter	proc	near
	;*******************************************
	;BIOS在光标位置只显示字符及其属性调用 -- INT 10H, AH = 0EH
	;	AL=字符, BL=前景色
	mov		ah, 0EH
	mov		al, InputLetter
	int		10H
	
	ret
PrintLetter	endp
;*******************************************

;*******************************************
SyncLetter	proc	near
	;*******************************************
	;set the cursor to Windows 1
	;mov		ah, 02H
	;mov		bh, 00H
	;mov		dh, Wnd1CursorRow
	;mov		dl, Wnd1CursorCol
	;int		10H
	;*******************************************
	;call	PrintLetter
	
	;*******************************************
	;set the cursor to Windows 2
	;mov		ah, 02H
	;mov		bh, 00H
	;mov		dh, Wnd2CursorRow
	;mov		dl, Wnd2CursorCol
	;int		10H
	;*******************************************
	;call	PrintLetter
	
	;*******************************************
	;set the cursor to Windows 3
	mov		ah, 02H
	mov		bh, 00H
	mov		dh, Wnd3CursorRow
	mov		dl, Wnd3CursorCol
	int		10H
	;*******************************************
	call	PrintLetter
	
	;*******************************************
	;change Cursor Info for All the Windows
	mov		ah, CurrentWnd
	cmp		ah, 1
	je		ChangeCursor1
	cmp		ah, 2
	je		ChangeCursor2
	cmp		ah, 3
	je		ChangeCursor3
	
	ChangeCursor1:
	mov		ah, Wnd1CursorCol				;Column to the limit?
	mov		al, Wnd1LeftTopCol
	add		al, Wnd1Width
	cmp		ah, al
	jne		Wnd1ColEdit
	mov		ah, Wnd1CursorRow				;Row also to the limit?
	mov		al, Wnd1LeftTopRow
	add		al, Wnd1Height
	cmp		ah, al
	jne		Wnd1RowEdit
	mov		ch, Wnd1LeftTopRow
	mov		cl, Wnd1LeftTopCol
	mov		dh, Wnd1Height
	mov		dl, Wnd1Width
	call	ScrollUp
	mov		ah, Wnd1LeftTopCol-1
	Wnd1ColEdit:
		inc		ah
		mov		Wnd1CursorCol, ah
		jmp		ChangeCursor3
	Wnd1RowEdit:
		inc		ah
		mov		Wnd1CursorRow, ah
		mov		ah, Wnd1LeftTopCol
		mov		Wnd1CursorCol, ah
		jmp		ChangeCursor3
	
	ChangeCursor2:
	mov		ah, Wnd2CursorCol				;Column to the limit?
	mov		al, Wnd2LeftTopCol
	add		al, Wnd1Width
	cmp		ah, al
	jne		Wnd2ColEdit
	mov		ah, Wnd2CursorRow				;Row also to the limit?
	mov		al, Wnd2LeftTopRow
	add		al, Wnd2Height
	cmp		ah, al
	jne		Wnd2RowEdit
	mov		ch, Wnd2LeftTopRow
	mov		cl, Wnd2LeftTopCol
	mov		dh, Wnd2Height
	mov		dl, Wnd2Width
	call	ScrollUp
	mov		ah, Wnd2LeftTopCol-1
	Wnd2ColEdit:
		inc		ah
		mov		Wnd2CursorCol, ah
		jmp		ChangeCursor3
	Wnd2RowEdit:
		inc		ah
		mov		Wnd2CursorRow, ah
		mov		ah, Wnd2LeftTopCol
		mov		Wnd2CursorCol, ah
		jmp		ChangeCursor3
	
	ChangeCursor3:
	mov		ah, Wnd3CursorCol				;Column to the limit?
	mov		al, Wnd3LeftTopCol
	add		al, Wnd3Width
	cmp		ah, al
	jne		Wnd3ColEdit
	mov		ah, Wnd3CursorRow				;Row also to the limit?
	mov		al, Wnd3LeftTopRow
	add		al, Wnd3Height
	cmp		ah, al
	jne		Wnd3RowEdit
	mov		ch, Wnd3LeftTopRow
	mov		cl, Wnd3LeftTopCol
	mov		dh, Wnd3Height
	mov		dl, Wnd3Width
	call	ScrollUp
	mov		ah, Wnd3LeftTopCol-1
	Wnd3ColEdit:
		inc		ah
		mov		Wnd3CursorCol, ah
		jmp		SyncLetterReturn
	Wnd3RowEdit:
		inc		ah
		mov		Wnd3CursorRow, ah
		mov		ah, Wnd3LeftTopCol
		mov		Wnd3CursorCol, ah
	;*******************************************
SyncLetterReturn:
	call	SetToCurrWnd
	ret
SyncLetter	endp
;*******************************************

;*******************************************
TestLetter	proc	near
	cmp		al, 0							;if input is a function key
	jne		TestLetterReturn2
	mov		ah, 08H
	int		21H
	cmp		al, 3BH							;F1?
	je		CHGto1
	cmp		al, 3CH							;F2?
	je		CHGto2
	cmp		al, 3DH							;F3?
	je		CHGto3
	jmp		TestLetterReturn1
	CHGto1:
		mov		ah, 1
		jmp		CHG
	CHGto2:
		mov		ah, 2
		jmp		CHG
	CHGto3:
		mov		ah, 3
	CHG:
		mov		CurrentWnd, ah
		call	SetToCurrWnd
		jmp		TestLetterReturn1
	TestLetterReturn1:
		call	GetLetter
	TestLetterReturn2:	
		ret
TestLetter	endp
;*******************************************

;*******************************************
SetToCurrWnd	proc	near
;Change back to Curent Windows
	mov		ah, CurrentWnd
	cmp		ah, 1
	je		CurrWnd1
	cmp		ah, 2
	je		CurrWnd2
	cmp		ah, 3
	je		CurrWnd3
	CurrWnd1:
		mov		ah, 02H
		mov		bh, 00H
		mov		dh, Wnd1CursorRow
		mov		dl, Wnd1CursorCol
		int		10H
		jmp		SetToCurrWndReturn
	CurrWnd2:
		mov		ah, 02H
		mov		bh, 00H
		mov		dh, Wnd2CursorRow
		mov		dl, Wnd2CursorCol
		int		10H
		jmp		SetToCurrWndReturn
	CurrWnd3:
		mov		ah, 02H
		mov		bh, 00H
		mov		dh, Wnd3CursorRow
		mov		dl, Wnd3CursorCol
		int		10H
		jmp		SetToCurrWndReturn
	SetToCurrWndReturn:
		ret
SetToCurrWnd	endp
;*******************************************

;*******************************************
;Scroll Up One Line
;@param	CH	需要上卷的窗口的左上角行号
;@param	CL	需要上卷的窗口的左上角列号
;@param	DH	需要上卷的窗口的高度Height
;@param	DL	需要上卷的窗口的宽度Width
ScrollUp	proc	near
	mov		ah, 06H
	mov		al, 1							;上卷1行
	mov		bh, 0F0H						;背景白色，前景黑色
	add		dh, ch
	add		dl, cl
	int		10H
	
	ret
ScrollUp	endp
;*******************************************

CSEG    ENDS 

        END    START    ; set entry point.

