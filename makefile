CLS = clear
DEL = rm

LIB = $(wildcard ./lib/**.cpp)

pa: # Run parent
	g++ -o a-parent/main.o a-parent/main.cpp
	$(CLS)
	@echo ">>> Running parent <<<"
	./a-parent/main.o
	$(DEL) a-parent/main.o

ch: # Run child
	g++ -o b-child/main.o b-child/main.cpp
	$(CLS)
	@echo ">>> Running child <<<"
	./b-child/main.o
	$(DEL) b-child/main.o

t:
	echo $(LIB)