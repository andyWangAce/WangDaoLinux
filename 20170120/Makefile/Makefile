SOURCES:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SOURCES))
CFLAGS:=-g
CC:=gcc
ELF:=main
$(ELF):$(OBJS)
	$(CC) $^ -o $@
.PHONY:clean
clean:
	rm $(OBJS) $(ELF)
