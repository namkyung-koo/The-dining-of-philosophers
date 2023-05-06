NAME = philo_bonus
CFLAGS = -Wall -Wextra -Werror -MMD -MP
RM = rm -rf
SRCS = main_bonus.c philo_init_bonus.c philo_act_bonus.c philo_routine_bonus.c philo_utils_bonus.c ft_utils_bonus.c
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