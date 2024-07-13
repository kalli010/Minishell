


NAME = ft_printf.a
HFILE = ft_printf.h

SRC =	ft_printf.c\
	ft_printf_functions.c\

OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
AR = ar rc
RM = rm -f
CC = cc

all : $(NAME)

$(NAME) : $(OBJ) $(HFILE)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
	$(AR) $(NAME) $@

re : fclean all

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

.PHONY : all clean fclean re
