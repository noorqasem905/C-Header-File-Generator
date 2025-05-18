CC = cc
CFLAGS = -g
NAME = header_generator

SRCS = generated_headers.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft
HIDE = $(if $(set),, @)
HIDED = $(if $(DIR),, --no-print-directory)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c "$<" -o "$@"

$(NAME): $(OBJS) $(LIBFT)
	$(HIDE)make $(HIDED) -C "libft/printf"
	$(HIDE)make $(HIDED) -C "libft"
	$(HIDE)make $(HIDED) -C "libft" bonus
	$(HIDE)$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L"libft/printf" -lftprintf -L"libft" -lft -g

clean:
	$(HIDE)make $(HIDED) -C "libft/printf" clean
	$(HIDE)make $(HIDED) -C "libft" clean
	$(HIDE)rm -f $(OBJS)	
fclean:
	$(HIDE)make $(HIDED) -C "libft/printf" fclean
	$(HIDE)make $(HIDED) -C "libft" fclean
	$(HIDE)rm -f $(OBJS)
	$(HIDE)rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re