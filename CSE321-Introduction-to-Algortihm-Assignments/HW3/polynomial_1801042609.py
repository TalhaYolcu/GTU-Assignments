def calculate_p(x,coefficients):
    sum=0
    for i in range(len(coefficients)):
        sum+=pow(x,i)*coefficients[i]
    return  sum


coefficients=[1,2,5] #a0,a1,a2
x=6
result=calculate_p(x,coefficients)
print("TEST1")
print("expected: 6^0 * 1 + 6^1 * 2 + 6^2 * 5 = 193")
print("calculated: ",result)

print("")
print("")

print("TEST2")
coefficients=[5,10,15,0,2] #a0,a1,a2
x=2
result=calculate_p(x,coefficients)
print("expected: 2^0 * 5 + 2^1 * 10 + 2^2 * 15 + 2^3 * 0 + 2^4 * 2 = 117")
print("calculated: ",result)

print("")
print("")

print("TEST3")
coefficients=[3,5,8] #a0,a1,a2
x=4
result=calculate_p(x,coefficients)
print("expected: 2^0 * 5 + 2^1 * 10 + 2^2 * 15 + 2^3 * 0 + 2^4 * 2 = 151")
print("calculated: ",result)

print("")
print("")

print("TEST4")
coefficients = [2,4,6,8]  # a0,a1,a2
x = 3
result = calculate_p(x, coefficients)
print("expected: 2^0 * 5 + 2^1 * 10 + 2^2 * 15 + 2^3 * 0 + 2^4 * 2 = 284")
print("calculated: ", result)
