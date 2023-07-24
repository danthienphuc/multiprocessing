CLS = clear
DEL = rm

LIB = $(wildcard ./lib/**.cpp)

pa: # Run parent
	g++ -o main.o main.cpp $(LIB)
	$(CLS)
	@echo ">>> Running parent <<<"
	./main.o
	$(DEL) main.o
t:
	g++ -o test.o testShMem.cpp $(LIB)
	$(CLS)
	./test.o
	$(DEL) test.o