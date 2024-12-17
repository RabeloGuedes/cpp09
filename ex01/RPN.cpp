#include <RPN.hpp>

bool	isOnlyWhiteSpace(std::string token) {
	for (size_t i = 0; i < token.size(); i++) {
		if (!isspace(token[i]))
			return (false);
	}
	return (true);
}

bool	isOperator(std::string op) {
	return (op.size() == 1 && (op == "+" || op == "-" || op == "*" || op == "/"));
}

bool	isNumber(std::string num) {
	if (num[0] == '+' || num[0] == '-')
		num = num.substr(1);
	if (!num.length())
		return (false);
	for (size_t i = 0; i < num.size(); i++) {
		if (!isdigit(num[i]))
			return (false);
	}
	return (true);
}

void	calculate(std::stack<std::string> &nums, std::string op) {
	if (nums.size() < 2)
		throw std::runtime_error("Error");
	double		a = 0, b = 0, res = 0;
	b = std::strtod(nums.top().c_str(), NULL);
	nums.pop();
	a = std::strtod(nums.top().c_str(), NULL);
	nums.pop();

	if (op == "+")
		res = a + b;
	else if (op == "-")
		res = a - b;
	else if (op == "/")
		res = a / b;
	else if (op == "*")
		res = a * b;
	if (std::isinf(res))
		res = 0;
	else
		res = static_cast<int>(res);
	std::stringstream t;
	std::string	s;

	t << static_cast<int>(res);
	t >> s;
	nums.push(s);
}

void	parseRPN(std::string rpn) {
	std::stack<std::string>	nums = std::stack<std::string>();
	std::string				token;
	std::string::size_type	pos = 0;
	std::stringstream		sstr;

	while ((pos) != std::string::npos) {
		pos = rpn.find_first_of(" \t\r\v\n\f");
		token = rpn.substr(0, pos);
		rpn.erase(0, pos + 1);
		if (isOnlyWhiteSpace(token) || token.empty())
			continue ;
		else if (isNumber(token))
			nums.push(token);
		else if (isOperator(token) && nums.size() >= 1) {
			calculate(nums, token);
		}
		else
			throw std::runtime_error("Error");
	}
	if (nums.size() != 1)
		throw std::runtime_error("Error");
	else
		std::cout << nums.top() << std::endl;
}

