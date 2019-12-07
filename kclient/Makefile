CC		:= gcc
CFLAGS	:= -g

all: kclient kserver

kclient: kclient.c
	$(CC) $(CFLAGS)  kclient.c -o kclient

kserver: kserver.c
	$(CC) $(CFLAGS) kserver.c -o kserver