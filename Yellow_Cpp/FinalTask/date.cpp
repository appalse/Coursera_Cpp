#include <iostream>
#include <string>
#include <iomanip>
#include "date.h"

using namespace std;

Date ParseDate(istream& is)
{
	int year, month, day;
	char delim;
	is >> year >> delim >> month >> delim >> day;
	return Date(year, month, day);
}

std::ostream& operator<< (std::ostream& os, const Date& date)
{
	os << setfill('0') << setw(4) << date.Year() << '-';
	os << setw(2) << date.Month() << '-' << setw(2) << date.Day() << endl;
	return os;
}

Date::Date(int year, int month, int day) :
	m_year(year),
	m_month(month),
	m_day(day)
{}