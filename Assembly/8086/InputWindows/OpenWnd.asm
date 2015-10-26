DSEG SEGMENT
	
	titlebarSize		equ	1						;标题栏大小
	frameSize			equ	1						;边框大小
	titleOffsetVal		equ	2						;标题文字偏移量
	screenWidth			equ	80						;Dos窗口宽度
	screenHeight		equ	25						;Dos窗口高度

	OpenWndLeftTopRow	db	'$'						;OpenWnd函数参数--左上角行号
	OpenWndLeftTopCol	db	'$'						;OpenWnd函数参数--左上角列号
	OpenWndWidth		db	'$'						;OpenWnd函数参数--窗口宽度
	OpenWndHeight		db	'$'						;OpenWnd函数参数--窗口高度
	pOpenWndTitle		dw	'$'						;OpenWnd函数参数--标题栏文字字符串指针
	
DSEG ENDS

SSEG SEGMENT

	dw 100 dup(?)

SSEG ENDS

CSEG SEGMENT
;*******************************************
;Open a window
;@param	OpenWndLeftTopRow	OpenWnd函数参数--左上角行号
;@param	OpenWndLeftTopCol	OpenWnd函数参数--左上角列号
;@param	OpenWndWidth		OpenWnd函数参数--窗口宽度
;@param	OpenWndHeight		OpenWnd函数参数--窗口高度
;@param	pOpenWndTitle		OpenWnd函数参数--标题栏文字字符串指针
OpenWnd	proc	far
	;*******************************************
	;function initiation	
	push	bp
	mov		bp, sp
	push	ax
	push	bx
	push	cx
	push	dx
	
	add		bp, 2*5
	mov		ax, [bp+2]
	mov		al, OpenWndLeftTopRow
	mov		ax, [bp+4]
	mov		al, OpenWndLeftTopCol
	mov		ax, [bp+6]
	mov		al, OpenWndWidth
	mov		ax, [bp+8]
	mov		al, OpenWndHeight
	mov		ax, [bp+10]
	mov		ax, pOpenWndTitle
	;*******************************************
	
	;*******************************************
	;Draw the frame
	;
	;BIOS窗口上卷清空调用 INT 10H -- AH = 06H
	;	AL=上卷行数(为0时清除窗口内容), BH=卷入行属性
	;	CH:CL=左上角行号:列号, DH:DL=右下角行号:列号
	mov		ah, 06H
	mov		al, 00H						;clear the frame
	mov		bh, 7FH						;设置外框为背景灰色，前景白色
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
	mov		bh, 0F0H						;设置标题栏为背景白色，前景黑色
	mov		ch, OpenWndLeftTopRow
	mov		cl, OpenWndLeftTopCol
	mov		dh, OpenWndLeftTopRow
	add		dh, OpenWndHeight
	mov		dl, OpenWndLeftTopCol
	add		dl, OpenWndWidth
	int		10H
	;*******************************************
	
	;*******************************************
	;function return
	pop		ax
	pop		bx
	pop		cx
	pop		dx
	
	ret
	;*******************************************
OpenWnd	endp
;*******************************************

CSEG ENDS