TARGET=main
INCLUDE=-I./
LIBS=-L./ -ldl
FLAGS=-Wall -O -fPIC

$(TARGET):libsubclass.so main.o
	g++ -o $(@) main.o $(FLAGS)

libsubclass.so:subClass.o
	g++ -shared -o $(@) $(^) $(LIBS)

subClass.o:subClass.cpp
	g++ -c $(<) -o $(@) $(INCLUDE)

main.o:main.cpp
	g++ -c $(<) -o $(@) $(INCLUDE)

.PHONY: clean
clean:
	rm -fR $(TARGET) *~ *.o *.so
