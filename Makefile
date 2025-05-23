# Nombre del compilador
CC = gcc

# Opciones del compilador
CFLAGS = -Wall -g

# Archivos de origen
SRCS = main.c DataManager.c Interface.c CsvParser.c

# Archivos objeto
OBJS = $(SRCS:.c=.o)

# Nombre del ejecutable
EXEC = DataManager

# Regla principal
all: $(EXEC)

# Regla para crear el ejecutable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Regla para compilar los archivos .c en archivos .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean