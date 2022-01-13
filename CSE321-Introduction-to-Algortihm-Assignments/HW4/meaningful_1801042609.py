def decrease(rates):
    min_v=min(rates)
    for i in range(len(rates)):
        if(rates[i]==min_v):
            rates.pop(i)
            return

def find_kth_meaningful(rates,k):
    for i in range(k-1):
        decrease(rates)
    return min(rates)

k=5
success_rates=[20,25,97,10,15,0,99]
print("---------")
print("Input array: ",success_rates)
print("Expected 5th smallest: 25")
print("Calculated 5th smallest: ",find_kth_meaningful(success_rates,k))

k=3
success_rates=[20,25,97,10,15]
print("---------")
print("Input array: ",success_rates)
print("Expected 3rd smallest: 20")
print("Calculated 3rd smallest: ",find_kth_meaningful(success_rates,k))

k=2
success_rates=[7,10,4,3,20,15]
print("---------")
print("Input array: ",success_rates)
print("Expected 2nd smallest: 4",)
print("Calculated 3rd smallest: ",find_kth_meaningful(success_rates,k))

