#target : dependency1 dependency2 dependency3 ...
#	action


#compile objects into executable and run
main: main.o Hero.o
	g++ -std=c++11 main.o Hero.o -o main
	./main 

#create .o files 
main.o: main.cpp 
	g++ -std=c++11 -c main.cpp

Hero.o: Hero.cpp Hero.h
	g++ -std=c++11 -c Hero.cpp

clean: 
	rm *.o main