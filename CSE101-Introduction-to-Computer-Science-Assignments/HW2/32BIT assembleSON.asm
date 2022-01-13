load R0,00
load R1,00
load R2,00
load R3,00
move RB,R0
move RC,R1
move RD,R2
move RE,R3
move R2,RB
move R3,RC
move R4,RD
move R5,RE

load  R0,255
load  R1,01

xor   R2,R2,R0
xor   R3,R3,R0
xor   R4,R4,R0
xor   R5,R5,R0
jmpEQ R5=R0,D0 
addi  R5,R5,R1
move  R0,R2
move  R1,R3
move  R2,R4
move  R3,R5
halt

D0:addi  R5,R5,R1
jmpEQ R4=R0,E0
addi  R4,R4,R1
jmpEQ R0=R0,A0

E0:addi  R4,R4,R1   
jmpEQ R3=R0,F0 
addi  R3,R3,R1
jmpEQ R0=R0,A0

F0:addi  R3,R3,R1   
addi  R2,R2,R1   
jmpEQ R0=R0,A0

A0:move  R0,R2      
move  R1,R3 
move  R2,R4      
move  R3,R5 
halt