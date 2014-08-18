GXX=g++
FLAGS=-g -c
LDFLAGS=-ldl
RDYNAMIC=-rdynamic
INSTRUMENT=-finstrument-functions
MAIN=main
TRACE=trace

all:
	${GXX} ${FLAGS} ${RDYNAMIC} ${INSTRUMENT} ${MAIN}.cpp
	${GXX} ${FLAGS} ${RDYNAMIC} ${TRACE}.cpp
	${GXX} ${LDFLAGS} ${RDYNAMIC} ${MAIN}.o ${TRACE}.o -o ${MAIN}
	${CURDIR}/./${MAIN}	

clean:
	rm -rf *.o main
