TARGET = prog
OBJS = arraylist.o main.o
CFLAGS = -Wall

$(TARGET) : $(OBJS)
	@gcc $(CFLAGS) $(OBJS) -o $(TARGET)

main.o : main.c arraylist.h

diccionario.o : arraylist.c

.PHONY : clean
clean: 
	rm -f *.o $(TARGET)