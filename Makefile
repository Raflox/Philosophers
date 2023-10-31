################################################################################
#                                    CONFIGS                                   #
################################################################################

NAME     := philos
CC       := cc
CFLAGS    := -Wall -Wextra -Werror -pthread -g -fsanitize=thread

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=		main.c 		\
					utils.c		\
					time.c		\
					data.c		\
					checkers.c	\
					error.c		\
					logging.c	\
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f


all:		${NAME}

$(NAME): $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "$(GREEN)Successfully built --> $(YELLOW)$(NAME)$(DEFAULT)"


clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re