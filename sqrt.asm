
            
;---------------------------------------------------------------------------------------------------------------------------------------------            
            .model medium
            .stack 64
;---------------------------------------------------------------------------------------------------------------------------------------------
            .data

;---------------------------------------------------------------------------------------------------------------------------------------------
            .code
main    proc far
        mov ax, @data
        mov ds, ax 
      
          ;bl = sqrt(dx)
          mov dx, 100
          call sqrt
      

            hlt
main        endp
;--------------------------------------------------------------------------------------------------------------------------------------------









sqrt proc 
          ;bl = sqrt(dx)
        push cx
        mov ax, 0
        mov bl, 0
        mov cx, 0
        
        
        LOOP1:
        mov al, bl
    	mul bl		; C = B*B       CX = C, bl=B 
	    mov cx, ax
	    
	    cmp cx, dx      ; Compare C to A
	    jg fin			; If C > A Branch to the end

	    ADD bl, 1		; B = B + 1

	    jmp LOOP1		; Go back to the beginning of the loop
        fin:
        sub bl , 1		; B = B-1
        pop cx
        
        ret

endp sqrt 



end         main