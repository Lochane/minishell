CC = cc
CFLAGS = -g3 -Wall -Werror -Wextra #-fsanitize=address

SRCSIGNALS = signals
SRCPARSING  = parsing
SRCBUILTIN = builtin
SRCHEREDOC = heredoc
SRCEXPAND = expansion
SRCEXEC = exec
OBJDIR  = obj
MAKEFLAGS += --no-print-directory

SRCS =  $(SRCEXPAND)/expansion.c $(SRCEXPAND)/utils.c $(SRCEXPAND)/utils2.c $(SRCEXPAND)/utils3.c\
		$(SRCEXEC)/init_env.c $(SRCEXEC)/init_env_util.c $(SRCEXEC)/quit.c $(SRCEXEC)/init_exec.c $(SRCEXEC)/redir.c $(SRCEXEC)/redir_utils.c $(SRCEXEC)/access.c $(SRCEXEC)/access_utils.c $(SRCEXEC)/exec.c $(SRCEXEC)/wait.c $(SRCEXEC)/env.c $(SRCEXEC)/env_utils.c $(SRCEXEC)/utils.c  \
		$(SRCPARSING)/set_cmd_utils.c $(SRCPARSING)/manage_redirection.c \
		$(SRCPARSING)/check_syntax.c $(SRCPARSING)/ft_split_shell.c \
		$(SRCPARSING)/check_syntax_2.c $(SRCPARSING)/manage_redirection_2.c \
		$(SRCPARSING)/utils.c $(SRCPARSING)/set_cmd.c  $(SRCPARSING)/utils2.c\
		$(SRCBUILTIN)/builtin.c $(SRCBUILTIN)/env.c $(SRCBUILTIN)/builtin_util.c $(SRCBUILTIN)/cd.c $(SRCBUILTIN)/echo.c $(SRCBUILTIN)/exit.c \
		$(SRCBUILTIN)/export.c $(SRCBUILTIN)/export_utils.c $(SRCBUILTIN)/pwd.c $(SRCBUILTIN)/unset.c $(SRCBUILTIN)/ft_strjoin_pool.c\
		$(SRCHEREDOC)/heredoc.c $(SRCHEREDOC)/heredoc_util.c \
		$(SRCSIGNALS)/signals.c \
		minihell.c \

OBJS = $(patsubst $(SRCHEREDOC)/%.c $(SRCEXPAND)%.c $(SRCBUILTIN)/%.c $(SRCEXEC)/exec.c \
		$(SRCEXEC)/utils.c $(SRCSIGNALS)/%.c $(SRCDIR)/%.c,\
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

valgrind2: all
		valgrind -q --suppressions=$(PWD)/ignore_readline2 --trace-children=yes \
		--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes    \
    	./minishell

valgrind3: all
		valgrind --trace-children=yes --track-fds=yes --leak-check=full ./minishell


re: fclean all

.PHONY: all lib clean fclean re norme
