NAME = test
SCS = main.cpp

all: $(NAME) 

$(NAME):
	c++ -Wall -Wextra -Werror -std=c++98 $(SCS) -o $(NAME)
clean:
	rm $(NAME)
fclean:	clean

re: fclean all