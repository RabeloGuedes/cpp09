#include <PMergeMe.hpp>

// Parsing functions //

bool	isPositiveInteger(std::string arg) {
	for (size_t i = 0; i < arg.size(); i++) {
		if (!std::isdigit(arg[i]))
			return (false);
	}
    return (arg.length() < 11 && std::strtol(arg.c_str(), NULL, 10) > 0);
}

bool	checkDuplicates(std::vector<int> &vec) {
	std::vector<int> tmp = vec;
	std::sort(tmp.begin(), tmp.end());
	for (size_t i = 1; i < tmp.size(); i++) {
		if (tmp[i] == tmp[i - 1])
			return (true);
	}
	return (false);
}

// Parsing functions //

// MergeInsertionSort algorithm //

void insertionSort(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1);
    std::vector<int> R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; ++i)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeInsertionSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        if (right - left + 1 <= INSERTION_SORT_THRESHOLD) {
            insertionSort(arr, left, right);
        } else {
            int mid = left + (right - left) / 2;
            mergeInsertionSort(arr, left, mid);
            mergeInsertionSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
}

void insertionSort(std::deque<int>& deq, int left, int right) {
	for (int i = left + 1; i <= right; ++i) {
		int key = deq[i];
		int j = i - 1;
		while (j >= left && deq[j] > key) {
			deq[j + 1] = deq[j];
			--j;
		}
		deq[j + 1] = key;
	}
}

void merge(std::deque<int>& deq, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	std::deque<int> L(n1);
	std::deque<int> R(n2);

	for (int i = 0; i < n1; ++i)
		L[i] = deq[left + i];
	for (int i = 0; i < n2; ++i)
		R[i] = deq[mid + 1 + i];

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			deq[k] = L[i];
			++i;
		} else {
			deq[k] = R[j];
			++j;
		}
		++k;
	}

	while (i < n1) {
		deq[k] = L[i];
		++i;
		++k;
	}

	while (j < n2) {
		deq[k] = R[j];
		++j;
		++k;
	}
}

void mergeInsertionSort(std::deque<int>& deq, int left, int right) {
	if (left < right) {
		if (right - left + 1 <= INSERTION_SORT_THRESHOLD) {
			insertionSort(deq, left, right);
		} else {
			int mid = left + (right - left) / 2;
			mergeInsertionSort(deq, left, mid);
			mergeInsertionSort(deq, mid + 1, right);
			merge(deq, left, mid, right);
		}
	}
}

// MergeInsertionSort algorithm //