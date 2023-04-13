# class Node:
#     def __init__(self, priority, data):
#         self.data = data
#         self.priority = priority

class Heap:
    def __init__(self):
        self.nodes = []
    
    def count(self):
        return len(self.nodes)

    def fetch(self):
        return self.nodes[0] if self.count() > 0 else None

    def insert(self, node):
        self.nodes.append(node)
        idx = self.count()-1
        while idx > 0 and self.nodes[idx] > self.nodes[(idx+1)//2-1]:
            self.nodes[idx], self.nodes[(idx+1)//2-1] = self.nodes[(idx+1)//2-1], self.nodes[idx]

    def heapify(self, i, n):
        current = self.nodes[i]
        index = i
        while True:
            left = index + index + 1, 
            right = left + 1
            
            if left < n & self.nodes[left] > current:
                index = left
            if right < n & self.nodes[right] > self.nodes[index]:
                index = right

            if index == i:
                break
            
            self.nodes[i] = self.nodes[index]
            self.nodes[index] = current

            i = index
    
    def sort(self):
        i = self.count()//2 - 1
        while i >=0:
            self.heapify(i)
            i -= 1

        n = self.count()
        while n > 1:
            n -= 1
            self.nodes[0], self.nodes[n] = self.nodes[n], self.nodes[0]
            self.heapify(0, n)

def main():
    heap = Heap()

    for item in [17, 4, 5, 14, 45, 6, 10, 20, 50]:
        heap.insert(item)
    # heap.insert(4)
    # heap.insert(17)
    # heap.insert(5)
    # heap.insert(14)

    print(heap.nodes)

if __name__ == "__main__":
    main()
