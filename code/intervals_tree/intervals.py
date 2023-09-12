def CalcMax(a, b):
    return max(a, b)

class Tree:
    INF = -1

    def __init__(self, data, func):
        self.func = func

        k = 1
        while True:
            if pow(2, k) > len(data):
                break
            k += 1
        k += 1

        self.nodes = [self.INF for _ in range(pow(2, k)-1)]
        self.nodes.append(self.INF)

        self.C = idx = pow(2, k - 1)

        for item in data:
            self.nodes[idx] = item
            self.propagate(idx)
            idx += 1
     
    def propagate(self, idx):
        while idx > 1:
            self.nodes[idx//2] = self.func(self.nodes[idx], self.nodes[idx//2])
            idx //= 2

    def replace(self, idx, value):
        self.nodes[self.C + idx - 1] = value
        self.propagate(self.C + idx - 1)

    def calculate(self, left, right):
        result = self.INF

        if left % 2 == 1:
            result = self.func(result, self.nodes[left])
            left += 1
        if right % 2 == 0:
            result = self.func(result, self.nodes[right])
            right -= 1            
        if right > left:
            result = self.func(result, self.calculate(left//2, right//2))

        return result

    def get_result(self, left, right):
        idx = self.C-1
        return self.calculate(idx + left, idx + right)

def main():
    t = Tree([1, 2, 3, 4, 5], CalcMax)
    print(t.nodes)
    
    t.replace(1, 10)
    print(t.nodes)

    mx = t.get_result(2, 5)
    print(mx)

if __name__ == "__main__":
    main()