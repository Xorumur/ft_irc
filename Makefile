NAME =		ft_irc

CXX =		clang++

CXXFLAGS =	-Wall -Wextra -Werror -std=c++98 -g -fsanitize=address

SRCS =		main.cpp \
			srcs/irc.cpp \
			srcs/server.cpp \
			srcs/utils.cpp \

OBJS =		$(SRCS:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:	
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		re clean fclean all