; Programm
;------------------------------------------------------------------------------
; Start auf Adr. 1000 (Zusatz-ROM 3)
;------------------------------------------------------------------------------

		CPU Z80
DAK2		equ	0883h			; Anzeige 1x für 2x1 ROMs
;DAK2		equ	0483h			; Anzeige 1x für 1x2 ROM 2716
;DAK2		equ	0624h			; Anzeige 1x für MPF-1

;------------------------------------------------------------------------------
;------------------------------------------------------------------------------
;		org 	1000h			; LC80 U3 2716
		org 	2000h			; MPF-1 U7 2716
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
; multiply by 6 since our words array is fixed length on 6 bytes
;------------------------------------------------------------------------------

  		add 	hl,hl                  	; HL = Index * 2
  		ld 	d,h                    	; DE = Index * 2
  		ld 	e,l
  		add 	hl,hl                   ; HL = Index * 4
  		add 	hl,de                   ; HL = Index * 6

;------------------------------------------------------------------------------
; now point to start of words array and add index value times 6 (element length)
;------------------------------------------------------------------------------

  		ld 	de,words0		; start of array address
  		add 	hl,de                   ; HL = ArrayAddress + Index * 6

;------------------------------------------------------------------------------
; just get hl into ix for subroutine dak2
;------------------------------------------------------------------------------

		push 	hl			; hl on stack
  		pop 	ix			; get hl as ix from stack
		
		ld	l,2
w:		ld 	e,250			; delay value char
w0:		call	dak2
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
; LC-80
		db 0abh,0e6h,048h,0ceh,068h,0ceh ;"ENERGY"
		db 0cah,0ceh,068h,06fh,0c2h,04fh ;"PLANET"
		db 000h,000h,000h,0ceh,0eah,0cdh ;"2BE   "
		db 000h,000h,000h,0e8h,0e9h,0cdh ;"2DO   "
		db 000h,000h,0ceh,020h,0e9h,0cdh ;"2DIE  "
		db 000h,000h,0c2h,0c2h,06fh,02bh ;"4ALL  "
		db 000h,06bh,0cah,048h,06fh,0ceh ;"EARTH "
		db 000h,000h,0ceh,04fh,0e8h,06bh ;"HOPE  "
		db 000h,000h,0ceh,0e0h,0e8h,0c2h ;"LOVE  "
		db 000h,0ceh,0c6h,06fh,0ceh,04fh ;"PEACE "
		db 0e9h,068h,0ceh,020h,048h,04eh ;"FRIEND"
		db 000h,000h,000h,0e9h,0e8h,0e6h ;"GOD   "
		db 000h,000h,000h,068h,0e3h,0aeh ;"SUN   "
		db 000h,0cah,020h,000h,0e8h,0e9h ;"DO IT "
		db 06bh,0cah,0e0h,048h,06bh,0cah ;"THRUTH"
		db 000h,000h,0c2h,0c2h,0ceh,0c6h ;"CELL  "

; MPF-1
;		db 0b6h,0adh,003h,08fh,023h,09fh ;"ENERGY"
;		db 087h,08fh,023h,03fh,085h,01fh ;"PLANET"
;		db 000h,000h,000h,08fh,0a7h,09bh ;"2BE   "
;		db 000h,000h,000h,0a3h,0b3h,09bh ;"2DO   "
;		db 000h,000h,08fh,089h,0b3h,09bh ;"2DIE  "
;		db 000h,000h,085h,085h,03fh,036h ;"4ALL  "
;		db 000h,037h,087h,003h,03fh,08fh ;"EARTH "
;		db 000h,000h,08fh,01fh,0a3h,037h ;"HOPE  "
;		db 000h,000h,08fh,0b7h,0a3h,085h ;"LOVE  "
;		db 000h,08fh,08dh,03fh,08fh,01fh ;"PEACE "
;		db 0b3h,023h,08fh,089h,003h,00fh ;"FRIEND"
;		db 000h,000h,000h,0b3h,0a3h,0adh ;"GOD   "
;		db 000h,000h,000h,023h,0b5h,0aeh ;"SUN   "
;		db 000h,087h,089h,000h,0a3h,0b3h ;"DO IT "
;		db 037h,087h,0b5h,003h,037h,087h ;"THRUTH"
;		db 000h,000h,085h,085h,08fh,08dh ;"CELL  "

;------------------------------------------------------------------------------

		end
		