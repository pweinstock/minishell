CC = gcc

NAME = minishell
D_NAME = minishell_debug

SDIR = ./srcs/
OBJDIR = ./objs/
DEBUGDIR = ./debug/

CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
CPPFLAGS = -I /Users/$(USER)/.brew/opt/readline/include

OBJECTS = $(OBJDIR)/*.o
D_OBJECTS = $(DEBUGDIR)/*.o

SRC =	./srcs/main.c						\

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) $(OBJECTS) -o $(NAME)

test: $(D_OBJECTS)
	$(CC) $(D_OBJECTS) $(LIBFT) -o $(D_NAME)

$(OBJECTS): $(SRC)
	@$(CC) -c $(CFLAGS) $(SRC)
	rm -rf ./objs; mkdir ./objs
	mv *.o $(OBJDIR)

$(D_OBJECTS): $(SRC)
	@$(CC) -c $(SRC)
	rm -rf ./debug; mkdir ./debug
	mv *.o $(DEBUGDIR)

clean:
	rm -f $(OBJECTS) $(D_OBJECTS)
	rm -rf ./objs ./debug

fclean: clean
	@rm -f $(NAME) $(D_NAME)

re: fclean all

testre: fclean test
