UTILS_DIR=/home/andrew/Documents/coursera_cppspecialization/utils/

CC=g++
CFLAGS=-std=c++17 -W -Wextra -Wall -Werror -I${UTILS_DIR}

all: main.out

main.out: main.o search_server.o parse.o index.o
	${CC} $^ -o $@ ${CFLAGS}

main.o: main.cpp search_server.h parse.h
	${CC} -c $< -o $@ ${CFLAGS}

search_server.o: search_server.cpp search_server.h parse.h
	${CC} -c $< -o $@ ${CFLAGS}

parse.o: parse.cpp parse.h iterator_range.h
	${CC} -c $< -o $@ ${CFLAGS}

index.o: index.cpp index.h parse.h
	${CC} -c $< -o $@ ${CFLAGS}

zip:
	zip attempt.zip *.h *.cpp

debug: CFLAGS+= -g
debug: main.out

release: CFLAGS+= -O3
release: main.out

clean:
	rm -rf *.o *.out *.zip
