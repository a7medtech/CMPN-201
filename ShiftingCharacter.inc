








;---------------------------------------------------------------------------------------------------------------------------------------------

ShiftingCharacter PROC
            ;Do you need to push any thing???
  

            mov ah,1 ;Get key pressed
            int 16h  ;(Wait for a key - AH:scancode,AL:ASCII)        
;------------------------------------------------------------
            mov cx,5  ;Array size (number of elements)
            mov bx,0  ;Word index

;See if any element of the data has reached 0 or 1280 (border limits)

Validate:   cmp charX[bx],0 ;cmp with 0, if it is, then it can increment
            je canI
            
            cmp charX[bx], 300 
            je canD
            
            add bx,2        ;word index
            loop validate   ;check them all
            
            jmp normal      ;if every thing is ok (not 0 or 1280)
            
;The User Clicked Left
canD:       cmp ah,75
            jz MoveLeft
            jmp after
;The User Clicked Right
canI:       cmp ah,77
            jz MoveRight
            
            
            
            
;Check if the user clicked on any key other than left or right, clear it
after:      cmp ah,01
            jne cons
            
            
            
           
            jmp CHECK
;---------------------------------------------------------
;All elements don't contain 0 or 1280

normal:     
        
            mov ah,1 ;Get key pressed
            int 16h  ;(Wait for a key - AH:scancode,AL:ASCII) 
            cmp ah,75
            jz MoveLeft

            cmp ah,77
            jz MoveRight
            
          
           
         
            
            
            
            cmp ah,01
            jne cons
            jmp CHECK
;---------------------------------------------------------
;Left Arrow Click subtracts 1
MoveLeft:   


            mov cx, ShiftingStep
DrawDelayL:                                    ;Delaying drawing left while shifting 10 pixels to give the flashy effect with speed    
            push cx
            mov si, offset charx
            mov cx, 5
            
loopx1:     mov bx, [si]
            mov ax, 1
            ;Subtract 1 from the element (word)
            sub bx, ax
            mov [si], bx
            ;Subtract from all elements
            inc si
            inc si
            loop loopx1   
            
            call RotateLeft                     ;after shifting all Xs to the left, rotate the character to the left a little bit
            call DrawCharacter
            pop cx
            loop DrawDelayL
            mov ah,0
            int 16h 
            
             
            jmp CHECK
;---------------------------------------------------------
;Right Arrow Click adds 1            
MoveRight:  

            mov cx, ShiftingStep
DrawDelayR:                                     ;Delaying drawing right while shifting 10 pixels to give the flashy effect with speed
            push cx
            mov si, offset charx
            mov cx, 5
            
loopx2:     mov bx, [si]
            mov ax, 1
            ;Add 1 from the element (word)
            add bx, ax
            mov [si], bx
            ;Add to all elements
            inc si
            inc si
            loop loopx2
            
            call RotateRight                    ;after shifting all Xs to the right, rotate the character to the right a little bit
            call DrawCharacter
            
            pop cx
            loop DrawDelayR
            
            
;---------------------------------------------------------


cons:       mov ah,0
            int 16h  
CHECK:      call DrawCharacter
            call ReturnIdle 
            ;Clear Screen
            mov ax,0700h      ;Scroll Screen AH=06 (Scroll),AL=0 Entire Page
            mov cx,0          ;from 0,0
            mov dx,184fH      ;To 18h,4fh
            int 10h           ;Clear Screen
            ;Don't forget to pop if you pushed anything    
ret
ShiftingCharacter   endp
;---------------------------------------------------------------------------------------------------------------------------------------------
RotateRight PROC
            mov si, offset chary
            mov di, offset charx 
            
            
            
            ;Adjusting Ys
            
            mov bx, [si]
            mov cx, shiftingFeed
           
            ;Subtract 1  ;first point
            cmp cx, 25
            je stop
            mov ax, 2 
            sub bx, ax 
            add shiftingFeed, 1
            mov [si], bx   
            
            
            mov bx, [si+2]
           
            ;Subtract 1   ;second point
            mov ax, 1 
            sub bx, ax 
            mov [si+2], bx
            
            
            mov bx, [si+6]
            mov ax, 1                                     ;forth point
            ;Add 1 
            add bx, ax 
            mov [si+6], bx  
            
            
            mov bx, [si+8]
            mov ax, 2                                     ;fifth point
            ;Add 1
            add bx, ax 
            mov [si+8], bx
            
            
  
            
            
            
            stop:
            ret

ENDP RotateRight  


RotateLeft PROC
mov si, offset chary
            
            ;Adjusting Ys
            mov cx, shiftingFeed
            cmp cx, 15 
            je stop2
            mov bx, [si+8]
            ;Subtract 1   ;first point
            mov ax, 2 
            sub bx, ax 
            mov [si+8], bx
            mov bx, [si+6]
                        
            ;Subtract 1  ;second point
            mov ax, 1 
            sub bx, ax 
            mov [si+6], bx
            
            
            mov bx, [si+2]
            mov ax, 1                                    ;forth point
            ;add 1 
            add bx, ax 
            mov [si+2], bx  
            
            
            mov bx, [si]
            mov ax, 2 
            sub shiftingFeed, 1                          ;fifth point
            ;add 1
            add bx, ax 
            mov [si], bx
            

         
             
            
            stop2:
            ret
            
ENDP RotateLeft


ReturnIdle Proc
    
     mov cx, 30000    
     delay:    
         mov ah,01
         int 16h
         cmp ah, 75
         je finish
         cmp ah, 77
         je finish
         loop delay
         
         
         
         mov cx, shiftingFeed
         cmp cx, 20
         ja ReturnLeft
         jb ReturnRight
         je finish 
     
     ReturnLeft:
         
         call RotateLeft
     
     
     jmp finish 
     
     ReturnRight:
     
         call RotateRight
           
      
      
      
      finish:
      ret
ENDP ReturnIdle 


DrawCharacter Proc
     
     
     mov si,offset charx
     mov bx,offset chary 
     mov di,0 
     
     Draw:  
       
        mov cx,[si]
        mov dx,[bx]
        mov al,0Ah         ;Pixel color
        mov ah,0ch 
        int 10h
        inc si 
        inc si
        inc bx
        inc bx
        inc di
        cmp di,5
jne Draw
ret 
    
ENDP DrawCharacter
;-------------------------------------------------------------------------------------------------------------------------------------------------------------------




