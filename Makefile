CC=gcc
TARGET=test
DEPS=fast_itoa
CFLAGS+=-Wall -Wextra -Werror -Wpedantic -std=c2x -O3
LDFLAGS+=-lm

all: $(TARGET)

$(TARGET): $(TARGET).c $(DEPS).o $(DEPS).h
	$(CC) $(CFLAGS) $(LDFLAGS) $(DEPS).o $(TARGET).c -o $(TARGET)

intel: CFLAGS+=-arch x86_64 
intel: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(DEPS).o