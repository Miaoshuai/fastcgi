main:main.o fcgi.o tools.o
	clang++ -std=c++11  main.o fcgi.o tools.o -o main
main.o:fcgi.h tools.h
	clang++ -std=c++11 -c  main.cpp
fcgi.o:fcgi.h
	clang++ -std=c++11 -c fcgi.cpp
tools.o:tools.h
	clang++ -std=c++11 -c tools.cpp
.PHONY:clean
clean:
	rm *.o main
