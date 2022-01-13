def exponential_brute_force(a,n):
    res=1
    for i in range(n):
        res=res*a
    return res

def exponential_divide_and_conq(a,n):
    if(n==0):
        return 1

    elif (n%2==0): return exponential_divide_and_conq(a,n/2) * exponential_divide_and_conq(a,n/2)
    else : return a * exponential_divide_and_conq(a,n-1)

n=5
a=2

result_brute_force=exponential_brute_force(a,n)
result_exponential_divide_and_conq=exponential_divide_and_conq(a,n)

print("---------------")
print("2^5 BRUTE FORCE: ",result_brute_force)
print("2^5 DIVIDE AND CONQUER: ",result_exponential_divide_and_conq)
print("---------------")

n=3
a=5

result_brute_force=exponential_brute_force(a,n)
result_exponential_divide_and_conq=exponential_divide_and_conq(a,n)

print("---------------")
print("5^3 BRUTE FORCE: ",result_brute_force)
print("5^3 DIVIDE AND CONQUER: ",result_exponential_divide_and_conq)
print("---------------")