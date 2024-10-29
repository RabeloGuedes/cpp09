#include <BitcoinExchange.hpp>

static std::string	trim(std::string &str) {
	str.erase(0, str.find_first_not_of(" \t\r\n\v\f"));
	str.erase(str.find_last_not_of(" \t\r\n\v\f") + 1);
	return str;
}

static void	split(std::string *data, std::string &line, std::string delimit) {
	std::size_t	pos = 0;
	std::size_t	next = 0;
	int			i = 0;

	while ((next = line.find(delimit, pos)) != std::string::npos) {
		if (i == 2)
			break ;
		data[i++] = line.substr(pos, next - pos);
		pos = next + delimit.length();
	}
	if (i != 1)
		throw std::runtime_error("Error: bad input => " + line);
	data[i] = line.substr(pos);
}

std::map<std::string, std::string>	loadData( void ) {
	std::map<std::string, std::string>	dataBase;
	std::ifstream						dataBaseFile("data.csv");
	std::string							line;
	std::string							data[2];

	if (!dataBaseFile.is_open())
		throw std::runtime_error("Error: Open failed, file: data.csv");

	std::getline(dataBaseFile, line);
	split(data, line, ",");
	if (trim(data[0]) != "date" || trim(data[1]) != "exchange_rate")
		throw std::runtime_error("Error: Invalid header in database format, it must be 'date,exchange_rate'.");
	while (std::getline(dataBaseFile, line)) {
		std::stringstream	streamedLine(line);
		std::string			key;
		std::string				value;

		if (std::count(line.begin(), line.end(), ',') != 1)
			throw std::runtime_error("Error: Invalid data format");
		if (std::getline(streamedLine, key, ',') && streamedLine >> value) {
			key = trim(key);
			dataBase[key] = value;
		}
	}

	return dataBase;
}

static bool isDateValid(std::string &date) {
    std::istringstream streamedDate(date);
    int year, month, day;
    char delimiter1, delimiter2;

    if (streamedDate >> year >> delimiter1 >> month >> delimiter2 >> day) {
        if (delimiter1 == '-' && delimiter2 == '-' &&
            year >= 1900 && year <= 9999 &&
            month >= 1 && month <= 12 &&
            day >= 1 && day <= 31) {
            std::tm time = {};
            time.tm_year = year - 1900;
            time.tm_mon = month - 1;
            time.tm_mday = day;
            std::mktime(&time);
			if ((year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
				&& month == 2 && day > 29)
					return false;
            if (time.tm_year == year - 1900 && time.tm_mon == month - 1 && time.tm_mday == day) {
                return true;
            }
        }
    }
    return false;
}

static bool	isFloat(std::string &amount) {
	std::string::const_iterator	it = amount.begin();

	if (amount[0] == '-' || amount[0] == '+')
		++it;
	while (it != amount.end() && std::isdigit(*it))
		++it;
	if (it != amount.end() && *it == '.')
		++it;
	while (it != amount.end() && std::isdigit(*it))
		++it;
	return !amount.empty() && it == amount.end();
}

static void	checkDateAndAmount(std::string &date, std::string &amount) {
	if (!isDateValid(date))
		throw std::runtime_error("Error: Invalid date format => " + date);
	if (!isFloat(amount))
		throw std::runtime_error("Error: Invalid amount format => " + amount);
	
	float	amountFloat = std::stof(amount);
	if (amountFloat < 0)
		throw std::runtime_error("Error: not a positive number.");
	else if (amountFloat > 1000)
		throw std::runtime_error("Error: too large number.");
}

static void	calculateBitCoinValue(std::map<std::string, std::string> &dataBase, std::string &date, std::string &amount) {
	std::map<std::string, std::string>::iterator	it;
	std::string	exchangeRate = dataBase[date];

	if (exchangeRate.empty()) {
		it = dataBase.lower_bound(date);
		if (it == dataBase.begin())
			exchangeRate = "0";
		else
			--it;
		exchangeRate = it->second;
	}
	float	amountFloat = std::strtof(amount.c_str(), NULL);
	float	bitCoinValue = amountFloat * std::strtof(exchangeRate.c_str(), NULL);
	std::cout << date << " => " << amountFloat << " = " << bitCoinValue << std::endl;
}

void	convert(std::map<std::string, std::string> &dataBase, std::ifstream &inputFile) {
	std::string	line;

	std::getline(inputFile, line);
	if (line != "date | value") {
		std::cerr << "Error: Invalid header format, it must be 'date | value'." << std::endl;
		return;
	}

	while (std::getline(inputFile, line)) {
		std::string			data[2];
		std::stringstream	streamedLine(line);
		std::string			date;
		std::string			amount;

		try {
			split(data, line, "|");
			date = trim(data[0]);
			amount = trim(data[1]);
			checkDateAndAmount(date, amount);
			calculateBitCoinValue(dataBase, date, amount);
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
			continue;
		}
	}
}