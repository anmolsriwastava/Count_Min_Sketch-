import hashlib

class CountMinSketch:
    def __init__(self, depth, width):
        self.d = depth
        self.w = width
        self.table = [[0] * width for _ in range(depth)]

    def _hash(self, item, i):
        # Use hashlib with different seeds
        h = hashlib.md5((item + str(i)).encode()).hexdigest()
        return int(h, 16) % self.w

    def update(self, item, count=1):
        for i in range(self.d):
            idx = self._hash(item, i)
            self.table[i][idx] += count

    def estimate(self, item):
        return min(self.table[i][self._hash(item, i)] for i in range(self.d))


# Example usage
cms = CountMinSketch(5, 100)
cms.update("apple")
cms.update("apple")
cms.update("banana")

print("apple count ≈", cms.estimate("apple"))
print("banana count ≈", cms.estimate("banana"))
print("orange count ≈", cms.estimate("orange"))
