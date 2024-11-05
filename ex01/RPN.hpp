#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <string>
# include <exception>
# include <limits>
# include <cstdlib>
# include <sstream>
# include <cmath>

typedef	struct sStacks {
	std::stack<std::string>	*nums;
	std::stack<std::string>	*operators;
}	tStacks;

void	parseRPN(std::string rpn);

#endif