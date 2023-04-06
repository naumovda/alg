bunch = [1, 2, 2, 4, 4, 4, 5, 6, 7, 8, 9]

def lbs(bunch, item, left, right):
    while right - left > 1:
        middle = (right + left) // 2
        if bunch[middle] < item:
            left = middle
        else:
            right = middle
    return left

def rbs(bunch, item, left, right):
    while right - left > 1:
        middle = (right + left) // 2
        if bunch[middle] <= item:
            left = middle
        else:
            right = middle
    return right

def main():
    print("bunch=", bunch)
    key = 11 
    print(lbs(bunch, key, -1, len(bunch)))
    print(rbs(bunch, key, -1, len(bunch)))

if __name__ == "__main__":
    main()
