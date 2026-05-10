.PHONY: clean
NAME := main
SRC := main.cpp
LIBS := -lraylib -lopengl32 -lgdi32 -lwinmm
STD := c++20
main: $(SRC)
	g++ --std=$(STD) -o $(NAME) $(SRC) $(LIBS)
clean:
	rm -rf *.exe