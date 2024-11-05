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

void	calculate(std::stack<std::string> *nums, std::string op, double &res) {
	if (nums->size() < 2) {
		delete nums;
		throw std::runtime_error("Error");
	}
	double		a = 0, b = 0;
	a = std::strtod(nums->top().c_str(), NULL);
	nums->pop();
	b = std::strtod(nums->top().c_str(), NULL);
	nums->pop();

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
}

void	parseRPN(std::string rpn) {
	std::stack<std::string>	*nums = new std::stack<std::string>();
	std::string				token;
	std::string::size_type	pos = 0;
	double					res = std::numeric_limits<double>::max();
	std::stringstream		sstr;

	if (!nums) {
		std::cerr << "Error: memory allocation failed" << std::endl;
		return ;
	}
	while ((pos) != std::string::npos) {
		pos = rpn.find_first_of(" \t\r\v\n\f");
		token = rpn.substr(0, pos);
		rpn.erase(0, pos + 1);
		if (isOnlyWhiteSpace(token) || token.empty())
			continue ;
		else if (isNumber(token) && nums)
			nums->push(token);
		else if (isOperator(token) && nums && nums->size() >= 1) {
			if (res != std::numeric_limits<double>::max()) {
				sstr << static_cast<int>(res);
				nums->push(sstr.str());
				sstr.str("");
			}
			calculate(nums, token, res);
		}
		else {
			delete nums;
			throw std::runtime_error("Error");
		}
	}
	if (nums->size() != 0) {
		delete nums;
		throw std::runtime_error("Error");
	}
	else
		std::cout << res << std::endl;
	delete nums;
}

