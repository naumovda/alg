import time

def readData(fileName = './code/max_product3/test_0.txt'):
    data = list()
    
    f = open(fileName,'r')
    try:
        data_size = int(f.readline())
        while True:
            if (len(data) == data_size):
                break   
            res = int(f.readline())   
            data.append(res)
    finally:
        f.close()
    return data
    
def getMaxProduct3_sort(data: list):
    data.sort() # N * LOG(N)

    max1 = data[len(data)-1] 
    max2 = data[len(data)-2] 
    max3 = data[len(data)-3] 
    min1 = data[0]
    min2 = data[1]

    return max(max1 * max2 * max3, min1 * min2 * max1)

def getMaxProduct3_line(data: list):
    if len(data) < 3:
        raise ValueError('Data array must contain at least 3 values')

    max1 = data[0] 
    max2 = data[1] 
    max3 = data[2] 

    if max1 < max2:
        max1, max2 = max2, max1
    if max1 < max3:
        max1, max3 = max3, max1
    if max2 < max3:
        max2, max3 = max3, max2

    min1 = max3
    min2 = max2

    # invariant: i=3; max1, max2, max3 - max of three, min1, min2 - min of three

    idx = 3
    while idx < len(data):
        if data[idx] > max1:
            max1, max2, max3 = data[idx], max1, max2
        elif data[idx] > max2:
            max2, max3 = data[idx], max2
        elif data[idx] > max3:
            max3 = data[idx]

        if data[idx] < min1:
            min1, min2 = data[idx], min1
        elif data[idx] < min2:
            min2 = data[idx]

        idx += 1

    return max(max1 * max2 * max3, min1 * min2 * max1)

if __name__ == "__main__":
    dir = './code/max_product3/'
    
    t1 = time.time()
    
    data = readData(dir + 'test_5.txt')   
    
    # res = getMaxProduct3_sort(data)
    res = getMaxProduct3_line(data)

    t2 = time.time()

    # print('time=', t2-t1)
    print(res)
    
