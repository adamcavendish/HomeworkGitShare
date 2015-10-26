
DSEG    SEGMENT 'DATA'
    screenWidth			equ	80						;Dos���ڿ��
	screenHeight		equ	25						;Dos���ڸ߶�
    
	Wnd1LeftTopRow		equ	3						;����1���Ͻ��к�
	Wnd1LeftTopCol		equ 3						;����1���Ͻ��к�
	Wnd1Width			equ 30						;����1���
	Wnd1Height			equ	5						;����1�߶�
	Wnd1Title			db	'Windows 1', '$'		;����1������
	
	Wnd2LeftTopRow		equ	3						;����2���Ͻ��к�
	Wnd2LeftTopCol		equ 40						;����2���Ͻ��к�
	Wnd2Width			equ 30						;����2���
	Wnd2Height			equ	5						;����2�߶�
	Wnd2Title			db	'Windows 2', '$'		;����2������
	
	Wnd3LeftTopRow		equ	14						;����3���Ͻ��к�
	Wnd3LeftTopCol		equ 3						;����3���Ͻ��к�
	Wnd3Width			equ 67						;����3���
	Wnd3Height			equ	8						;����3�߶�
	Wnd3Title			db	'Windows 3', '$'		;����3������
	
	InputSize			db  screenWidth				;��������
	InputActSize		db	'$'						;ʵ�������ַ�����
	InputBuffer			db	screenWidth dup('$')	;���뻺����

DSEG    ENDS

SSEG    SEGMENT STACK   'STACK'
        DW      100h    DUP(?)
SSEG    ENDS

CSEG    SEGMENT 'CODE'

;*******************************************

START   PROC    FAR

; Store return address to OS:
    PUSH    DS
    MOV     AX, 0
    PUSH    AX

; set segment registers:
    MOV     AX, DSEG
    MOV     DS, AX
    MOV     ES, AX


;Draw first windows
;	mov		al, Wnd1LeftTopRow					
;	mov		OpenWndLeftTopRow, al
;	mov		al, Wnd1LeftTopCol
;	mov		OpenWndLeftTopCol, al
;	mov		al, Wnd1Width
;	mov		OpenWndWidth, al
;	mov		al, Wnd1Height
;	mov		OpenWndHeight, al
;	mov		bx, offset Wnd1Title
;	mov		pOpenWndTitle, bx
	mov		ax, offset Wnd1Title
	push	ax
	mov	    ax, Wnd1Height
	push	ax
	mov		ax, Wnd1Width
	push	ax
	mov		ax, Wnd1LeftTopCol
	push	ax
	mov		ax, Wnd1LeftTopRow
	push	ax
	call far	 ptr OpenWnd
;;Draw second windows
;	mov		al, Wnd2LeftTopRow					
;	mov		OpenWndLeftTopRow, al
;	mov		al, Wnd2LeftTopCol
;	mov		OpenWndLeftTopCol, al
;	mov		al, Wnd2Width
;	mov		OpenWndWidth, al
;	mov		al, Wnd2Height
;	mov		OpenWndHeight, al
;	mov		bx, offset Wnd2Title
;	mov		pOpenWndTitle, bx
;	call	OpenWnd
;;Draw third windows
;	mov		al, Wnd3LeftTopRow					
;	mov		OpenWndLeftTopRow, al
;	mov		al, Wnd3LeftTopCol
;	mov		OpenWndLeftTopCol, al
;	mov		al, Wnd3Width
;	mov		OpenWndWidth, al
;	mov		al, Wnd3Height
;	mov		OpenWndHeight, al
;	mov		bx, offset Wnd3Title
;	mov		pOpenWndTitle, bx
;	call	OpenWnd
;Input a character, use esc to jump from windows to windows

; return to operating system:
    RET
START   ENDP

;*******************************************

CSEG    ENDS 

        END    START    ; set entry point.

