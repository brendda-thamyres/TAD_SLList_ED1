CC = gcc
CFLAGS = -Wall -Wextra -g3
TARGET = output/main.exe
SOURCES = lista.c main.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)