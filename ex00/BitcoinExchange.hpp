#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <map>
# include <ctime>
# include <algorithm>
# include <exception>
# include <iomanip>

std::map<std::string, std::string>	loadData( void );
void								convert(std::map<std::string, std::string> &dataBase,
										std::ifstream &inputFile);

#endif