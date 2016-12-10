#!/usr/bin/python3

import board

def f(a):
	global h
	ans = h % 4 + 1
	while a.deadlock(ans) and ans != h:
		ans = ans % 4 + 1
	h = ans
	return h

h = 0
board.main(f)
