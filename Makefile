CC = cc
CFLAGS = -g3 -Wall -Werror -Wextra #-fsanitize=address

SRCDIR = src
OBJDIR = obj

SRCS = $(SRCDIR)/minishell.c $(SRCDIR)/utils.c $(SRCDIR)/set_cmd.c \
		$(SRCDIR)/set_cmd_utils.c $(SRCDIR)/manage_redirection.c \
		$(SRCDIR)/check_syntax.c $(SRCDIR)/ft_split_shell.c \
		$(SRCDIR)/check_syntax_2.c $(SRCDIR)/manage_redirection_2.c \
		$(SRCDIR)/poubelle_fonction.c $(SRCDIR)/built_in.c\

OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
 

NAME = minishell
LIBPATH = ./libft/libft.a

all: $(NAME)


$(NAME): $(OBJS) | lib
		@echo "			-> Compiling $(NAME)..."
		@$(CC) $(OBJS) $(LIBPATH) $(CFLAGS) -lreadline -o $@
		@echo "			-> Finished $(NAME)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

lib:
	@make -C ./libft

clean:
	@rm -rf $(OBJDIR)
	@make clean -C ./libft

fclean: clean
		@rm -f $(NAME)
		@make fclean -C ./libft

norme:
		norminette $(SRCS)

valgrind: all
		valgrind --suppressions=ignore_readline --trace-children=yes \
		--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes    \
    	./minishell

re: fclean all

.PHONY: all lib clean fclean re norme
