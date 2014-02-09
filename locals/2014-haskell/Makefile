e="`pwd | sed 's/^.*\///'`"
o="$e.out"
i="$e.in"
a="$e.answer"

run:
	@runhaskell $e.hs

test:
	@runhaskell $e.hs < $i > $o
	@diff $o $a

prep:
	mkdir $p
	cd $p; vim $p.in; vim $p.answer
	echo 'include ../Makefile' > $p/Makefile
	cp template.hs $p/$p.hs
	vim $p/$p.hs
