#!/usr/bin/python3

import board

def f(a):
	global h
	if h == 1:
		l = [2, 1]
	else:
		l = [1, 2]
	l += [4, 3, 0]
	while a.deadlock(l[0]) and l[0] != 0:
		l = l[1:]
	h = l[0]
	return h

h = 0
board.main(f)
