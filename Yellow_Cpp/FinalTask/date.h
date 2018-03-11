#pragma once

/*должны содержать объ€влени€ и определени€ класса Date, 
функции ParseDate и оператора вывода в поток дл€ класса Date;*/

Date ParseDate(std::istream& is);

std::ostream& operator<< (std::ostream& os, const Date& date);

class Date {
public:
	Date(int year, int month, int day);

	int Year() const { return m_year; }
	int Month() const { return m_month; }
	int Day() const { return m_day; }

private:
	const int m_year;
	const int m_month;
	const int m_day;
};
