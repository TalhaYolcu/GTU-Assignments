
INT_MIN_VALUE = -pow(2,32)

def getmaxobtainable(price,length):
    values = []
    for i in range(length+1):
        values.append(0)

    values=getmaxobtainable_rec(price,length,1,INT_MIN_VALUE,values)
    return values[length]

def determine_max(price,start_index,end_index,max_val,values):
    if(start_index==end_index):
        return max_val
    else:
        max_val = max(max_val, price[start_index] + values[end_index - start_index - 1])
        return determine_max(price,start_index+1,end_index,max_val,values)

def getmaxobtainable_rec(price,length,start_index,max_val,values):
    if(start_index==length+1):
        return values
    else:
        max_val=INT_MIN_VALUE
        max_val=determine_max(price,0,start_index,max_val,values)
        values[start_index]=max_val
        return getmaxobtainable_rec(price,length,start_index+1,max_val,values)


prices = [1, 5, 8, 9, 10, 17, 17, 20]
print(prices)
print("Maximum Obtainable Value is ",getmaxobtainable(prices,len(prices)))

prices = [1, 5, 8, 9, 10]
print(prices)
print("Maximum Obtainable Value is ",getmaxobtainable(prices,len(prices)))

