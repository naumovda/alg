import random

def heapify(bunch):
    swaps = 0
    i = len(bunch)
    while i > 1:
        j = i
        idx1 = j-1
        idx2 = idx1//2
        while (bunch[idx1] < bunch[idx2]):
            bunch[idx1], bunch[idx2] = bunch[idx2], bunch[idx1]
            swaps += 1
            j = j // 2
            idx1 = j-1
            idx2 = idx1//2
        print("i=",i,"bunch=",bunch,"swap=",swaps)
        i-=1
    return swaps

def main():
    #bunch = [random.randint(0,100) for _ in range(16)] 
    bunch = [i for i in range(16, 0, -1)] 
    
    
    print("source bunch=", bunch)
    
    swaps = heapify(bunch)
    
    print("result bunch=", bunch)
    print("swaps=", swaps)    

if __name__ == "__main__":
    main()