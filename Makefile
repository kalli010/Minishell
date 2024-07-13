NAME = Minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes -I$(GNL_SRC) -I$(LIBFT_SRC)

GNL_SRC = ./lib/get_next_line/
GNL = $(GNL_SRC)/get_next_line.a

LIBFT_SRC = ./lib/libft/
LIBFT = $(LIBFT_SRC)/libft.a

src = ./utils/Minishell.c

obj = $(src:.c=.o)

all: $(NAME)

$(NAME): $(obj) $(LIBFT) $(GNL)
	$(CC) $(CFLAGS) $(LIBFT) $(GNL)  -o $(NAME)

$(GNL): $(GNL_SRC)/*.c
	make -C $(GNL_SRC)

$(LIBFT): $(LIBFT_SRC)/*.c
	make -C $(LIBFT_SRC)

clean:
	make -C $(LIBFT_SRC) clean
	make -C $(GNL_SRC) clean
	rm -fr $(obj)

fclean: clean
	make -C $(LIBFT_SRC) fclean
	make -C $(GNL_SRC) fclean
	rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean re
