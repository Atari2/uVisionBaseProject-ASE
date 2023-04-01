				AREA _RO_code, CODE, READONLY
	
;; function prototype
;; my_func 		PROC
;; 				EXPORT my_func
;; 				push {r4-r8,r10-r11,lr}	
;; 				pop {r4-r8,r10-r11,pc}
;; 				ENDP

VAR RN 0
fibonacci 		PROC
				EXPORT fibonacci
				push {r4-r8,r10-r11,lr}	
				
				mov r4, #1 ; valore n
				mov r5, #0 ; valore n-1
				
fib_loop				
				cmp r4, VAR  ; se siamo arrivati alla fine, exit
				ble continue
				;; r4 is bigger than VAR
				sub r6, r4, VAR
				sub r7, VAR, r5
				cmp r6, r7
				movlt r0, r4
				movge r0, r5
				b exit_loop
continue
				; se VAR == r4, è fibonacci, return
				moveq r0, #0xFF ; se VAR == fib, ret 0xff
				popeq {r4-r8,r10-r11,pc}
				
			    add r6, r4, r5 ; calcolo il prossimo
				mov r5, r4     
				mov r4, r6
				
				b fib_loop ; altrimenti prossimo valore
exit_loop
				
				pop {r4-r8,r10-r11,pc}
				ENDP
				
				;; READ-ONLY DATA PORTION
				AREA _RO_data, DATA, READONLY
				
				;; READ-WRITE DATA PORTION
				AREA _RW_data, DATA, READWRITE
	
				END