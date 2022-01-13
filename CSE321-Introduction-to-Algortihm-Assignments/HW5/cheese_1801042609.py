def getMaxValue(weights, prices, capacity):
        values = []
        for i in range(len(weights)):
            values.append([prices[i]//weights[i],weights[i],prices[i]])

        values.sort(reverse=True)

        totalValue = 0
        for i in values:
            currentWeight = int(i[1])
            currentPrice = int(i[2])
            if capacity - currentWeight >= 0:
                capacity -= currentWeight
                totalValue += currentPrice
            else:
                fraction = capacity / currentWeight
                totalValue += currentPrice * fraction
                capacity = int(capacity - (currentWeight * fraction))
                if(capacity<=0):
                    break
        return totalValue

weights = [10, 40, 20, 30]
prices = [60, 40, 100, 120]
capacity = 50

print(weights)
print(prices)
maxValue = getMaxValue(weights, prices, capacity)
print("Maximum value =", maxValue)

print(weights)
print(prices)
weights = [20, 80, 40, 60]
prices = [60, 40, 100, 120]
capacity = 100

maxValue = getMaxValue(weights, prices, capacity)
print("Maximum value =", maxValue)