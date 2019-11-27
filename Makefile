CC = gcc
CFLAGS = -g -Wall -I

EXEC = astar_path

SRCDIR = src
OBJDIR = obj
IDIR = include

SRC = $(filter-out src/status.c, $(wildcard $(SRCDIR)/*.c))
DEP = $(wildcard $(IDIR)/*.h)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

CPPFLAGS += # -I is a preprocessor flag, not a compiler flag
CFLAGS += -Wall -I$(IDIR) # some warnings about bad code
LDFLAGS +=
LDLIBS +=

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LFLAGS) $(OBJ) -o $@
	@echo "Linking complete!"

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(DEP)
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

clean:
	rm -rf $(EXEC) $(OBJDIR)
	@echo "Cleanup complete!"

re: fclean all

