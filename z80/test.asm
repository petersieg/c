; Programm

		CPU Z80
PRINT		equ	0015h			; NKC: Print into display area
ANZEIGE		equ	0009h			; NKC: Show display area on HEX display

;------------------------------------------------------------------------------
		org 	8100h			; NKC RAM

;------------------------------------------------------------------------------
main:
  		ld 	hl,words0		; start of array address

;------------------------------------------------------------------------------
		
w0:		call	print
w1:		call	anzeige
		jp	w1

;------------------------------------------------------------------------------
		
words0:
; NKC
		db 0ffh,089h,0a3h,08ch,086h,0ffh,0ffh,0ffh ;"HOPE  "


;------------------------------------------------------------------------------

		end
		