CXX=g++
FLAGS=-std=c++11 -stdlib=libc++
all:
	$(CXX)	$(FLAGS)	vmsim.cpp	-o	vmsim
	$(CXX)	$(FLAGS)	vmgenU.cpp	-o	vmgenU
	$(CXX)	$(FLAGS)	vmgenWS.cpp	-o	vmgenWS
clean:
	rm	-fr	vmsim	vmgenU	vmgenWS
.PHONY:	all	clean