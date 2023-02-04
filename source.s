				AREA _RO_code, CODE, READONLY
	
;; function prototype
;; my_func 		PROC
;; 				EXPORT my_func
;; 				push {r4-r8,r10-r11,lr}	
;; 				pop {r4-r8,r10-r11,pc}
;; 				ENDP


count_bits_to_1 PROC
				EXPORT count_bits_to_1
				push {r4, lr}
				bl  PopCount
				pop {r4, pc}
				ENDP

PopCount	 	PROC
				EXPORT PopCount
				push {r4, lr}
				mov r4,r0
				eor r0, r0, r0
_PopCount_loop	tst r4, #1
				addne r0, r0, #1
				lsrs r4, r4, #1
				bne _PopCount_loop
				pop {r4, pc}
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