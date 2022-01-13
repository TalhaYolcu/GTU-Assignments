def merge(arr, left, mid, right):
    count = 0
    n1 = mid - left + 1
    n2 = right - mid
    LEFT = [0] * (n1)
    RIGHT = [0] * (n2)

    for i in range(0, n1):
        LEFT[i] = arr[left + i]

    for j in range(0, n2):
        RIGHT[j] = arr[mid + 1 + j]
    i = 0
    j = 0
    k = left
    while i < n1 and j < n2:
        if LEFT[i] <= RIGHT[j]:
            arr[k] = LEFT[i]
            i += 1
        else:
            arr[k] = RIGHT[j]
            count += (n1 - i)
            j += 1
        k += 1

    while i < n1:
        arr[k] = LEFT[i]
        i += 1
        k += 1

    while j < n2:
        arr[k] = RIGHT[j]
        j += 1
        k += 1
    return count



def mergeSort(arr2, left, right):
    if left < right:
        mid = left + (right - left) // 2
        return (mergeSort(arr2, left, mid) + mergeSort(arr2, mid + 1, right) + merge(arr2, left, mid, right))
    return 0


def find_rop(data):
    arr = data.copy()
    return mergeSort(arr, 0, len(arr) - 1)


data = [20, 1, 2, 6, 7, 15, 9, 10]
rop=find_rop(data)
print("---------")
print("Input array",data)
print("Expected number of rop 9:")
print("Calculated number of rop: ",rop)

data=[20,25,97,10,15,0,99]
rop=find_rop(data)
print("---------")
print("Input array",data)
print("Expected number of rop 11:")
print("Calculated number of rop: ",rop)

data=[1, 2, 20, 6, 7, 15, 9, 10]
rop=find_rop(data)
print("---------")
print("Input array",data)
print("Expected number of rop 7:")
print("Calculated number of rop: ",rop)

data=[1, 2, 20, 6, 5, 15, 9, 10]
rop=find_rop(data)
print("---------")
print("Input array",data)
print("Expected number of rop 8:")
print("Calculated number of rop: ",rop)

