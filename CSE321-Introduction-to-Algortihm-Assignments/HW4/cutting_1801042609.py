def takelog(n):
    if (n<=2):
        return 1
    else:
        return takelog(n/2) + 1

def cut(n):
    if(n<=1):
        return 0
    return takelog(n)


n=1
print("----------")
print("Expected cut: 0")
print("n=1, Calculated cuts: ",cut(n))

n=2
print("----------")
print("Expected cut: 1")
print("n=2, Calculated cuts: ",cut(n))

n=3
print("----------")
print("Expected cut: 2")
print("n=3, Calculated cuts: ",cut(n))

n=4
print("----------")
print("Expected cut: 2")
print("n=4, Calculated cuts: ",cut(n))

n=5
print("----------")
print("Expected cut: 3")
print("n=5, Calculated cuts: ",cut(n))

n=6
print("----------")
print("Expected cut: 3")
print("n=6, Calculated cuts: ",cut(n))

n=7
print("----------")
print("Expected cut: 3")
print("n=7, Calculated cuts: ",cut(n))

n=8
print("----------")
print("Expected cut: 3")
print("n=8, Calculated cuts: ",cut(n))

n=9
print("----------")
print("Expected cut: 4")
print("n=9, Calculated cuts: ",cut(n))

n=10
print("----------")
print("Expected cut: 4")
print("n=10, Calculated cuts: ",cut(n))

n=100
print("----------")
print("Expected cut: 7")
print("n=100, Calculated cuts: ",cut(n))

n=18
print("----------")
print("Expected cut: 5")
print("n=18, Calculated cuts: ",cut(n))

n=20
print("----------")
print("Expected cut: 5")
print("n=20, Calculated cuts: ",cut(n))


