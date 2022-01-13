def most_profitable(stations):
    left_index=0
    right_index=0
    profit_sum=-999
    current_max=0

    for i in range(len(stations)):
        current_max=stations[i]
        for j in range(i+1,len(stations)):
            current_max+=stations[j]
            if(profit_sum<current_max):
                profit_sum=current_max
                left_index=i
                right_index=j

    return stations[left_index:right_index+1],left_index,right_index


def max_profit(cluster1):
    if(len(cluster1)==1):
        return cluster1[0]
    cur_index=int(len(cluster1)/2)
    left=max_profit(cluster1[0:cur_index])
    right=max_profit(cluster1[cur_index:len(cluster1)])
    return left+right

letters=['A','B','C','D''E','F']
profits=[3,-5,2,11,-8,9,-5]

print("MOST PROFIT:")
print("Expected most profit: CDEF and 2,11,-8,9")
cluster,left,right=most_profitable(profits)


mstring=""
for i in range(left,right):
    mstring+=letters[i]

istring=""
for i in range(len(cluster)):
    istring+=str(cluster[i])
    istring+=","

print("Calculated most profit: "+mstring+" and "+istring)

print("--------")
print("MAX PROFIT:")
print("Expected max profit: 14")
print("Calculated max profit: ",max_profit(cluster))