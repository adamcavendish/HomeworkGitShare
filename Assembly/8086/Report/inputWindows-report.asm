;TITLE   8086 Code Template (for EXE file)

;       AUTHOR          emu8086
;       DATE            ?
;       VERSION         1.00
;       FILE            ?.ASM

; 8086 Code Template

; Directive to make EXE output:
       ;#MAKE_EXE#

DSEG    SEGMENT

	titlebarSize		equ	1						;��������С
	frameSize			equ	1						;�߿��С
	titleOffsetVal		equ	2						;��������ƫ����
	screenWidth			equ	80						;Dos���ڿ��
	screenHeight		equ	25						;Dos���ڸ߶�

	Wnd1LeftTopRow		equ	3						;����1���Ͻ��к�
	Wnd1LeftTopCol		equ 3						;����1���Ͻ��к�
	Wnd1Width			equ 30						;����1���
	Wnd1Height			equ	5						;����1�߶�
	Wnd1Title			db	'Windows 1', '$'		;����1������
	Wnd1CursorRow		db	Wnd1LeftTopRow			;����1�����λ��
	Wnd1CursorCol		db	Wnd1LeftTopCol			;����1�����λ��
	
	Wnd2LeftTopRow		equ	3						;����2���Ͻ��к�
	Wnd2LeftTopCol		equ 40						;����2���Ͻ��к�
	Wnd2Width			equ 30						;����2���
	Wnd2Height			equ	5						;����2�߶�
	Wnd2Title			db	'Windows 2', '$'		;����2������
	Wnd2CursorRow		db	Wnd2LeftTopRow			;����2�����λ��
	Wnd2CursorCol		db	Wnd2LeftTopCol			;����2�����λ��
	
	Wnd3LeftTopRow		equ	14						;����3���Ͻ��к�
	Wnd3LeftTopCol		equ 3						;����3���Ͻ��к�
	Wnd3Width			equ 67						;����3���
	Wnd3Height			equ	8						;����3�߶�
	Wnd3Title			db	'Windows 3', '$'		;����3������
	Wnd3CursorRow		db	Wnd3LeftTopRow			;����3�����λ��
	Wnd3CursorCol		db	Wnd3LeftTopCol			;����3�����λ��
	
	InputLetter			db	'$'						;������ַ�
	CurrentWnd			db	1						;�������ڵ�Window

	OpenWndLeftTopRow	db	'$'						;OpenWnd��������--���Ͻ��к�
	OpenWndLeftTopCol	db	'$'						;OpenWnd��������--���Ͻ��к�
	OpenWndWidth		db	'$'						;OpenWnd��������--���ڿ��
	OpenWndHeight		db	'$'						;OpenWnd��������--���ڸ߶�
	pOpenWndTitle		dw	'$'						;OpenWnd��������--�����������ַ���ָ��

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
;@param	OpenWndLeftTopRow	OpenWnd��������--���Ͻ��к�
;@param	OpenWndLeftTopCol	OpenWnd��������--���Ͻ��к�
;@param	OpenWndWidth		OpenWnd��������--���ڿ��
;@param	OpenWndHeight		OpenWnd��������--���ڸ߶�
;@param	pOpenWndTitle		OpenWnd��������--�����������ַ���ָ��
OpenWnd	proc	near
	;*******************************************
	;Draw the frame
	;
	;BIOS�����Ͼ���յ��� INT 10H -- AH = 06H
	;	AL=�Ͼ�����(Ϊ0ʱ�����������), BH=����������
	;	CH:CL=���Ͻ��к�:�к�, DH:DL=���½��к�:�к�
	mov		ah, 06H
	mov		al, 00H						;clear the frame
	mov		bh, 70H						;�������Ϊ������ɫ��ǰ����ɫ
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
	mov		bh, 37H						;���ñ�����Ϊ��������ɫ��ǰ����ɫ
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
	;BIOS�ù��λ�õ��� INT 10H -- AH = 02H
	;	BH=ҳ��, DH=�к�, DL=�к�
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
	mov		bh, 0F0H						;���������岿��Ϊ������ɫ��ǰ����ɫ
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
	mov		ah, 01H							;�Ӽ�������һ���ַ���������(֧��Ctrl+C��Ctrl+Break����)���ַ�����λ��AL��
	int		21H
	call	TestLetter
	mov		InputLetter, al
	
	ret
GetLetter	endp
;*******************************************

;*******************************************
PrintLetter	proc	near
	;*******************************************
	;BIOS�ڹ��λ��ֻ��ʾ�ַ��������Ե��� -- INT 10H, AH = 0EH
	;	AL=�ַ�, BL=ǰ��ɫ
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
;@param	CH	��Ҫ�Ͼ�Ĵ��ڵ����Ͻ��к�
;@param	CL	��Ҫ�Ͼ�Ĵ��ڵ����Ͻ��к�
;@param	DH	��Ҫ�Ͼ�Ĵ��ڵĸ߶�Height
;@param	DL	��Ҫ�Ͼ�Ĵ��ڵĿ��Width
ScrollUp	proc	near
	mov		ah, 06H
	mov		al, 1							;�Ͼ�1��
	mov		bh, 0F0H						;������ɫ��ǰ����ɫ
	add		dh, ch
	add		dl, cl
	int		10H
	
	ret
ScrollUp	endp
;*******************************************

CSEG    ENDS 

        END    START    ; set entry point.

