points = [
    (1, 1),
    (0, 1),
    (1, 0),
    (0, 0),
    (0.5, 0.5)
]

point_set = set(points)

print(points)
print(point_set)

left = points[0]
for item in points:
    if item[0] < left[0]:
        left = item

print(left)

point_set.remove(left)
print(point_set)