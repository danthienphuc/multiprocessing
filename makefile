CLS = clear
DEL = rm

LIB = $(wildcard ./lib/**.cpp)

pa: # Run parent
	g++ -o main.o main.cpp $(LIB)
	$(CLS)
	./main.o
	$(DEL) main.o

tf:
	g++ -o ./test/testf.o ./test/testFile.cpp $(LIB)
	$(CLS)
	./test/testf.o
	$(DEL) ./test/testf.o

tm:
	g++ -o ./test/testm.o ./test/testShMem.cpp $(LIB)
	$(CLS)
	./test/testm.o
	$(DEL) ./test/testm.o

ts:
	g++ -o ./test/testSocket.o ./test/testSocket.cpp $(LIB)
	$(CLS)
	./test/testSocket.o
	$(DEL) ./test/testSocket.o

t:
	g++ -o ./test/test.o ./test/test.cpp $(LIB)
	$(CLS)
	./test/test.o
	$(DEL) ./test/test.o