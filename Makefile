CC = gcc
EXEC = myPerceptron
CFALGS = -W -lm
SRC = $(shell find . -name '*.c')
OBJ = $(SRC:.c=.o)

all : $(EXEC) 

$(EXEC) : $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(CFALGS)

%.o : %.C
	$(CC) -o $(OBJ) -c $(SRC)

clean:
	rm -f $(OUT) $(OBJ) $(EXEC)