CXX = g++
CXXFLAGS = -Wall -g

mytest: graph.o mytest.cpp
	$(CXX) $(CXXFLAGS) graph.o mytest.cpp -o mytest

graph.o: graph.cpp graph.h
	$(CXX) $(CXXFLAGS) -c graph.cpp

clean:
	rm *.o*
	rm *~

run:
	./mytest

val:
	valgrind ./mytest
