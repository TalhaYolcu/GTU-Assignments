def partition(gifts, low, high,boxes):
    i = (low - 1)  # index of smaller element
    pivot = boxes[high]  # pivot

    for j in range(low, high):

        # If current element is smaller than or
        # equal to pivot
        if gifts[j] <= pivot:
            # increment index of smaller element
            i = i + 1
            gifts[i], gifts[j] = gifts[j], gifts[i]
            boxes[i],boxes[j] = boxes[j],boxes[i]


    gifts[i + 1], gifts[high] = gifts[high], gifts[i + 1]
    boxes[i + 1], boxes[high] = boxes[high], boxes[i + 1]
    return (i + 1)

def quickSort(gifts, low, high,boxes):
    if len(gifts) == 1:
        return gifts
    if low < high:
        # pi is partitioning index, gifts[p] is now
        # at right place
        pi = partition(gifts, low, high,boxes)

        # Separately sort elements before
        # partition and after partition
        quickSort(gifts, low, pi - 1,boxes)
        quickSort(gifts, pi + 1, high,boxes)

#Test code
boxes = [180,170,110,190,150,140,130,160,120]
#there are 9 boxes and these integers indicates the size of the box

gifts = [120,160,130,140,150,190,110,170,180]
#there are 9 boxes and these integers indicates the size of the gift

print("We have  " + str(len(gifts)) + " gifts")
print("We have " + str(len(boxes)) + " boxes")
cc = 0
dd=0

for i in range((len (gifts))):
    print(gifts[i],"=>",boxes[i])

print("---------")

for i in range((len(gifts))):
    if(gifts[i]!=boxes[i]):
        for j in range((len(boxes))):
            if(boxes[i]==gifts[j]):
                dd=j
                break
        temp2=boxes[j]
        boxes[j]=boxes[i]
        boxes[i]=temp2

for i in range((len (gifts))):
    print(gifts[i],"=>",boxes[i])

print("---------")


quickSort(gifts, 0, len(gifts) - 1,boxes)

for i in range((len (gifts))):
    print(gifts[i],"=>",boxes[i])


for i in range((len(gifts))):
    if (gifts[i] == boxes[i]):
        cc += 1

print(str(cc) + " gifts will be boxed properly...")