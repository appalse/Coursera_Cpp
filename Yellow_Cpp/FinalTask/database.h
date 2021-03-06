#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <functional>
#include "date.h"

class Database {
public:
	Database() {}

	void Add(const Date& date, const std::string& event);

	void Print(std::ostream& os) const;

	int RemoveIf(std::function<bool(const Date&, const std::string&)> condition);

	std::vector<std::string> FindIf(std::function<bool(const Date&, const std::string&)> condition) const;

	std::string Last(const Date& date);

private:
	std::map<Date, std::pair<  std::unordered_set<std::string>, std::map<unsigned, std::string>  >  > m_db;
};