#!/bin/bash


function check () {
	p=$(mktemp -u)
	mkfifo $p
	./2048 <$p | ./$bot >$p
	rm $p
}

function out () {
	echo -e "${1}\tSteps: ${2}\tScore: ${3}\tTime: ${4}"
	steps=$((${2}+$steps))
	score=$((${3}+$score))
	time=$((${4}+$time))
	max_st=$(($max_st<${2}?${2}:$max_st))
	max_sc=$(($max_sc<${3}?${3}:$max_sc))
	max_ti=$(($max_ti<${4}?${4}:$max_ti))
	min_st=$(($min_st>${2}?${2}:$min_st))
	min_sc=$(($min_sc>${3}?${3}:$min_sc))
	min_ti=$(($min_ti>${4}?${4}:$min_ti))
}

bot=${1:-bot}
count=${2:-10}
steps=0
score=0
time=0
max_st=0
max_sc=0
max_ti=0
min_st=$(((2**63)-1))
min_sc=$(((2**63)-1))
min_ti=$(((2**63)-1))
for i in $(eval echo {1..$count})
do
	err=$((check) 2>&1)
	arr=(${err// / })
	out "$i:" "${arr[@]}"
done

out "Average:\n" $(($steps / $count)) $(($score / $count)) $(($time / $count))
out "Min:\n" $min_st $min_sc $min_ti
out "Max:\n" $max_st $max_sc $max_ti
