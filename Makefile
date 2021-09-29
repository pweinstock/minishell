CC = gcc

NAME = minishell
D_NAME = minishell_debug

LFLAGS = -L$$HOME/.brew/opt/readline/lib -lreadline
CPFLAGS = -I$$HOME/.brew/opt/readline/include

SDIR = ./srcs/
OBJDIR = ./objs/
DEBUGDIR = ./debug/

CFLAGS = -Wall -Werror -Wextra
OBJECTS = $(OBJDIR)/*.o
D_OBJECTS = $(DEBUGDIR)/*.o

SRC =	./srcs/main.c							\
		./srcs/ft_utils.c						\
		./srcs/ft_utils2.c						\
		./srcs/ft_split.c						\
		./srcs/px.c								\
		./srcs/px_cmd.c							\
		./srcs/px_fork.c						\
		./srcs/px_error.c						\
		./srcs/px_parse.c						\

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o $(NAME)

test: $(D_OBJECTS)
	$(CC) $(D_OBJECTS) $(LIBFT) -o $(D_NAME)

$(OBJECTS): $(SRC)
	$(CC) -c $(CFLAGS) $(CPFLAGS) $(SRC)
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
