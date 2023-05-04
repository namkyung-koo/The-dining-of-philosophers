NAME = philo
CFLAGS = -Wall -Wextra -Werror -MMD -MP
RM = rm -rf
SRCS = philo.c simulation.c ft_utils.c utils.c
OBJS = $(addprefix $(DIR)/, $(SRCS:.c=.o))
DEPS = $(addprefix $(DIR)/, $(SRCS:.c=.d))
DIR = objs

all : $(NAME)

$(NAME) : $(DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(DIR) :
	@mkdir $@

$(DIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(DIR) $(OBJS) $(DEPS)

fclean : clean
	$(RM) $(DIR) $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re

-include $(DEPS)