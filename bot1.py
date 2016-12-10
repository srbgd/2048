#!/usr/bin/python3

import random
import board

def f(a):
	l = [1, 2, 3, 4]
	ans = random.choice(l)
	while a.deadlock(ans) and l != []:
		ans = random.choice(l)
		del l[l.index(ans)]
	if l == [] and a.deadlock(ans):
		ans = 0
	return ans


board.main(f)
