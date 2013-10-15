e="`pwd | sed 's/^.*\///'`"
o="$e.out"
i="$e.in"
a="$e.answer"

default: test

build:
	@g++ -lm -O2 -g -Wall -Wno-long-long -pedantic *.cpp -o $e

run: build
	@./$e < $i

test: build
	@./$e < $i > $o
	@diff $o $a

prep:
	mkdir $p
	cd $p; vim $p.in; vim $p.answer
	echo 'include ../Makefile' > $p/Makefile
	cp template.cpp $p/$p.cpp
	vim $p/$p.cpp

clip:
	cat $e.cpp | xclip -selection clipboard

clean:
	rm $e $o
