CC=gcc
CFLAGS=-c
LDFLAGS=-pthread
SOURCES=main.c object_factory.c thread_handler.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=cal_train

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)