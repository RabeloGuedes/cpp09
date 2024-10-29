#include <BitcoinExchange.hpp>

int	main( int argc, char **argv ) {
	if (argc != 2) {
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	std::map<std::string, std::string>	dataBase;

	try {
		dataBase = loadData();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	// std::cout << "Data base:" << std::endl;

	// for (std::map<std::string, std::string>::iterator it = dataBase.begin(); it != dataBase.end(); it++)
	// 	std::cout << it->first << ": " << it->second << std::endl;

	std::ifstream	inputFile(argv[1]);
	std::string		line;

	if (!inputFile.is_open()) {
		std::cerr << "Error: Open failed, file: " << argv[1] << std::endl;
		return 1;
	}

	convert(dataBase, inputFile);
	return 0;
}