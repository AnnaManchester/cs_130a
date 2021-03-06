TEMPLATES = list.h doubly_linked_list.h
OBJS = basic.o
OBJS += wall_post.o
OBJS += wall.o
OBJS += user.o
OBJS += user_network.o
OBJS += main.o

CC = g++
CCFLAGS = -std=c++0x -g
%.o: %.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

run: ${OBJS} ${TEMPLATES}
	$(CC) $(CCFLAGS) ${OBJS} -o $@

.PHONY: test
test: ${TEMPLATES} list_array.h test_list.cpp
	$(CC) $(CCFLAGS) test_list.cpp -o test_list
.PHONY: gen
gen: gen_userdata.cpp
	$(CC) $(CCFLAGS) gen_userdata.cpp -o gen 


.PHONY: all
all: run

.PHONY: clean
clean:
	rm -rf $(OBJS) run test_list gen
