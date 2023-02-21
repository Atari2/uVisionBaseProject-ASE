				AREA _RO_code, CODE, READONLY
	
;; function prototype
;; my_func 		PROC
;; 				EXPORT my_func
;; 				push {r4-r8,r10-r11,lr}	
;; 				pop {r4-r8,r10-r11,pc}
;; 				ENDP

vett RN 0
num RN 1
super_ptr RN 2

media_e_superiori_alla_media PROC
				EXPORT media_e_superiori_alla_media
				push {r4-r8,r10-r11,lr}	
				
				mov r4, #0
				mov r5, #0
sum_loop
				ldrb r6, [vett, r5]
				add r4, r4, r6
				add r5, r5, #1
				cmp r5, num
				bne sum_loop
				
				; r4 sum of all entries in vett
				; avg in r4
				udiv r7, r4, num
				
				mov r4, #0
				mov r5, #0
super_loop
				ldrb r6, [vett, r5] 
				cmp r6, r7
				addgt r4, r4, #1
				add r5, r5, #1
				cmp r5, num
				bne super_loop
				
				; *super = r4
				strb r4, [super_ptr]
				
				; return avg;
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