#include "TeamTask.h"


const TasksInfo& TeamTasks::GetPersonTasksInfo(const std::string& person) const {
	return teamTasks.at(person);
}

void TeamTasks::AddNewTask(const std::string& person) {
	++teamTasks[person][TaskStatus::NEW];
}

TaskStatus TeamTasks::next(TaskStatus status) {
	return static_cast<TaskStatus>(static_cast<int>(status) + 1);
}

void TeamTasks::removeZero(TasksInfo& tasks, TaskStatus status) {
	if (tasks[status] <= 0) {
		tasks.erase(status);
	}
}

std::tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(const std::string& person, int task_count) {
	TasksInfo updated, untouched;
	if (teamTasks.count(person) == 0) return std::make_tuple(updated, untouched);
	// Просматриваем задачи разработчика во всех статусах, кроме DONE, т.к. их не нужно обновлять
	// Задачи упорядочены в массиве по статусам: NEW, IN PROGRESS, TESTING, DONE
	TasksInfo& personTasks = teamTasks.at(person);	
	for (auto iter = personTasks.begin(); iter != personTasks.end(); ++iter) {
		TaskStatus status = iter->first;
		int taskCountForStatus = iter->second;		
		if (status == TaskStatus::DONE) break;		
		// Добавляем информацию  об обновленных задачах в массив updated
		int minTaskCount = std::min(taskCountForStatus, task_count);
		TaskStatus nextStatus = next(status);
		updated[nextStatus] = minTaskCount;
		removeZero(updated, nextStatus);
		// Добавляем информацию о старых задачах в массив untouched
		untouched[status] = taskCountForStatus - task_count;
		removeZero(untouched, status);
		// Обновляем количество оставшихся для выполнения задача
		task_count -= minTaskCount;
	}
	// Обновляем информацию в списке задач разработчика по данных из массива updated
	for (auto iter = updated.begin(); iter != updated.end(); ++iter) {
		TaskStatus status = iter->first;
		int count = iter->second;
		personTasks[status] += count;
		TaskStatus prevStatus = static_cast<TaskStatus>(static_cast<int>(status) - 1);
		personTasks[prevStatus] -= count;
		// Если число задач стало равно 0, то нужно убрать запись с таким статусом из массива personTasks
		removeZero(personTasks, prevStatus);
	}
	return std::make_tuple(updated, untouched);
}