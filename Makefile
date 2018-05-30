TARGET = CSV_to_EDF

CPP_FILES = $(shell ls *.cpp)
C_FILES = $(shell ls *.c)
BASE = $(basename $(CPP_FILES))
BASE += $(basename $(C_FILES))

OBJS = $(addsuffix .o,$(addprefix obj/, $(BASE)))

$(TARGET):$(OBJS)
	g++ $(OBJS) -o bin/$(TARGET)
obj/edflib.o:edflib.c
	g++ edflib.c -c -o obj/edflib.o
obj/main.o:main.cpp
	g++ main.cpp -c -o obj/main.o


clean:
	rm -rf obj/*.o bin/$(TARGET)
