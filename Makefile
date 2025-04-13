CC = gcc
CFLAGS = -Wall -g
TARGET = srtf_process_sched
SRC = main.c srtf_process_sched.c

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) -lm

clean:
	rm -f $(TARGET)
