// Pretty print for std::vector, std::map, std::pair
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

template <typename Collection>
std::string Join(const Collection& c, char delimiter = ',') {
	std::stringstream ss;
	bool firstValue = true;
	for (const auto& item : c) {
		if (!firstValue) {
			ss << delimiter << ' ';
		}
		firstValue = false;
		ss << item;
	}
	return ss.str();
}

template <typename T>
std::ostream& operator<< (std::ostream& out, std::vector<T> v) {
	return out << '[' << Join(v) << ']';
}

template <typename First, typename Second>
std::ostream& operator<< (std::ostream& out, std::pair<First, Second> p) {
	return out << '(' << p.first << ", " << p.second << ')';
}

template <typename Key, typename Value>
std::ostream& operator<< (std::ostream& out, std::map<Key, Value> m) {
	return out << '{' << Join(m) << '}';
}

int main() {
	std::vector<int> v1 = {1, 2, 3, 4};
	std::vector< std::vector<double> > v2 = { {-1.5, 0.5, 1.5}, {2.1, 3.1, 4.1}, {10, 20} };
	std::map<int, int> m1 = { {1, 10}, {2, 20}, {3, 30} };
	std::map<std::string, std::pair<int, char> > m2 = { 
		{ "Eva", {2017, 'E'} },
		{ "Petya", {2017, 'P'} }
	};

	std::cout << v1 << std::endl;
	std::cout << v2 << std::endl;
	std::cout << m1 << std::endl;
	std::cout << m2 << std::endl;

	system("pause");
	return 0;
}