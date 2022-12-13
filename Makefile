BIN=ghostdancer

all : $(BIN)

$(BIN) : $(wildcard ./src/*.c)
	gcc -o ./build/$@ $^ -g -lX11 -lpthread -lXinerama -lXext -lGL -lm -ldl 

run :
	./build/$(BIN)

debug :
	gdb ./build/$(BIN)

clean :
	rm -rf *.o *~ ./build/$(BIN)
