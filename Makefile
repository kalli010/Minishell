# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/28 23:04:40 by ayel-mou          #+#    #+#              #
#    Updated: 2024/08/31 05:47:13 by ayel-mou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc

CFLAGS = -Wall -Wextra -Werror -I./includes -I$(LIBFT_SRC) -g #-fsanitize=address -g3


LIBFT_SRC = ./lib/libft/
LIBFT = $(LIBFT_SRC)/libft.a

src = ./utils/Minishell.c \
      ./utils/lparsiiiing.c \
     execute_all/run_execute.c \
     execute_all/get_path.c \
     execute_all/here_doc.c \
     execute_all/helper_fun.c \
     bulutins/ft_env.c \
     bulutins/ft_pwd.c \
	  execute_all/execute_cmd.c \
	  execute_all/redirect.c \
	bulutins/ft_echo.c \
	execute_all/run_builtins.c \
	bulutins/ft_cd.c \
	bonus/check_logical.c \
#
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

