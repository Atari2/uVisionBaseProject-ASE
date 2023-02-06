				AREA _RO_code, CODE, READONLY
	
;; function prototype
;; my_func 		PROC
;; 				EXPORT my_func
;; 				push {r4-r8,r10-r11,lr}	
;; 				pop {r4-r8,r10-r11,pc}
;; 				ENDP

VETT   RN 0
VALUE  RN 1
N_V    RN 2
get_and_sort    PROC
				EXPORT get_and_sort
				push {r4-r8,r10-r11,lr}	
				mov r7, VALUE
				mov r4, #0
loop			
				ldrb r5, [VETT, r4]
				cmp r5, #0
				strbeq VALUE, [VETT, r4]
				beq exit
				cmp VALUE, r5
				strbhi VALUE, [VETT, r4]
				movhi VALUE, r5
				add r4, r4, #1
				cmp r4, N_V
				bne loop
exit
				mov r0, r7
				pop {r4-r8,r10-r11,pc}
				ENDP
mSize  RN 3
mSrc   RN 1
mDst   RN 2
MemCpy          PROC
				PUSH    {r5, r4, lr}
				
				MOV 	r4, #0
CopyLoop	
				LDR 	r5, [mSrc, r4, LSL #2]
				STR 	r5, [mDst, r4, LSL #2]
				ADD 	r4, r4, #1
				CMP 	r4, mSize
				BNE 	CopyLoop
				
				POP     {r5, r4, pc}
				ENDP
				
				;; READ-ONLY DATA PORTION
				AREA _RO_data, DATA, READONLY
				
				;; READ-WRITE DATA PORTION
				AREA _RW_data, DATA, READWRITE
	
				END