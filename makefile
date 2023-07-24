CLS = clear
DEL = rm

LIB = $(wildcard ./lib/**.cpp)

pa: # Run parent
	g++ -o main.o main.cpp $(LIB)
	$(CLS)
	@echo ">>> Running parent <<<"
	./main.o
	$(DEL) main.o

tm:
	g++ -o ./test/testm.o ./test/testShMem.cpp $(LIB)
	$(CLS)
	./test/testm.o
	$(DEL) ./test/testm.o

t:
	g++ -o ./test/test.o ./test/test.cpp $(LIB)
	$(CLS)
	./test/test.o
	$(DEL) ./test/test.o