NAME   = libftprintf.a

CC     = gcc
RM     = rm -f

AR     = ar rcs
CFLAGS = -Wall -Wextra -Werror

SRCS   = ft_printf.c  ft_printf_darg.c

OBJS   = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
