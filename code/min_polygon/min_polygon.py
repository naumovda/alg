import time

def readData(fileName):
    data = list()
    
    with open(fileName,'r') as f: 
        data_size = int(f.readline())

        while True:
            if (len(data) == data_size):
                break
            str = f.readline()
            coord = str.split()
            data.append((int(coord[0]), int(coord[1])))

    return data
    
def getAngleCos(p1, p2, p3):
    x1 = p2[0]-p1[0]
    x2 = p2[0]-p3[0]
    y1 = p2[1]-p1[1]
    y2 = p2[1]-p3[1]
    
    d1 = x1*x1 + y1*y1
    d2 = x2*x2 + y2*y2

    r = (x1*x2 + y1*y2) 

    if d1 == 0 or d2 == 0:
        return 1

    return r/d1/d2

def getMinPolygon(data: list):
    points = list()

    # find left point
    left = data[0]
    for i in range(1, len(data)):
        if data[i][0] < left[0]:
            left = data[i]

    # first_step = True
  
    current_point = left
    previous_point = left[0], left[1] - 1

    while True:
        # find next point
        min_cosAngle = 1
        next_point = None, None
        for point in data:
            # try:
            cosAngle = getAngleCos(previous_point, current_point, point)
            if cosAngle <= min_cosAngle:
                min_cosAngle = cosAngle
                next_point = point
                    # first_step = False
            # except:
            #     pass
        
        points.append(current_point)

        if next_point == left:
            points.append(next_point)
            break

        previous_point = current_point
        current_point = next_point
    
    return points
    
def getPolygonPerimeter(data: list):
    return 0

if __name__ == "__main__":
    # t1 = time.time()

    dir = './code/min_polygon/'      
    
    data = readData(dir + 'test_mp0.txt')   

    print(data)
    
    res = getMinPolygon(data)

    # t2 = time.time()
    # print('time=', t2-t1)
    
    print(res)
