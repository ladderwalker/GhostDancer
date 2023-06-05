BIN=ghostdancer

all : $(BIN)

$(BIN) : $(wildcard ./src/*.c)
	gcc -o ./build/$@ $^ -g -lX11 -lXfixes -lpthread -lXinerama -lXext -lGL -lm -ldl -DCNFGOGL -lasound

run :
	./build/$(BIN)

debug :
	gdb ./build/$(BIN)

clean :
	rm -rf *.o *~ ./build/$(BIN)
