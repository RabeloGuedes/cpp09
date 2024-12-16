CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -g -I. -std=c++98

NAME = btc
SRCS = BitcoinExchange.cpp
OBJS = $(SRCS:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJS) main.cpp
	$(CXX) $(CXXFLAGS) $(OBJS) main.cpp -o $(NAME)

$(OBJS): $(SRCS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) *.dSYM

fclean: clean
	rm -f $(NAME)

re: fclean all
