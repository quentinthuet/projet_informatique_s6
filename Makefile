CC = g++
CFLAGS = -Wall
EXEC_NAME = run
EXEC_NAME2 = tests
OBJ_FILES = main.o complexe.o signal_discret.o signal_continu.o signal_discret_stl.o
TEST_FILES = tests_units.o complexe.o signal_discret.o signal_continu.o signal_discret_stl.o

all : $(EXEC_NAME)

clean :
	rm $(EXEC_NAME) $(OBJ_FILES)

cleantests :
	rm $(EXEC_NAME2) $(TEST_FILES)

$(EXEC_NAME) : $(OBJ_FILES) filtre.hpp
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES)

$(EXEC_NAME2) : $(TEST_FILES) filtre.hpp
	$(CC) -o $(EXEC_NAME2) $(TEST_FILES) 

%.o: %.cpp %.hpp
	$(CC) -o $@ -c $<

tests_units.o : tests_units.cpp filtre.hpp

main.o : main.cpp filtre.hpp

