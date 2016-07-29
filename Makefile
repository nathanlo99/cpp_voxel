SRCS = src/main.cpp
OBJS = $(subst src/,bin/,$(subst .cpp,.o,$(SRCS)))
EXEC = main
CPP = llvm-g++
CPPFLAGS = -std=c++14 -Wall -Wextra -DDEBUG -framework OpenGL

all: $(EXEC)
	./$(EXEC)

clean:
	$(RM) $(EXEC)
	$(RM) $(OBJS)

$(EXEC): $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) -o $(EXEC)

bin/%.o: src/%.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $^

.PHONY: $(EXEC)
