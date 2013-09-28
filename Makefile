EXECUTABLE="`pwd | sed 's/^.*\///'`"
OUTPUT_FILE="${EXECUTABLE}.out"
UVA_INPUT_FILE="`find . -name *.in`"
UVA_OUTPUT_FILE="`find . -name *.in | sed 's/in$$/answer/'`"

CC=g++
CC_FLAGS=-lm -lcrypt -O2 -pipe -DONLINE_JUDGE

default: test

build:
	@$(CC) $(CC_FLAGS)  *.cpp -o ${EXECUTABLE}

run:
	@./${EXECUTABLE} < ${UVA_INPUT_FILE}

test: build
	@./${EXECUTABLE} < ${UVA_INPUT_FILE} > ${OUTPUT_FILE}
	@diff ${OUTPUT_FILE} ${UVA_OUTPUT_FILE}

clip:
	cat ${EXECUTABLE}.cpp | xclip -selection clipboard

clean:
	@rm ${EXECUTABLE} ${OUTPUT_FILE}
