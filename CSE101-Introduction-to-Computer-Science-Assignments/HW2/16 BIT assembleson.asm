load  R0,00
load  R1,00
move  R2,R0    
move  R3,R1
load R0,255
load R1,01
xor R4,R0,R2
xor R5,R0,R3
jmpEQ R5=R0,NextC
addi R5,R5,R1
move R0,R4
move R1,R5
halt

NextC: addi R5,R5,R1
addi R4,R4,R1
jmpEQ R0=R0,NextC2

NextC2:move R0,R4
move R1,R5
halt
