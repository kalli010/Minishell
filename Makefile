NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes -I$(LIBFT_SRC) -g   

LIBFT_SRC = ./lib/libft/
LIBFT = $(LIBFT_SRC)/libft.a

src = ./utils/Minishell.c \
      ./utils/lparsiiiing.c \
      exucutions/run_exucution.c \
      exucutions/get_path.c \
      exucutions/here_doc.c \
      exucutions/helper_fun.c \
      bulutins/ft_env.c \
      bulutins/ft_pwd.c \
	  exucutions/execute_cmd.c \
	  exucutions/redirect.c \

obj = $(src:.c=.o)

all: $(NAME)

$(NAME): $(obj) $(LIBFT)
	$(CC) $(CFLAGS) $(obj) $(LIBFT) -o $(NAME) -lreadline

compile:
	@if make -q $(NAME); then \
		echo "$(NAME) is up to date."; \
	else \
		bash -c ' \
		MK="make $(NAME)"; \
		LOGFILE=$$(mktemp); \
		$$MK >$$LOGFILE 2>&1 & MK_PID=$$!; \
		echo -n "Compiling"; \
		while kill -0 $$MK_PID 2>/dev/null; do \
		  for i in {1..3}; do \
		    echo -n "."; \
		    sleep 0.5; \
		  done; \
		  echo -ne "\rCompiling   \rCompiling"; \
		done; \
		wait $$MK_PID; \
		STATUS=$$?; \
		if [ $$STATUS -ne 0 ]; then \
		  echo -e "\nCompilation failed. See the output below:"; \
		  cat $$LOGFILE; \
		else \
		  echo -e "\rCompiling finished.    "; \
		fi; \
		rm -f $$LOGFILE; \
		'; \
	fi

$(LIBFT): $(LIBFT_SRC)/*.c
	make -C $(LIBFT_SRC)

clean:
	make -C $(LIBFT_SRC) clean
	rm -fr $(obj)

fclean: clean
	make -C $(LIBFT_SRC) fclean
	rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean re compile


