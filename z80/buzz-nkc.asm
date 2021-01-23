; Programm
;------------------------------------------------------------------------------
; NKC Version
;------------------------------------------------------------------------------

		CPU Z80
PRINT		equ	0015h			; NKC: Print into display area
ANZEIGE		equ	0009h			; NKC: Show display area on HEX display

;------------------------------------------------------------------------------
;------------------------------------------------------------------------------
;		org 	1000h			; 2nd 2732 Eprom
		org 	8100h			; NKC RAM
		ld	a,R			; read refresh register as seed
		ld	l,a			; in to reg a
		jp	nz,seed2		; if not zero continue
  		ld 	l,3                   	; else set to 3
seed2:		push	hl			; seed on stack
main:
;------------------------------------------------------------------------------
; generate random index value
;------------------------------------------------------------------------------

		pop	hl			; L = alte Zufallszahl

		LD 	A,L
		AND 	08EH			; RKM L
		JP 	PE,S1
		CCF
S1:		RL 	L			; L = neue Zufallszahl
		push	hl			; save on stack


		ld	a,l
		and	a,15			; just 16 values 0-15
		ld	l,a
		ld	h,0

;------------------------------------------------------------------------------
; multiply by 8 since our words array is fixed length on 8 bytes
;------------------------------------------------------------------------------

  		add 	hl,hl                  	; HL = Index * 2
  		ld 	d,h                    	; DE = Index * 2
  		ld 	e,l
  		add 	hl,hl                   ; HL = Index * 4
  		add 	hl,hl                   ; HL = Index * 8
;  		add 	hl,de                   ; HL = Index * 6

;------------------------------------------------------------------------------
; now point to start of words array and add index value times 8 (element length)
;------------------------------------------------------------------------------

  		ld 	de,words0		; start of array address
  		add 	hl,de                   ; HL = ArrayAddress + Index * 6

;------------------------------------------------------------------------------
; just get hl into ix for subroutine dak2
;------------------------------------------------------------------------------

		ld	l,2
w:		ld 	e,250			; delay value char
w0:		call	print
		call	anzeige
		call 	delay1
        	dec 	e
        	jp 	nz,w0	    		; times e
		dec 	l
		jp	nz,w			; times l
		jp	main


;------------------------------------------------------------------------------
; simple delay routine of 256 nop's
;------------------------------------------------------------------------------

delay1: 	ld a,0				; 256 x NOP; A is destroyed
del11:  	nop
        	inc a
        	jp nz,del11
del12:  	ret

;------------------------------------------------------------------------------
; our array of words in LC80 / MPF-1 7-segment byte values
;------------------------------------------------------------------------------
		
words0:
; NKC
		db 0ffh,086h,0abh,086h,0afh,082h,091h,0ffh ;"ENERGY"

		db 0ffh,08ch,0c7h,088h,0abh,0ceh,087h,0ffh ;"PLANET"
;--
		db 000h,000h,000h,086h,083h,0a4h,0ffh,0ffh ;"2BE   "

		db 000h,000h,000h,0a3h,0a1h,0a4h,0ffh,0ffh ;"2DO   "

		db 000h,000h,086h,0cfh,0a1h,0a4h,0ffh,0ffh ;"2DIE  "

		db 000h,000h,0c7h,0c7h,088h,099h,0ffh,0ffh ;"4ALL  "

		db 000h,089h,087h,0afh,088h,086h,0ffh,0ffh ;"EARTH "

		db 000h,000h,086h,08ch,0a3h,089h,0ffh,0ffh ;"HOPE  "

		db 000h,000h,086h,0e3h,0a3h,0c7h,0ffh,0ffh ;"LOVE  "

		db 000h,086h,0c6h,088h,086h,08ch,0ffh,0ffh ;"PEACE "

		db 0a1h,0abh,086h,0cfh,0afh,08eh,0ffh,0ffh ;"FRIEND"

		db 000h,000h,000h,0a1h,0a3h,082h,0ffh,0ffh ;"GOD   "

		db 000h,000h,000h,0abh,0c1h,092h,0ffh,0ffh ;"SUN   "

		db 000h,087h,0cfh,000h,0a3h,0a1h,0ffh,0ffh ;"DO IT "

		db 089h,087h,0c1h,0afh,089h,087h,0ffh,0ffh ;"THRUTH"

		db 000h,000h,0c7h,0c7h,086h,0c6h,0ffh,0ffh ;"CELL  "

;------------------------------------------------------------------------------

		end
		