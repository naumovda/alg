def getMinPolygon_N(min, max, greeds: list):
    points = list()

    idx = 0
    while greeds_max[idx] is None:
        idx += 1

    prev_point = (idx+min, greeds_max[idx]-1) # -1 is a magic const)
    point = (idx+min, greeds_max[idx])
    
    while True:
        # find min cos in greed_max[idx..max-min]
        next_point = None
        min_cosAngle = 1
        idx_point = None
        for idx_next in range(idx+1, max-min+1):
            if greeds_max[idx_next] is not None: 
                cosAngle = getAngleCos(prev_point, point, (idx_next+min, greeds_max[idx_next]))
                if cosAngle <= min_cosAngle:
                        min_cosAngle = cosAngle
                        next_point = (idx_next+min, greeds_max[idx_next])
                        idx_point = idx_next
        points.append(point)
        if next_point is None:
            break
        prev_point = point
        point = next_point
        idx = idx_point

    idx = max-min
    while greeds_max[idx] is None:
        idx -= 1

    prev_point = (idx+min, greeds_min[idx]-1) # -1 is a magic const)
    point = (idx+min, greeds_min[idx])
    
    while True:
        next_point = None
        min_cosAngle = 1
        idx_point = None
        # find min cos in greed_min[...]
        for idx_next in range(idx-1, -1, -1):
            if greeds_min[idx_next] is not None: 
                cosAngle = getAngleCos(prev_point, point, (idx_next+min, greeds_min[idx_next]))
                if cosAngle <= min_cosAngle:
                        min_cosAngle = cosAngle
                        next_point = (idx_next+min, greeds_min[idx_next])
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

        # if greeds_min[x-min] is None:
        #     greeds_min[x-min] = y
        # elif greeds_min[x-min] > y:
        #     greeds_min[x-min] = y
        # if greeds_max[x-min] is None:
        #     greeds_max[x-min] = y
        # elif greeds_max[x-min] < y:
        #     greeds_max[x-min] = y