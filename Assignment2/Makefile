CC = g++
CFLAGS = -std=c++11 -Wall

TARGET = TimingAttack

all: $(TARGET)

$(TARGET): TimingAttack.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGET)