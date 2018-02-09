#pragma once

#include <iostream>
#include <tuple>
#include <map>
#include <string>
#include <algorithm>

// Перечислимый тип для статуса задачи
enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = std::map<TaskStatus, int>;

class TeamTasks {
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const std::string& person) const;

	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const std::string& person);

	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(
		const std::string& person, int task_count);

private:
	std::map<std::string, TasksInfo> teamTasks;
	
	// Получить статус следующей в списке TaskStatus задачи
	TaskStatus next(TaskStatus status);

	// Удалить из массива статус и задачи, если кол-во задач не положительное
	void removeZero(TasksInfo& tasks, TaskStatus status);
};


