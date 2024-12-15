#include <PMergeMe.hpp>

int main(int ac, char **args) {
	if (ac < 2) {
		std::cerr << "Error: Program usage './PMergeMe args...'" << std::endl;
		return (1);
	}

	for (int i = 1; i < ac && args && args[i]; i++) {
		if (!isPositiveInteger(args[i])) {
			std::cerr << "Error: " << args[i] << " is not a positive integer" << std::endl;
			return (1);
		}
	}

	std::vector<int> vec(ac - 1);
	std::deque<int> deq(ac - 1);
	clock_t start = clock();

	for (int i = 1; i < ac; ++i) {
		int num = std::atoi(args[i]);
		vec[i - 1] = num;
	}

	if (args && checkDuplicates(vec)) {
		std::cerr << "Error: duplicated numbers" << std::endl;
		return (1);
	}

	if (isSorted(vec)) {
		std::cerr << "Error: sequence is already sorted" << std::endl;
		return (1);
	}

	printSequence("Before:\t", vec);
	mergeInsertionSort(vec, 0, vec.size() - 1);
	clock_t end = clock();
	double vecTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	printSequence("After:\t", vec);
	std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " 
				<< std::fixed << std::setprecision(6) << vecTime << " us" << std::endl;

	start = clock();
	for (int i = 1; i < ac; ++i) {
		int num = std::atoi(args[i]);
		deq[i - 1] = num;
	}
	mergeInsertionSort(deq, 0, deq.size() - 1);
	end = clock();
	double dequeTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << deq.size() << " elements with std::deque  : " 
			<< std::fixed << std::setprecision(6) << dequeTime << " us" << std::endl;
    return (0);
}
