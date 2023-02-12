import random

def writeData(fileName: str, size: int, low: int, high: int):
    f = open(fileName,'w')

    f.write(str(size)+'\n')

    try:
        for i in range(size):
            f.write(str(random.randrange(low, high))+'\n')
    finally:
        f.close()
    
if __name__ == "__main__":
    dir = './code/max_product3/'
    fileName = 'test_5.txt'

    # writeData(dir + fileName, 1000, -1000, 1000)
    # writeData(dir + fileName, 2000, -1000000, 1000000)
    writeData(dir + fileName, 999999, -1000000, 1000000)

    print('writting ' + fileName + ' is done!')