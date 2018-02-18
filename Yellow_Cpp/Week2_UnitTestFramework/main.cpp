#include <iostream>
#include <sstream>
#include <exception>
#include <string>
#include <set>
#include <map>

bool TestedFunction() {
	// some function to be tested
	return true;
}

template <class T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
std::ostream& operator << (std::ostream& os, const std::map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template <typename Left, typename Right>
void assert_equal(const Left& expected, const Right& actual, const std::string& hint = {}) {
	if (expected != actual)
	{
		std::ostringstream ss;
		ss << "expected " << expected << " != actual " << actual;
		if (!hint.empty())
			ss << " (" << hint << ")";
		throw std::runtime_error(ss.str());
	}
}

class TestRunner {
public:
	template <typename FuncType>
	void RunTest(FuncType func, const std::string& test_name = {}) {
		try {
			func();
			std::cerr << test_name << " is OK" << std::endl;
		} catch (std::runtime_error ex) {
			std::cerr << test_name << " is FAIL: " << ex.what() << std::endl;
			++failed_count;
		} catch (...) {
			std::cerr << test_name << " is FAIL. Unknown expection" << std::endl;
			++failed_count;
		}
	}

	~TestRunner() {
		if (failed_count > 0) {
			std::cerr << failed_count << " unit tests failed. Exit" << std::endl;
			exit(1);
		}
	}
private:
	int failed_count = 0;
};

void test1() {
	assert_equal(true, TestedFunction());
}

void test2() {
	assert_equal(false, TestedFunction());
}


void RunAllTests() {
	TestRunner runner;
	runner.RunTest(test1, "test1");
	runner.RunTest(test2, "test2");
}

int main() {
	RunAllTests();
	return 0;
}