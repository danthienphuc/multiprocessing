CLS = clear
DEL = rm

LIB = $(wildcard ./lib/**.cpp)
SOCK += $(wildcard ./lib/socket/**.cpp)

main: # Run main
	g++ -o main.o main.cpp $(LIB) $(SOCK)
	$(CLS)
	./main.o
	$(DEL) main.o

test_server_socket:
	g++ -o ./test/testse.o ./test/testServerSocket.cpp $(LIB) $(SOCK)
	$(CLS)
	./test/testse.o
	$(DEL) ./test/testse.o

test_client_socket:
	g++ -o ./test/testcl.o ./test/testClientSocket.cpp $(LIB) $(SOCK)
	$(CLS)
	./test/testcl.o
	$(DEL) ./test/testcl.o
test_fileIO:
	g++ -o ./test/testf.o ./test/testFile.cpp $(LIB)
	$(CLS)
	./test/testf.o
	$(DEL) ./test/testf.o

test_shmem:
	g++ -o ./test/testm.o ./test/testShMem.cpp $(LIB)
	$(CLS)
	./test/testm.o
	$(DEL) ./test/testm.o

test_socket:
	g++ -o ./test/testSocket.o ./test/testSocket.cpp $(LIB)
	$(CLS)
	./test/testSocket.o
	$(DEL) ./test/testSocket.o

t:
	g++ -o ./test/test.o ./test/test.cpp $(LIB)
	$(CLS)
	./test/test.o
	$(DEL) ./test/test.o