CC		:= gcc
CFLAGS	:= -g


ifeq ($(OS),Windows_NT)
EXECUTABLE	:= kclient.exe
else
EXECUTABLE	:= kclient
endif


$(EXECUTABLE): kclient.c
	$(CC) $(CFLAGS)  $^ -o $@