#pragma once

#include <iostream>

class Date 
{
public:
	Date(int year, int month, int day);
	Date(const Date& other);

	int Year() const { return m_year; }
	int Month() const { return m_month; }
	int Day() const { return m_day; }

private:
	const int m_year;
	const int m_month;
	const int m_day;
};

Date ParseDate(std::istream& is);

std::ostream& operator<< (std::ostream& os, const Date& date);

bool operator< (const Date& lhs, const Date& rhs);
bool operator<= (const Date& lhs, const Date& rhs);
bool operator> (const Date& lhs, const Date& rhs);
bool operator>= (const Date& lhs, const Date& rhs);
bool operator== (const Date& lhs, const Date& rhs);
bool operator!= (const Date& lhs, const Date& rhs);