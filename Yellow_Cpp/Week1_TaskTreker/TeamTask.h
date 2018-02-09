#pragma once

#include <iostream>
#include <tuple>
#include <map>
#include <string>
#include <algorithm>

// ѕеречислимый тип дл€ статуса задачи
enum class TaskStatus {
	NEW,          // нова€
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

// ќбъ€вл€ем тип-синоним дл€ map<TaskStatus, int>,
// позвол€ющего хранить количество задач каждого статуса
using TasksInfo = std::map<TaskStatus, int>;

class TeamTasks {
public:
	// ѕолучить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const std::string& person) const;

	// ƒобавить новую задачу (в статусе NEW) дл€ конкретного разработчитка
	void AddNewTask(const std::string& person);

	// ќбновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(
		const std::string& person, int task_count);

private:
	std::map<std::string, TasksInfo> teamTasks;
	
	// ѕолучить статус следующей в списке TaskStatus задачи
	TaskStatus next(TaskStatus status);

	// ”далить из массива статус и задачи, если кол-во задач не положительное
	void removeZero(TasksInfo& tasks, TaskStatus status);
};


