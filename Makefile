CC = cc
CFLAGS = -g3 -Wall -Werror -Wextra #-fsanitize=address

SRCPARSING  = parsing
SRCEXEC = exec
OBJDIR  = obj

SRCS = $(SRCEXEC)/exec.c $(SRCEXEC)/env.c $(SRCEXEC)/ft_strjoin_pool.c $(SRCPARSING)/minishell.c $(SRCPARSING)/utils.c $(SRCPARSING)/set_cmd.c \
		$(SRCPARSING)/set_cmd_utils.c $(SRCPARSING)/manage_redirection.c \
		$(SRCPARSING)/check_syntax.c $(SRCPARSING)/ft_split_shell.c \
		$(SRCPARSING)/check_syntax_2.c $(SRCPARSING)/manage_redirection_2.c \
		$(SRCPARSING)/poubelle_fonction.c \

OBJS = $(patsubst $(SRCEXEC)/exec.c $(SRCEXEC)/exec.c $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
 

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
