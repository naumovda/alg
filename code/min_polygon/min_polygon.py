import time

def readData(fileName, dataSize = None):
    data = list()    
    with open(fileName,'r') as f: 
        data_size = int(f.readline())
        if dataSize is not None:
            data_size = dataSize
        while True:
            if (len(data) == data_size):
                break
            str = f.readline()
            coord = str.split()
            data.append((int(coord[0]), int(coord[1])))
    return data

def getDistanceSqr(p1, p2):
    x1 = p2[0]-p1[0]
    y1 = p2[1]-p1[1]
    return x1*x1 + y1*y1

def getAngleCos(p1, p2, p3):
    x1 = p2[0]-p1[0]
    x2 = p2[0]-p3[0]
    y1 = p2[1]-p1[1]
    y2 = p2[1]-p3[1]
    
    d1 = pow(x1*x1 + y1*y1, 0.5)
    d2 = pow(x2*x2 + y2*y2, 0.5)

    r = (x1*x2 + y1*y2) 

    if d1 == 0 or d2 == 0:
        return 1

    return r/d1/d2

def getMinPolygon_N2(data: list):
    points = list()

    current_point = data[0]
    previous_point = data[0][0], data[0][1] - 1

    while True:
        min_cosAngle = 1
        next_point = (None, None)
        for point in data:
            cosAngle = getAngleCos(previous_point, current_point, point)
            if cosAngle <= min_cosAngle:
                min_cosAngle = cosAngle
                next_point = point
        
        points.append(current_point)

        if next_point == data[0]:
            points.append(next_point)
            break

        previous_point = current_point
        current_point = next_point
    
    return points
    
def getMinPolygon_D2(greeds: list):
    points = list()
    
    point = greeds[0]
    prev_point = (point[0], point[1]-1)

    idx = 0
    while True:
        next_point = None
        idx_point = None
        min_cosAngle = 1

        for idx_next in range(idx+1, len(greeds)):
            new_point = greeds[idx_next]
            cosAngle = getAngleCos(prev_point, point, new_point)
            if cosAngle < min_cosAngle: # if (<=) - error!
                    min_cosAngle = cosAngle
                    next_point = new_point
                    idx_point = idx_next
        
        points.append(point)
        
        if next_point is None:
            break
        
        prev_point = point
        point = next_point
        idx = idx_point

    if points[0] != points[len(points)-1]:
        points.append(points[0])
    
    return points

def getPolygonPerimeter(data: list):
    perimeter = 0
    for i in range(0, len(data)-1):
        perimeter += pow(getDistanceSqr(data[i], data[i+1]), 0.5)
    return perimeter

def min_none(value1, value2):
    if value1 is None:
        return value2
    if value2 is None:
        return value1
    return min(value1, value2)

def max_none(value1, value2):
    if value1 is None:
        return value2
    if value2 is None:
        return value1
    return max(value1, value2)

def test_alg(calc_function, filename, dir='./code/min_polygon/', dataSize=None):
    print(calc_function.__name__)
    # print("file:", filename)

    t1 = time.time()          
    
    points = readData(dir + filename, dataSize)

    min_idx = -10000
    max_idx = +10000
    
    greeds_max = [None for _ in range(min_idx, max_idx+1)]
    greeds_min = [None for _ in range(min_idx, max_idx+1)]
    
    for x, y in points:
        greeds_min[x-min_idx] = min_none(greeds_min[x-min_idx], y)
        greeds_max[x-min_idx] = max_none(greeds_max[x-min_idx], y)
   
    points_cut = []
    for x in range(0, max_idx-min_idx+1):
        if greeds_max[x] is not None:
            points_cut.append((x+min_idx, greeds_max[x]))    
    
    offset = 1 if greeds_max[max_idx-min_idx] == greeds_min[max_idx-min_idx] else 0
    
    for x in range(max_idx-min_idx-offset, -1, -1):
        if greeds_min[x] is not None:
            points_cut.append((x + min_idx, greeds_min[x]))

    polygon = calc_function(points_cut)
    perimetr = getPolygonPerimeter(polygon)
    # print(polygon)    

    t2 = time.time()
    
    print(f"p1 = {perimetr:.2f}")
    print(f"time = {t2-t1:.2f} sec.\n")

if __name__ == "__main__":
    filename = 'test_mp5.txt'
    
    # test_alg(getMinPolygon_D2, filename)
    test_alg(getMinPolygon_N2, filename)
