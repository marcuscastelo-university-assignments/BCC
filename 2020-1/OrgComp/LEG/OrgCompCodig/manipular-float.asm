.data
  numero1: .float -10.5
.text
    
    li     $v0, 6
    syscall


   lwc1 $f12, numero1
                              
                              
    li     $v0, 2
    syscall

   mov.s $f12, $f0   


    s.s  $f12 ,numero1
      
                            
                              
    li     $v0, 2
    syscall
   
    	
  