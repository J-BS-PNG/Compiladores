TARGET = prog
OBJS = diccionario.o main.o
CFLAGS = -Wall

$(TARGET) : $(OBJS)
	@gcc $(CFLAGS) $(OBJS) -o $(TARGET)

main.o : main.c diccionario.h

diccionario.o : diccionario.c

.PHONY : clean
clean: 
	rm -f *.o $(TARGET)