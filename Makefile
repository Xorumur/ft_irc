NAME =		ircserv

CXX =		clang++

CXXFLAGS =	-Wall -Wextra -Werror -std=c++98 -g -fsanitize=address

SRCS =		main.cpp \
			srcs/irc.cpp \
			srcs/utils.cpp \
			commands/pass.cpp \
			commands/nick.cpp \
			commands/user.cpp \
			commands/mode.cpp \
			commands/join.cpp \
			commands/privmsg.cpp \
			commands/part.cpp \
			commands/topic.cpp \
			commands/oper.cpp \
			commands/kill.cpp \
			commands/kick.cpp \
			commands/names.cpp \

INC = 		includes/Channel.hpp \
			includes/Client.hpp \
			includes/parse.hpp \
			includes/Server.hpp \
			includes/except.hpp \
			includes/irc.hpp \

OBJS =		$(SRCS:.cpp=.o)

all:		$(NAME)

$(NAME):	$(OBJS) 
			@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
			

clean:	
			@rm -rf $(OBJS)

fclean:		clean
			@rm -rf $(NAME)

re:			fclean all

count: 
		wc -l $(SRCS) $(INC)

run :	re
		./ircserv 8888 pass

nc:
		nc -c localhost 8888

.PHONY:		re clean fclean all