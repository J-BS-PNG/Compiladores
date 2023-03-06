TARGET = prog
OBJS = Diccionario/diccionario.o analizadorLexico.o
CFLAGS = -Wall

$(TARGET) : $(OBJS)
	@gcc $(CFLAGS) $(OBJS) -o $(TARGET)

analizadorLexico.o : analizadorLexico.c Diccionario/diccionario.h

Diccionario/diccionario.o : Diccionario/diccionario.c

.PHONY : clean
clean: 
	rm -f Diccionario/*.o Diccionario/$(TARGET)