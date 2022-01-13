.data
	#read_file datasý
	file_name: .asciiz "input.txt"			#input file name
	buffer: .space 400				#buffer that read data will be written to it
	buffer1: .word 1,2,3,4,5,6,7,8,10		#output array that stores integer inside, it could be taken as input of the algorithm
	tempbuffer: .space 400				#in here, I store characters that until I reach a space for example 3_10
							#in first iteration I have 3 in the tempbuffer, then in the second iteration I have 10 in the tempbuffer
	newLine: .asciiz "\n"				#new line for alignment issues
	#arr2: .word 50,3,10,7,40,80			#test array
	space: .byte ' '				#space character for alignment issues
	exclamation: .byte '!'				#exclamation that helps us to understand we are in the end of array
	my_ascii: .word 48				#ascii number 48 that helps us the handle char-int issues
	space2: .asciiz " "				#string of space


	#hw1_1 algo kýsmý datasý
	#arr,arr_size and arr_size_by_4 is unnecessary data, when I try to delete them, I encounter with an error
	arr: .word 50,3,10,7,40,80			#test array for algorithn
	arr_size: .word 6				#size of array
	arr_size_by_4: .word 24				#array size*4
	out: .space 400					#temp array, it holds sequences in each iteration
	tempArr: .space 400				#output array at the end of algorithm, it could be taken as an input to write file
	k: .word 0					#counter for loop2
	i: .word 0					#counter for loop1
	z: .word 0					#counter for loop3
	counter: .word 0				#counter for temparray length
	max_of_array: .word 0				#number that first less element that current element
	max_v: .word 0					#maximum element of sequence until now
	out_size: .word 0				#output array size
	str1: .asciiz "\nArray elements are:"		#string to helps us to undestand array elements
	str2: .asciiz " "				#space
	counter_old: .word 0				#size of the previous sequence, if it is less than new sequence , it will be updated
	
	#write_file__datasý			
	#array: .word 50,3,10,7,40,80
	array: .word 3,10,7,9,4,11			#test_array I couldnt remove it gives error
	fout: .asciiz "output.txt"			#output file name
	buffer2: .space 44				#helps to align size and array
	buffer4: .space 44				#space for buffers
	buffer3: .space 400				#space for buffers
	size_text: .asciiz " size: "			#size text to write file
	write_array_size: .byte 48			#ascii code
	#array_size: .word 24
	#space: .asciiz " "
	input_text: .asciiz "\nInput array: "
	output_text: .asciiz "\nOutput array: "



.text
.globl main

main:

	#open file for reading
	li $v0,13		#system call for open file
	la $a0,file_name	#input file name
	li $a1,0		#flag for reading
	li $a2,0		#mode is ignored
	syscall			#open a file
	move $s0,$v0		#save the file descriptor

	# reading from file just opened
	li   $v0, 14       # system call for reading from file
	move $a0, $s0      # file descriptor 
	la   $a1, buffer   # address of buffer from which to read
		
	li   $a2,  240  	   # hardcoded buffer length
	syscall            # read from file	
	
	#print the buffer	
	li $v0,4
	la $a0,buffer
	syscall
	
	jal close_the_read_file
	
	# Open (for writing) a file that does not exist
	li $v0,13	#system call for open file
	la $a0,fout	#output file name
	li $a1,1	#open for writing flags are 0: read 1:write
	li $a2,0	#mode is ignored
	syscall		#open a file file descriptor returned in $v0
	
	move $s6,$v0
	
	
	#write to file just opened
	li $v0,15	#system call for write to file
	move $a0,$s6	#file descriptor
	la $a1,newLine	#adress of buffer from which to write
	li $a2,1	#hardcoded buffer length
	syscall		#write to file
	
	#close the file
	li $v0,16	#system call for close file
	move $a0,$s6	#file descriptor to close
	syscall		#close file
	
	
		
	
	
	j start_the_process
	
	
start_the_process:
	
	#excalamation gorene kadar devam edecez
	#her exclamationda döngü olacak
	#6.exclamationdan sonra da bu döngüden çýkacaz
	
	addi $t0,$zero,0	#exclamation counter
	addi $t1,$zero,0	#buffer cursor	holds the end index of the array in the buffer

	
process_loop1:
	beq $t0,6,exit_process	#if(t0==6 then exit from the process, all arrays are evaluated write file should be closed)
	add $t4,$zero,$t1	#t4 holds the start index of the array in the buffer
	#find_the_length_of_array
	#addi $t1,$zero,0		#counter
	find_length_of_buffer_loop:
		lb $t2,buffer($t1)		#t2=buffer[counter]
		lb $t3,exclamation($zero)	#t3='!'
		beq $t2,$t3,find_length_of_buffer_exit_loop		#if t2==t3 then exit loop
		addi $t1,$t1,1			#else increment counter
		j find_length_of_buffer_loop
		
	find_length_of_buffer_exit_loop:
	
		 
	#saving numbers into buffer	 t0,t1,t3 cant be used
	
	addi $t2,$t4,0			#index to iterate through buffer
	addi $t3,$zero,0		#counter_number, number of digit in the tempArray
	addi $t5,$zero,0		#length of the integer array multiply of 4
	addi $a2,$t1,1			#array_length+1 is in a2,it will be updated, 
	
	save_number_into_buffer1_loop1:
		beq $t2,$a2,save_number_into_buffer1_exit_loop1		#if t2=array_length then exit loop
		lb $t6,buffer($t2)		#t6=buffer[i]
		lb $t7,space($zero)		#t7=space
		lb $t8,exclamation($zero)	#t8=!
		beq $t6,$t7,this_is_space	#if t6=t7 then this is space
		beq $t6,$t8,this_is_space	#if t6=t8 then this is exlclamation
		sb $t6,tempbuffer($t3)			#if it is not space this means that it is a digit,store it into memory
		addi $t3,$t3,1			#number of digit found
		addi $t2,$t2,1			#increment counter
		j save_number_into_buffer1_loop1
		
		this_is_space:
			
			addi $t9,$zero,0	#t9=0
			addi $s0,$zero,0	#s0=0
			save_number_into_buffer1_loop2:
				beq $t9,$t3,save_number_into_buffer1_exit_loop2		#if t9==t3 then exit loop2, t3 counter for handle space
				addi $s2,$zero,10		#s2=10
				mult $s0,$s2			#s0=s2*10 because we need to have integer value of the character
				mflo $s0			
				lb $s1,tempbuffer($t9)		#s1=tempbuffer[t9]
				addi $s1,$s1,-48		#s1=s1-48 it is integer we need to have its ascii value
				add $s0,$s0,$s1			#s0=s0+s1 add numberr to have result
				add $t9,$t9,1			#increment counter
				j save_number_into_buffer1_loop2
				
			save_number_into_buffer1_exit_loop2:	#number is saved in s0 , store it into memory
				sw $s0,buffer1($t5)
				
			
				
				addi $t5,$t5,4			#increment counter
				addi $t3,$zero,0		#reset number of digit in the buffer
				
				
		addi $t2,$t2,1					#1 number is stored into memory
		j save_number_into_buffer1_loop1	
			
	save_number_into_buffer1_exit_loop1:
		addi $a2,$t5,0					#all numbers are saved into memory
		

#end of saving numbers into buffer1	

print_the_buffer1_array:			#prints the input array to the terminal

	li $v0,4
	la $a0,newLine
	syscall

	li $v0,4
	la $a0,newLine
	syscall

	li $v0,4
	la $a0,input_text
	syscall

	addi $t3,$zero,0		#t0=0

	print_loop_buffer1:
		slt $s0,$t3,$t5		#if t0<t1 then s0=1 => if z<counter_old s0=1
		beq $s0,1,cont_buffer1		#if s0=1 then continue loop
		j exit_printing_buffer1			#else exit
		cont_buffer1:
			li $v0,1	
			lw $t6,buffer1($t3)	
			add $a0,$zero,$t6	#print integer
			syscall			
		
			li $v0,4		#print space
			la $a0,space2
			syscall
		
			addi $t3,$t3,4
			j print_loop_buffer1			
	
		
	exit_printing_buffer1:	
		
	
	
	
	#algoritma kýsmý
	#input arrayi:buffer1
	#size ý t5'te tutuluyor
	#dokunmamam gereken counterlar:t0,t1,t4,t2,t5
	#serbest counterlar:t3,t4,t5,t6,t7,t8,t9,s0,s1,s2,s3,s3,s5,s6,s7,a2
	
	addi $t3,$t5,0		#t3=arr_size			#t5 arrayin size i
	lw $t4,i($zero)			#t4=i
	
	outer_loop:

		slt $s0,$t4,$t3			#i<arr_size
		beq $s0,$zero,print_the_output_array	#if s0=0 go and print output array	
		lw $t5,buffer1($t4)				# t5=arr[i]
		sw $t5,max_v($zero)			#max_v=t5
		j clear_output_array			#clear the output array so that we will need the reset values
		after_clear_output_array:
		sw $zero,counter($zero)			#counter=0
		bne $zero,$t4,look_back			#if(i!=0) then go into if like in the c code
		j don_t_look_back	
		
		look_back:
			sw $zero,max_of_array($zero)	#max_of_array=0
			sw $zero,k($zero)		#k=0
			lw $s0,k($zero)			#s0=k
		
			inner_loop1:
				slt $s1,$s0,$t4		#if s0<t1 so k<i then s1=1
				beq $s1,$zero,exit_from_inner_loop	#if s1=0 then exit from inner loop
				lw $s1,buffer1($s0)			#s1=arr[k]
				lw $s2,max_v($zero)			#s2=max_v
				lw $s3,max_of_array($zero)		#s3=max_of_array
				slt $s4,$s1,$s2				#if s1<s2 then set s4=1 so if arr[k]<max_v then s4=1
				slt $s5,$s3,$s1				#if s3<s1 then set s5=1 so if max_of_array<arr[j] then s5=1
				and $s6,$s4,$s5				#s6=s5 and s4
				beq $s6,1,go_into_if			#if result of and is 1 then branch to if
				j don_t_go_into_if
				go_into_if:
					lw $s4,counter($zero)		#s4=counter
					sw $s1,out($s4)			#out[s4]=s1 => out[counter]=arr[j]
					addi $s4,$s4,4			#counter++
					sw $s4,counter($zero)		#after incremental, store it into memory
					add $s3,$zero,$s1		#max_of_array=arr[k] => s3=0+s1
				
				don_t_go_into_if:
					sw $s2,max_v($zero)		#give s2 back
					sw $s3,max_of_array($zero)	#give s3 back
					addi $s4,$zero,0		#give s4 back
					addi $s3,$zero,0		#set s3 0
					addi $s5,$zero,0		#set s5 0		
					addi $s6,$zero,0		#set s6 0
					
				addi $s0,$s0,4				#k++
				j inner_loop1				#execute inner loop1 again
				
				#danger
					
				
				
			exit_from_inner_loop:
				#out[counter]=arr[i];
        			#counter++		
				
				
			
don_t_look_back:	
			lw $s0,counter($zero) #s0=counter
			sw $t5,out($s0)		#out[s0]=t5 => out[counter]=arr[i];
			addi $s0,$s0,4		#counter++
			sw $s0,counter($zero)	#save counter to memory				
			addi $s0,$t4,4			#set s0=i+1 => j=i+1
			second_inner_loop:
				slt $s1,$s0,$t3		#if s0<t3 then s1=1 => j<arr_size 
				bne $s1,1,exit_from_second_inner_loop	#if s1=1 then go into second if
				lw $s2,max_v($zero)	#s2=max_v
				lw $s3,buffer1($s0)		#s3=arr[j]
				slt $s1,$s2,$s3		# if s2<s3 then s1=1 => if max_v<arr[j] then s1=!
				beq $s1,1,go_into_second_if	#if s1=1 then go into second if
				j don_t_go_into_second_if	
				
				go_into_second_if:
					lw $s4,counter($zero) #s4=counter
					sw $s3,out($s4)		#out[s4]=s3 => out[counter]=arr[j]
					addi $s2,$s3,0		#s2=s3 => s2=arr[j]
					sw $s2,max_v($zero)	#max_v=s2
					addi $s4,$s4,4		#counter++
					sw $s4,counter($zero)	#save counter to memory
					
				don_t_go_into_second_if:
					sw $s2,max_v($zero)	#give s2 back
					sw $s3,buffer1($s0)		#give s3 back
					
				addi $s0,$s0,4			#j++			
				j second_inner_loop
				
			exit_from_second_inner_loop:
				lw $s0,counter_old($zero)	#s0=counter_old
				lw $s1,counter($zero)		#s1=counter
				slt $s2,$s0,$s1			#if s0<s1 then s2=1 => if counter_old<counter then s2=1
				beq $s2,1,go_into_third_if	#if s2=1 then go into third_if
				j don_t_go_into_third_if	#else dont go into third_if
				
				go_into_third_if:
					addi $s3,$zero,0	#s3=0   => z=0
					third_inner_loop:
						slt $s4,$s3,$t3		#if z<arr_size then s4=1
						beq $s4,1,cont_til	#if s4=1 then cont. third inner loop
						j exit_til		#else exit from third inner loop
							
						cont_til:
							sw $zero,tempArr($s3)	#tempArr[z]=0
							addi $s3,$s3,4		#z++
							j third_inner_loop	#execute loop
							
				exit_til:
					addi $s3,$zero,0			#s3=0 => z=0
					lw $s4,counter($zero)			#s4=counter
					fourth_inner_loop:
						slt $s5,$s3,$s4			#if z<counter then set s5=1
						beq $s5,1,cont_fil		#if s5=1 then continue fourth inner loop
						j exit_fil			#else exit fourth inner loop
						
						cont_fil:
						lw $s6,out($s3)			#s6=out[z]
						sw $s6,tempArr($s3)		#tempArr[z]=s6
						addi $s3,$s3,4			#z++
						j fourth_inner_loop		#execute loop
							
				exit_fil:
				lw $s1,counter($zero)				#reset the used memory
				sw $s1,counter_old($zero)
				sw $s1,counter($zero)
					
						
							
				don_t_go_into_third_if:
				
				
				addi $t4,$t4,4			#we evaluated 1 index, increment it

				

				j outer_loop		
		
		
		
	
	end_of_algo:
	
	sw $zero,counter($zero)				#reset the used memory
	sw $zero,i($zero)
	sw $zero,k($zero)
	sw $zero,z($zero)
	sw $zero,max_of_array($zero)
	sw $zero,max_v($zero)	

			
	#write_to_file
	

	#open file
	li $v0,13	#system call for open file
	la $a0,fout	#oputput file
	li $a1,9	#write to file append mode
	li $a2,0	#ignore mode
	syscall		
	
	move $s6,$v0	#file descriptor is in the s6
	move $a3,$s6	#file descriptor is in the v0
	
	#parse the integer array to write to the file
	#output file:output.txt
	#output array:	buffer3
	
	addi $s2,$zero,0	#i=0
	addi $t3,$zero,10	#t3=10
	lw $s0,counter_old($zero)#s0=array_size
	addi $t7,$zero,0	#every time make t7 zero
	loop_parse_buffer3:
		beq $s2,$s0,exit_loop_parse_buffer3	#if (i==array_Size then exit loop
			
		lw $s5,tempArr($s2)	#s5=array[i]
		addi $t8,$zero,0	#every time make t8 zero, t8 is digit counter
		parse:
		addi $t3,$zero,10	#t3=10
			div $s5,$t3		#s5/10
			mfhi $t6		#t6=s5%10
			mflo $t5		#t5=s5/10
			
			addi $t6,$t6,48		#get ascii code of digit
			la $t9,buffer3($t7)	#t9 is adress of element
			sb $t6,($t9)		#store character in that adress
			
			addi $t7,$t7,1		#t7 is incremented because we evaluated 1 digit
						
			beq $t5,0,parsed_buffer3	#if t6/10==0 then it is parsed
			
			addi $t8,$t8,1			#it is not parsed yet continue
			#put char into memory then continue parsing

			
			move $s5,$t5			#s5 is the fraction part,move it so that we will continue parsing
			j parse
		
		
	
	parsed_buffer3:
		addi $t8,$t8,1				#because of indexing we need to increment nubmer of digits
		addi $t6,$zero,1
		beq $t8,$t6,don_t_reverse_buffer3	#t6 is 1, t8 is number of digits compare, if we have more than 1 digits we need to reverse the number
		slt $s1,$t8,$t6
		beq $s1,1,don_t_reverse_buffer3
		
		addi $t5,$zero,0			#reset t5
		
		
	reverse_loop_buffer3:
	#aralarýndaki fark 2 uzunlukta 3 oluyor, aralarýndaki fark 1 olmalý #s4 ve #t9
			addi $t6,$zero,2		#t6 is 2 we will need 2 because we will divide length by 2
			
			div $t8,$t6			#t8/t6
			mflo $t6			#t6=length of array/2
			slt $s1,$t5,$t6			#if t5<t6 then s1=1, continue reversing
			beq $s1,0,exit_reverse_loop_buffer3
			
			sub $s3,$t7,$t8		#s3=evalueated digit-length		
			addi $s3,$s3,0	
			la $s4,buffer3($s3)	#s4=buffer3[s3]
			lb $s7,($s4)		#s7=buffer3[s3]	 => s7=buffer[start_index]		
			
			addi $t6,$zero,0	#length-start_index-1
			add $s6,$zero,$t8	#s6=length
			slt $s1,$s6,$s3		#if length<s3 
			beq $s1,0,continue_reverse_buffer3	
			add $s6,$s6,$s3
continue_reverse_buffer3:	sub $t6,$s6,$s3
			sub $t6,$t6,1
			
			addi $t6,$zero,0		#reset t6
			sub $t6,$t7,$s3			
			sub $t6,$t6,1
			add $t6,$t6,$s3
			
			la $t9,buffer3($t6)	
			lb $t3,($t9)		#s2=buffer3[t6] => s2=buffer[length-i-1]

			addi $a0,$t3,0		#t8=s2 => char x=buffer3[length-i-1]
			addi $t3,$s7,0		#s2=s7 => buffer3[length-i-1]=buffer3[i]
			addi $s7,$a0,0		#s7=t8 => buffer3[i]=x
		
			sb $s7,($s4)
			sb $t3,($t9)
			
			addi $t5,$t5,1
			j reverse_loop_buffer3
		


	exit_reverse_loop_buffer3:
			
	
	don_t_reverse_buffer3:
		#put space into memory
		addi $t6,$zero,0
		lb $t6,space
		la $t9,buffer3($t7)
		sb $t6,($t9)	
		addi $t7,$t7,1
		
		addi $s2,$s2,4
		j loop_parse_buffer3
	
	
	exit_loop_parse_buffer3:
		
	
	li $v0, 15 # system call for write to file
	move $a0, $a3 # file descriptor
	la $a1,buffer3
	li $a2,50
	syscall	
	
	#size_text .asciiz " size: "
	#write_array_size .byte 0
	
	li $v0,15
	move $a0,$a3
	la $a1,size_text
	li $a2,7
	syscall
	
	li $v0,15
	move $a0,$a3
	addi $s7,$zero,0
	lw $s7,counter_old($zero)
	div $s7,$s7,4
	beq $s7,10,size_is_ten
	j size_is_not_ten
	
	size_is_ten:
	addi $s7,$zero,49
	sb $s7,write_array_size($zero)
	la $a1,write_array_size($zero)
	li $a2,1
	syscall
	
	li $v0,15
	move $a0,$a3,
	addi $s7,$zero,48
	sb $s7,write_array_size($zero)
	la $a1,write_array_size($zero)
	li $a2,1
	syscall
	
	j writing_done
	
	
		
	size_is_not_ten:
	addi $s7,$s7,48
	sb $s7,write_array_size($zero)
	la $a1,write_array_size
	li $a2,2
	syscall
	
	
writing_done:	
	li $v0,15
	move $a0,$a3
	la $a1,newLine
	li $a2,1
	syscall
	

	
	
	#close the file
	li $v0,16	#system call for close file
	move $a0,$a3	#file descriptor to close
	syscall	
	
	sw $zero,counter($zero)
	sw $zero,counter_old($zero)
	sw $zero,i($zero)
	sw $zero,k($zero)
	sw $zero,z($zero)
	sw $zero,max_of_array($zero)
	sw $zero,max_v($zero)	
	
	addi $s2,$zero,0
	addi $s5,$zero,0
	addi $t3,$zero,0
	addi $t5,$zero,0
	addi $t8,$zero,0
	addi $t9,$zero,0
	addi $s0,$zero,0
	addi $s1,$zero,0
	addi $s3,$zero,0
	addi $s4,$zero,0
	addi $s6,$zero,0
	addi $s7,$zero,0	
	
	addi $t6,$zero,0
	clear_buffer3_loop:beq $t6,100,exit_clear_buffer
	la $t7,buffer3($t6)
	sb $zero,($t7)
	addi $t6,$t6,1
	j clear_buffer3_loop
	
	addi $t6,$zero,0
	addi $t7,$zero,0
	
exit_clear_buffer:

	
	
		
	
	
	
	
	
	addi $t0,$t0,1		#after 1 array is evaluated, exclamation counter is incremented, \n should be read and then start_the_process again
	#read newLine here
	addi $t1,$t1,1
	
	addi $t1,$t1,2
	addi $t4,$t4,3	
	j process_loop1		#go to the other array
	
	
print_the_output_array:

	li $v0,4
	la $a0,output_text
	syscall

	addi $t4,$zero,0		#t0=0
	lw $s0,counter_old($zero)	#t1=counter_old

	print_loop_tempArr:
		slt $s1,$t4,$s0	#if t0<t1 then s0=1 => if z<counter_old s0=1
		beq $s1,1,cont_tempArr		#if s0=1 then continue loop
		j end_of_algo		#else exit
		cont_tempArr:
			li $v0,1	
			lw $t6,tempArr($t4)	
			add $a0,$zero,$t6	#print integer
			syscall			
		
			li $v0,4		#print space
			la $a0,str2
			syscall
		
			addi $t4,$t4,4
			j print_loop_tempArr
	

clear_output_array:
	addi $s1,$zero,0		#s1=0
continue_clear:
	slt $s2,$s1,$t3			#if s1<t0 then set s2=1
	beq $s2,$zero,after_clear_output_array	#if s2=0 then return_back
	sw $zero,out($s1)			#out[$s1]=$s3
	addi $s1,$s1,4			#s1=s1+4
	j continue_clear		#execute loop again
	

exit_process:
	j exit
	

close_the_read_file:
# Close the file  and exit

	li   $v0, 16       # system call for close file
	move $a0, $s6      # file descriptor to close
	syscall            # close file
	
	jr $ra
exit:
	#close file

	
	li $v0,10
	syscall
	

