TARGET = prog
OBJS = estructuraLexico/estructuraLexico.o Diccionario/diccionario.o analizadorLexico.o
CFLAGS = -Wall

$(TARGET) : $(OBJS)
	@gcc $(CFLAGS) $(OBJS) -lm -o $(TARGET)

analizadorLexico.o : analizadorLexico.c Diccionario/diccionario.h estructuraLexico/estructuraLexico.h

Diccionario/diccionario.o : Diccionario/diccionario.c

analizadorLexico/analizadorLexico.o : analizadorLexico/analizadorLexico.c

.PHONY : clean
clean: 
	rm -f Diccionario/*.o Diccionario/$(TARGET)