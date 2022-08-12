CC = g++
CC_INCLUDE = $(patsubst %, -I%, $(shell find src -type d))
CC_FLAGS = -ggdb -pipe -O0

LIBARIES = -lsfml-graphics -lsfml-window -lsfml-system -lpthread
SRC_DIR = src/
OUTPUT = build/miniCPU
SOURCE = $(wildcard $(SRC_DIR)*.cpp) $(wildcard $(SRC_DIR)*/*.cpp)
OBJECTS = $(SOURCE:.cpp=.o)



all: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUTPUT) $(LIBARIES)
	find . -name "*.o" | xargs -r rm 

%.o: %.cpp
	$(CC) $(CC_INCLUDE) -c $< -o $@ $(CC_FLAGS)

clean:
	find . -name "*.o" | xargs -r rm 