NAME = minishell
CC = cc

CFLAGS = -Wall -Wextra -Werror -I./includes -I$(LIBFT_SRC) -g #-fsanitize=address -g3

LIBFT_SRC = ./lib/libft
LIBFT = $(LIBFT_SRC)/libft.a

DIRS = bonus  bulutins  executor  signal  utils libft
OBJDIR = bin

src = $(foreach dir, $(DIRS), $(wildcard $(dir)/*.c))
obj = $(patsubst %.c, $(OBJDIR)/%.o, $(notdir $(src)))

vpath %.c $(DIRS)


all: $(NAME)

$(NAME): $(obj) $(LIBFT)
	$(CC) $(CFLAGS) $(obj) $(LIBFT) -o $(NAME) -lreadline

#bin/check_logical.o : bonus/check_logical.c | $(OBJDIR)
#	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR)/%.o : %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<
    
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

$(OBJDIR) :
	mkdir -p $(OBJDIR)

clean:
	make -C $(LIBFT_SRC) clean
	rm -fr $(OBJDIR)

fclean: clean
	make -C $(LIBFT_SRC) fclean
	rm -fr $(NAME)

re: fclean all

l: all clean

.PHONY: all clean fclean re compile
.SECONDARY:
