import random

def writeData(fileName: str, size: int, low: int, high: int):
    f = open(fileName,'w')

    f.write(str(size)+'\n')

    try:
        for i in range(size):
            f.write(str(random.randrange(low, high)) 
                + ' ' + str(random.randrange(low, high)) 
                + '\n')
    finally:
        f.close()
    
if __name__ == "__main__":
    dir = './code/min_polygon/'
    fileName = 'test_mp5.txt'

    # writeData(dir + fileName, 1000, -1000, 1000)
    # writeData(dir + fileName, 20, -10, 10)
    # writeData(dir + fileName, 2000, -1000000, 1000000)
    writeData(dir + fileName, 499999, -10000, 10000)

    print('writting ' + fileName + ' is done!')