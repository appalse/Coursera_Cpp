#include "date.h"
#include <iomanip>
#include <vector>

using namespace std;

Date::Date(int year, int month, int day) :
	m_year(year),
	m_month(month),
	m_day(day)
{}

Date::Date(const Date& other) :
	m_year(other.Year()),
	m_month(other.Month()),
	m_day(other.Day())
{}


Date ParseDate(istream& is) 
{
	int year, month, day;
	char delim;
	is >> year >> delim >> month >> delim >> day;
	if ((year < 0) || (year > 9999))
		throw logic_error("Year is out of range [0..9999]");
	if ((month < 1) || (month > 12))
		throw logic_error("Month is out of range [1..12]");
	if ((day < 1) || (day > 31))
		throw logic_error("Day is out of range [1..31]");
	return Date(year, month, day);
}

std::ostream& operator<< (std::ostream& os, const Date& date) 
{
	os << setfill('0') << setw(4) << date.Year() << '-';
	os << setw(2) << date.Month() << '-' << setw(2) << date.Day();
	return os;
}

bool operator< (const Date& lhs, const Date& rhs) 
{
	vector<int> left = { lhs.Year(), lhs.Month(), lhs.Day() };
	vector<int> right = { rhs.Year(), rhs.Month(), rhs.Day() };
	return left < right;
}

bool operator<= (const Date& lhs, const Date& rhs) 
{
	return lhs < rhs || lhs == rhs;
}

bool operator> (const Date& lhs, const Date& rhs) 
{
	return rhs < lhs;
}

bool operator>= (const Date& lhs, const Date& rhs) 
{
	return rhs <= lhs;
}

bool operator== (const Date& lhs, const Date& rhs) 
{
	return lhs.Year() == rhs.Year() &&
			lhs.Month() == rhs.Month() &&
			lhs.Day() == rhs.Day();
}

bool operator!= (const Date& lhs, const Date& rhs) 
{
	return !(lhs == rhs);
}

