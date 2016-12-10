import sys


class A:
	n = 0
	score = 0

	def __init__(self, n):
		A.n = n
		self.m = [[0 for _ in range(A.n)] for _ in range(A.n)]

	def out(self):
		for i in range(A.n):
			print(self.m[i],file=sys.stderr)
		print(file=sys.stderr)

	def turn(self, side):
		m = [[_ for _ in i] for i in self.m]
		if side not in [1, 2, 3]:
			return
		for _ in range(side):
			for i in range(A.n):
				for j in range(A.n):
					m[i][j] = self.m[j][A.n - i - 1]
			self.m = [[_ for _ in x] for x in m]

	def add_line(self, l):
		t = []
		score = 0
		for i in [i for i in self.m[l] if i]:
			t.append(i)
			while len(t) > 1 and t[-1] == t[-2]:
				t[-2] += 1
				score += 2 ** (t[-1] + 1)
				del t[-1]
		self.m[l] = t + [0 for _ in range(A.n - len(t))]
		return score

	def add(self):
		score = 0
		for i in range(A.n):
			score += self.add_line(i)
		return score

	def move(self, side):
		side = side % 4
		self.turn(side)
		score = self.add()
		self.turn(4 - side)
		self.score += score
		return score

	def update(self, i, j, k):
		self.m[i][j] = k

	def copy(self):
		a = A(A.n)
		a.m = [i[:] for i in self.m]
		a.score = self.score
		return a

	def deadlock(self, side):
		if side == 0:
			return True
		a = self.copy()
		a.move(side)
		return a.m == self.m



def main(f):
	n = 4
	a = A(n)
	b = list(map(int, input().split()))
	a.update(b[0], b[1], 1)
	a.update(b[2], b[3], 1)
	c = 1
	while c != 0:
		c = f(a)
		if c == 0:
			print(5)
			sys.stdout.flush()
			break
		a.move(c)
		print(c)
		b = list(map(int, input().split()))
		a.update(b[0], b[1], b[2])
