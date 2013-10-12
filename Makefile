e="`pwd | sed 's/^.*\///'`"
o="${e}.out"
i="`find . -name *.in`"
a="`find . -name *.in | sed 's/in$$/answer/'`"

c=g++
f=-lm -lcrypt -O2 -pipe -g -Wall -pedantic

default: test

build:
	@$(c) $(f)  *.cpp -o ${e}

run: build
	@./${e} < ${i}

test: build
	@./${e} < ${i} > ${o}
	@diff ${o} ${a}

clip:
	cat ${e}.cpp | xclip -selection clipboard

clean:
	rm ${e} ${o}
