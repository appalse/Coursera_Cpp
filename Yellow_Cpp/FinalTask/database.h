#pragma once

/*эти файлы должны содержать объ€вление и определение класса Database;*/

/* в классах Database и Node делайте у методов именно те сигнатуры, которые используютс€ в функции main.*/

class Database {
public:
	Database() {}

	void Add(Date data, std::string event);

	void Print(ostream& os);

	int RemoveIf(predicate (condition->Evaluate(date, event)));

	std::vector<string> FindIf(std::function < std::shared_ptr<Node>(const Date& date, const std::string& event) > predicate);

	std::string Last(Date date);
};