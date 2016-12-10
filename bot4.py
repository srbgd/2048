#!/usr/bin/python3

import board

def f(a):
	max = 0
	ans = 0
	for i in range(1, 5):
		if not a.deadlock(i):
			b = a.copy()
			t = b.move(i)
			if (t >= max):
				ans = i
				max = t
	return ans


board.main(f)
