output: main.o
	gcc main.o -o main

main.o: main.c
	gcc  main.c -lpthread

pthread101.o: pthread101.c
	gcc pthread101.c -lpthread

clean:
	rm *.o main

# gcc pthread101.c main.c -o main -pthread


