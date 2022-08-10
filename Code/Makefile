all: a.out

a.out: main.o utrello_interface.o User.o Task.o List.o
	g++ main.o utrello_interface.o User.o Task.o List.o

main.o: main.cpp utrello_interface.hpp
	g++ -c main.cpp

utrello_interface.o: utrello_interface.cpp utrello_interface.hpp User.h Task.h List.h
	g++ -c utrello_interface.cpp

User.o: User.cpp User.h Task.h List.h
	g++ -c User.cpp

Task.o: Task.cpp User.h Task.h List.h
	g++ -c Task.cpp

List.o: List.cpp User.h Task.h List.h
	g++ -c List.cpp

.PHONY: clean
clean:
	rm *.o 
	rm a.out
