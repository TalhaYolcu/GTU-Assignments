
def find_worst_best(succes_rates):
    if(len(succes_rates)<2):
        return succes_rates[0],succes_rates[0]

    mid=int(len(succes_rates)/2)
    left_half_worst,left_half_best=find_worst_best(succes_rates[0:mid])
    right_half_worst,right_half_best=find_worst_best(succes_rates[mid:len(succes_rates)])
    return min(left_half_worst,right_half_worst),max(left_half_best,right_half_best)



succes_rates=[20,25,97,10,15,0,99]
worst,best=find_worst_best(succes_rates)
print("---------")
print("Input",succes_rates)
print("Expected worst: ",min(succes_rates)," Expected best: ",max(succes_rates))
print("Calculated worst: ",worst,"Calculated Best: ",best)


succes_rates=[20,25,97,10,15]
worst,best=find_worst_best(succes_rates)
print("---------")
print("Input",succes_rates)
print("Expected worst: ",min(succes_rates)," Expected best: ",max(succes_rates))
print("Calculated worst: ",worst,"Calculated Best: ",best)


succes_rates=[2, 6, 7, 15, 9, 10]
worst,best=find_worst_best(succes_rates)
print("---------")
print("Input",succes_rates)
print("Expected worst: ",min(succes_rates)," Expected best: ",max(succes_rates))
print("Calculated worst: ",worst,"Calculated Best: ",best)

succes_rates=[1, 2, 20, 6, 5, 15, 9, 10]
worst,best=find_worst_best(succes_rates)
print("---------")
print("Input",succes_rates)
print("Expected worst: ",min(succes_rates)," Expected best: ",max(succes_rates))
print("Calculated worst: ",worst,"Calculated Best: ",best)

