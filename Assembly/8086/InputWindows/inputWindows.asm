
DSEG    SEGMENT 'DATA'
    screenWidth			equ	80						;Dos窗口宽度
	screenHeight		equ	25						;Dos窗口高度
    
	Wnd1LeftTopRow		equ	3						;窗口1左上角行号
	Wnd1LeftTopCol		equ 3						;窗口1左上角列号
	Wnd1Width			equ 30						;窗口1宽度
	Wnd1Height			equ	5						;窗口1高度
	Wnd1Title			db	'Windows 1', '$'		;窗口1标题栏
	
	Wnd2LeftTopRow		equ	3						;窗口2左上角行号
	Wnd2LeftTopCol		equ 40						;窗口2左上角列号
	Wnd2Width			equ 30						;窗口2宽度
	Wnd2Height			equ	5						;窗口2高度
	Wnd2Title			db	'Windows 2', '$'		;窗口2标题栏
	
	Wnd3LeftTopRow		equ	14						;窗口3左上角行号
	Wnd3LeftTopCol		equ 3						;窗口3左上角列号
	Wnd3Width			equ 67						;窗口3宽度
	Wnd3Height			equ	8						;窗口3高度
	Wnd3Title			db	'Windows 3', '$'		;窗口3标题栏
	
	InputSize			db  screenWidth				;输入容量
	InputActSize		db	'$'						;实际输入字符数量
	InputBuffer			db	screenWidth dup('$')	;输入缓冲区

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

