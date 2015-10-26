DSEG SEGMENT
	
	titlebarSize		equ	1						;��������С
	frameSize			equ	1						;�߿��С
	titleOffsetVal		equ	2						;��������ƫ����
	screenWidth			equ	80						;Dos���ڿ��
	screenHeight		equ	25						;Dos���ڸ߶�

	OpenWndLeftTopRow	db	'$'						;OpenWnd��������--���Ͻ��к�
	OpenWndLeftTopCol	db	'$'						;OpenWnd��������--���Ͻ��к�
	OpenWndWidth		db	'$'						;OpenWnd��������--���ڿ��
	OpenWndHeight		db	'$'						;OpenWnd��������--���ڸ߶�
	pOpenWndTitle		dw	'$'						;OpenWnd��������--�����������ַ���ָ��
	
DSEG ENDS

SSEG SEGMENT

	dw 100 dup(?)

SSEG ENDS

CSEG SEGMENT
;*******************************************
;Open a window
;@param	OpenWndLeftTopRow	OpenWnd��������--���Ͻ��к�
;@param	OpenWndLeftTopCol	OpenWnd��������--���Ͻ��к�
;@param	OpenWndWidth		OpenWnd��������--���ڿ��
;@param	OpenWndHeight		OpenWnd��������--���ڸ߶�
;@param	pOpenWndTitle		OpenWnd��������--�����������ַ���ָ��
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
	;BIOS�����Ͼ���յ��� INT 10H -- AH = 06H
	;	AL=�Ͼ�����(Ϊ0ʱ�����������), BH=����������
	;	CH:CL=���Ͻ��к�:�к�, DH:DL=���½��к�:�к�
	mov		ah, 06H
	mov		al, 00H						;clear the frame
	mov		bh, 7FH						;�������Ϊ������ɫ��ǰ����ɫ
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
	mov		bh, 0F0H						;���ñ�����Ϊ������ɫ��ǰ����ɫ
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