.PHONY: test

test: gcd
	./gcd

LIBPATH=${HOME}/local/lib
CPPFLAGS=-I${HOME}/local/include
LDFLAGS=-L${LIBPATH} -lgtest -lgtest_main -lpthread
CXXFLAGS=-Wall -O3

gcd: gcd.cc
	LD_RUN_PATH=${LIBPATH} ${CXX} ${CXXFLAGS} ${CPPFLAGS} ${LDFLAGS} $< -o $@