#pragma once
#include <iostream>
#include <sstream>
#include <exception>
#include <string>
#include <set>
#include <map>
#include <vector>


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

template <class T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) {
	os << "[";
	bool first = true;
	for (const auto& item : v) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << item;
	}
	return os << "]";
}


template <typename Left, typename Right>
void AssertEqual(const Left& expected, const Right& actual, const std::string& hint = {})
{
	if (expected != actual)
	{
		std::ostringstream ss;
		ss << "expected " << expected << " != actual " << actual;
		if (!hint.empty())
			ss << " (" << hint << ")";
		throw std::runtime_error(ss.str());
	}
}

template <class ClassType, typename ArgType, typename ExceptionType>
void assert_throw(ArgType arg, const std::string& hint = {})
{
	try {
		ClassType ph(arg);
		std::ostringstream ss;
		ss << "Exception was not thrown with arg " << arg;
		throw std::runtime_error(ss.str());
	} catch (ExceptionType ex) {
		// OK
	} catch (...) {
		std::ostringstream ss;
		ss << "Unknown exception was thrown with arg " << arg;
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
