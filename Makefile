CC 		= gcc
CFLAGS 		= -Wall
LDFLAGS		= -lpthread	
OBJFILES	= main.o pthread101.o pthread102.o pthread103.o 
TARGET 		= main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~

