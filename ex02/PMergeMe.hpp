#ifndef PMERGERME_HPP
# define PMERGERME_HPP

# include <deque>
# include <vector>
# include <iostream>
# include <string>
# include <iostream>
# include <algorithm>
# include <ctime>
# include <iomanip>
# include <utility>

# ifdef INSERTION_SORT_THRESHOLD
# undef INSERTION_SORT_THRESHOLD
#  define INSERTION_SORT_THRESHOLD 10
# else
#  define INSERTION_SORT_THRESHOLD 10
# endif

bool	isPositiveInteger(std::string arg);
bool	checkDuplicates(std::vector<int> &vec);

void	insertionSort(std::vector<int> &vec, int left, int right);
void	merge(std::vector<int> &vec, int left, int mid, int right);
void	mergeInsertionSort(std::vector<int> &vec, int left, int right);

void	insertionSort(std::deque<int> &deq, int left, int right);
void	merge(std::deque<int> &deq, int left, int mid, int right);
void	mergeInsertionSort(std::deque<int> &deq, int left, int right);


template <typename T>
bool	isSorted(T &container) {
	for (size_t i = 1; i < container.size(); i++) {
		if (container[i] < container[i - 1])
			return (false);
	}
	return (true);
}

template <typename T>
void	printSequence(std::string msg, T &container) {
	std::cout << msg << " ";
	for (size_t i = 0; i < container.size(); i++) {
		std::cout << container[i];
		if (i + 1 < container.size())
			std::cout << " ";
	}
	std::cout << std::endl;
}
#endif
