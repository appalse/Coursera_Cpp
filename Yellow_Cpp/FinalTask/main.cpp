#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "tests.h"

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <exception>
#include <string>

using namespace std;

std::string ParseEvent(std::istream& is) 
{
	string event_str;
	getline(is, event_str);
	while (!event_str.empty() && event_str.front() == ' ')
		event_str.erase(event_str.begin(), event_str.begin() + 1);
	auto it = event_str.find('\"');
	if (it != string::npos)
		throw logic_error("Event contain forbidden character (\"): " + event_str);
	return event_str;
}


int main() 
{
	TestAll();

	Database db;

	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "Add") {
			const auto date = ParseDate(is);
			const auto event = ParseEvent(is);
			db.Add(date, event);
		} else if (command == "Print") {
			db.Print(cout);
		} else if (command == "Del") {
			auto condition = ParseCondition(is); // shared_ptr<Node>
			auto predicate = [condition] (const Date& date, const string& event) {
				return condition->Evaluate(date, event);
			};
			auto count = db.RemoveIf(predicate);
			cout << "Removed " << count << " entries" << endl;
		} else if (command == "Find") {
			auto condition = ParseCondition(is);
			auto predicate = [condition] (const Date& date, const string& event) {
				return condition->Evaluate(date, event);
			};

			const auto entries = db.FindIf(predicate);
			for (const auto& entry : entries) {
				cout << entry << endl;
			}
			cout << "Found " << entries.size() << " entries" << endl;
		} else if (command == "Last") {
			try {
				cout << db.Last(ParseDate(is)) << endl;
			} catch (invalid_argument&) {
				cout << "No entries" << endl;
			}
		} else if (command.empty()) {
			continue;
		} else {
			throw logic_error("Unknown command: " + command);
		}
	}
	system("pause");
	return 0;
}



