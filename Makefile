CC = cc
CFLAGS = -g3 -Wall -Werror -Wextra #-fsanitize=address

SRCPARSING  = parsing
SRCBUILTIN = builtin
SRCHEREDOC = heredoc
SRCEXEC = exec
OBJDIR  = obj

SRCS = expansion/expansion.c $(SRCEXEC)/exec.c $(SRCEXEC)/env.c $(SRCEXEC)/utils.c  \
		$(SRCPARSING)/minihell.c $(SRCPARSING)/utils.c $(SRCPARSING)/set_cmd.c \
		$(SRCPARSING)/set_cmd_utils.c $(SRCPARSING)/manage_redirection.c \
		$(SRCPARSING)/check_syntax.c $(SRCPARSING)/ft_split_shell.c \
		$(SRCPARSING)/check_syntax_2.c $(SRCPARSING)/manage_redirection_2.c \
		$(SRCPARSING)/poubelle_fonction.c \
		$(SRCBUILTIN)/builtin.c $(SRCBUILTIN)/cd.c $(SRCBUILTIN)/echo.c $(SRCBUILTIN)/exit.c \
		$(SRCBUILTIN)/export.c $(SRCBUILTIN)/pwd.c $(SRCBUILTIN)/unset.c $(SRCBUILTIN)/ft_strjoin_pool.c\
		$(SRCHEREDOC)/heredoc.c \

OBJS = $(patsubst $(SRCHEREDOC)/%.c $(SRCBUILTIN)/%.c $(SRCEXEC)/exec.c $(SRCEXEC)/utils.c $(SRCDIR)/%.c,\
		$(OBJDIR)/%.o,$(SRCS))
 

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
