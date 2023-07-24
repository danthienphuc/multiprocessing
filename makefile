CLS = clear
DEL = rm

LIB = $(wildcard ./lib/**.cpp)

pa: # Run parent
	g++ -o a-parent/main.o a-parent/main.cpp $(LIB) 
	$(CLS)
	@echo ">>> Running parent <<<"
	@sudo ./a-parent/main.o
	$(DEL) a-parent/main.o

ch: # Run child
	g++ -o b-child/main.o b-child/main.cpp $(LIB)
	$(CLS)
	@echo ">>> Running child <<<"
	./b-child/main.o
	$(DEL) b-child/main.o

t:
	g++ -o test.o test.cpp
	$(CLS)
	./test.o
	$(DEL) test.o