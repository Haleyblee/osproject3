CC=gcc
TARGET=srtf
SRC=STRF.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) input.txt

clean:
	rm -f $(TARGET)
