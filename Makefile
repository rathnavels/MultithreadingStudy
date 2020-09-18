CC 		= gcc
CFLAGS 		= -Wall
LDFLAGS		= -lpthread	
OBJFILES	= pthread101.o main.o
TARGET 		= main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~

