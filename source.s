				AREA _RO_code, CODE, READONLY
	
;; function prototype
;; my_func 		PROC
;; 				EXPORT my_func
;; 				push {r4-r8,r10-r11,lr}	
;; 				pop {r4-r8,r10-r11,pc}
;; 				ENDP

begin_val RN 0
tot_time  RN 1
vett_times RN 2
n_var      RN 3
duty_cycle		PROC
				EXPORT duty_cycle
				push {r4-r8,r10-r11,lr}	
				mov r5, #0 		;; uint32_t tempo_totale_up = 0;
				eor r4, r4, r4
dc_loop							
				;; uint32_t curr = tempi_variazioni[i];
				ldr r7, [vett_times, r4, LSL #2]
				;; uint32_t next_tempo = (i+1 == numero_variazioni) ? tempo_totale : tempi_variazioni[i + 1];
				add r8, r4, #1 ; i+1
				cmp r8, n_var ; i+1 == numero_variazioni
				moveq r6, tot_time ;  (i+1 == numero_variazioni) ? tempo_totale : tempi_variazioni[i + 1]
				ldrne r6, [vett_times, r8, LSL #2] ;  (i+1 == numero_variazioni) ? tempo_totale : tempi_variazioni[i + 1]
				sub r6, r6, r7 ; next_tempo - curr;
				add r5, r5, r6 ; tempo_totale_up += next_tempo - curr;
				add r4, r4, #2
				cmp r4, n_var
				blt dc_loop
				
				cmp begin_val, #1
				subeq r5, tot_time, r5
				
				mov r0, #100
				mul r5, r5, r0 
				udiv r5, r5, tot_time 
				
				mov r0, r5
				
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