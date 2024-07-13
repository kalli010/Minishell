NAME = Minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes -I$(GNL_SRC) -I$(LIBFT_SRC)

GNL_SRC = ./lib/get_next_line/
GNL = $(GNL_SRC)/get_next_line.a

LIBFT_SRC = ./lib/libft/
LIBFT = $(GNL_SRC)/libft.a

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
	make -C clean $(GNL_SRC)
	make -C clean $(LIBFT_SRC)
	rm -fr $(obj)

fclean: clean
	make -C fclean $(LIBFT_SRC)
	make -C fclean $(GNL_SRC)
	rm -fr $(NAME)

re: fclean all

.PHONY: all clean fclean re
