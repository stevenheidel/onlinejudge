e="`pwd | sed 's/^.*\///'`"
o="$e.answer"
i="$e.in"
a="$e.out"

default: test

build:
	@g++ -lm -g -Wall -Wno-long-long -pedantic $e.cpp -o $e

run: build
	@./$e < $i

test: build
	@./$e < $i > $o
	@diff $o $a

prep:
	mkdir $p
	echo 'include ../Makefile' > $p/Makefile
	cp template.cpp $p/$p.cpp
	vim $p/$p.cpp

print:
	paf $e.cpp | lpr -Pprn125

printout: 
	paf $o | lpr -Pprn125
