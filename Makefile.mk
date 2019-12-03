CC		:= gcc
CFLAGS	:= -g


ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
else
EXECUTABLE	:= main
endif


$(EXECUTABLE): server.c client.c
	$(CC) $(CFLAGS)  $^ -o $@