CC=gcc
TARGET=srtf
SRC=strf_process_sched.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) input.txt

clean:
	rm -f $(TARGET)
