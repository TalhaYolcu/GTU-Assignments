def count_str(s_letter,e_letter,str):
    counter=0
    for i in range (len(str)):
        if (str[i]==s_letter):
            for j in range(i+1,len(str)):
                if (str[j]==e_letter):
                    counter=counter+1

    return counter






s_letter='X'
e_letter='Z'
str=['T','X','Z','X','X','J','Z','W','X']

print("Expected result: 4")
print("Calculated result: ",count_str(s_letter,e_letter,str))

print("")
print("")

s_letter='A'
e_letter='D'
str=['B','A','D','D','C','A','D','A','D']

print("Expected result: 7")
print("Calculated result: ",count_str(s_letter,e_letter,str))

print("")
print("")

s_letter='S'
e_letter='E'
str=['S','E','T','E','Y','E']

print("Expected result: 3")
print("Calculated result: ",count_str(s_letter,e_letter,str))