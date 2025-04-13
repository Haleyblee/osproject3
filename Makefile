CC = gcc
CFLAGS = -Wall -g
TARGET = srtf_process_sched

all: $(TARGET)

$(TARGET): main.c srtf_process_sched.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c srtf_process_sched.c

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
