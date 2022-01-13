def sum_rest(stations2,start_index2,sums2,sums_counter2):
    if(start_index2==len(stations2)):
        return sums2,sums_counter2
    else:
        sums2.append(sums2[sums_counter2-1]+stations2[start_index2])
        sums_counter2+=1
        return sum_rest(stations2,start_index2+1,sums2,sums_counter2)

def find_cluster_rec(stations,start_index,sums,sums_counter):
    if (start_index==len(stations)):
        return sums
    else:
        sums.append(stations[start_index])
        sums_counter+=1
        sums,sums_counter=sum_rest(stations,start_index+1,sums,sums_counter)
        return find_cluster_rec(stations,start_index+1,sums,sums_counter)



def find_cluster2(stations):
    sums=[]
    sums_counter=0
    sums=find_cluster_rec(stations,0,sums,sums_counter)
    return max(sums)



stations=[3,-5, 2, 11, -8, 9, -5]
my_max=find_cluster2(stations)
print(stations)
print("MAX OF PROFIT: ",my_max)
print("------------")

stations=[3,5, 2, 11, -8, 9, -5]
my_max=find_cluster2(stations)
print(stations)
print("MAX OF PROFIT: ",my_max)
print("------------")










