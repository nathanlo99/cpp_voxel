SRCS = main.cpp
EXEC = main

all: main
	./main

clean: 
	rm main

main: $(SRCS)
	llvm-g++ $(SRCS) -o main

