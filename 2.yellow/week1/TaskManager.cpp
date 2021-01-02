#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

enum class TaskStatus {
    NEW,
    IN_PROGRESS,
    TESTING,
    DONE
};


using TasksInfo = map<TaskStatus, int>;

void PrintTasksInfo(const TasksInfo& tasks_info) {
    if (tasks_info.count(TaskStatus::NEW)) {
        std::cout << "NEW: " << tasks_info.at(TaskStatus::NEW) << " ";
    }
    if (tasks_info.count(TaskStatus::IN_PROGRESS)) {
        std::cout << "IN_PROGRESS: " << tasks_info.at(TaskStatus::IN_PROGRESS) << " ";
    }
    if (tasks_info.count(TaskStatus::TESTING)) {
        std::cout << "TESTING: " << tasks_info.at(TaskStatus::TESTING) << " ";
    }
    if (tasks_info.count(TaskStatus::DONE)) {
        std::cout << "DONE: " << tasks_info.at(TaskStatus::DONE) << " ";
    }
}

void PrintTasksInfo(const TasksInfo& updated_tasks, const TasksInfo& untouched_tasks) {
    std::cout << "Updated: [";
    PrintTasksInfo(updated_tasks);
    std::cout << "] ";

    std::cout << "Untouched: [";
    PrintTasksInfo(untouched_tasks);
    std::cout << "] ";

    std::cout << std::endl;
}

TaskStatus Next(TaskStatus task_status) {
    return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
}

class TeamTasks {
 public:
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return PersonsTask.at(person);
    }

    void AddNewTask(const string& person) {
        ++PersonsTask[person][TaskStatus::NEW];
    }

    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
        vector<TaskStatus> VStatus = { TaskStatus::NEW,
                                       TaskStatus::IN_PROGRESS,
                                       TaskStatus::TESTING,
                                       TaskStatus::DONE};

        TasksInfo updated_tasks = BuildUpdatedTasks(person, task_count);
        TasksInfo untouched_tasks;

        for (const auto& status : VStatus) {
            if (updated_tasks.count(status))
                PersonsTask[person][status] += updated_tasks[status];

            if (updated_tasks.count(Next(status)))
                PersonsTask[person][status] -= updated_tasks[Next(status)];

            if (PersonsTask[person].count(status) && PersonsTask[person][status] == 0)
                PersonsTask[person].erase(status);
        }

        untouched_tasks = BuildUntouchedTasks(person, updated_tasks);

        return tie(updated_tasks, untouched_tasks);
    }

 private:
    TasksInfo BuildUntouchedTasks(const string& person, TasksInfo& updated_tasks) {
        TasksInfo untouched_tasks;

        for (const auto& [status, amount] : PersonsTask[person]) {
            if (status != TaskStatus::DONE) {
                if (updated_tasks.count(status))
                    untouched_tasks[status] = PersonsTask[person][status] - updated_tasks[status];
                else
                    untouched_tasks[status] = PersonsTask[person][status];
            }

            if (untouched_tasks.count(status) && untouched_tasks.at(status) == 0)
                untouched_tasks.erase(status);
        }
        return untouched_tasks;
    }
    TasksInfo BuildUpdatedTasks(const string& person, int task_count) {
        TasksInfo updated_tasks;

        for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = Next(status)) {
            if (PersonsTask[person].count(status)) {
                if (task_count > 0) {
                    updated_tasks[Next(status)] = min(task_count, PersonsTask[person].at(status));
                    task_count -= updated_tasks[Next(status)];
                } else {
                    break;
                }
            }
        }

        return updated_tasks;
    }


 private:
    map<string, TasksInfo> PersonsTask;
};


int main() {
    TeamTasks tasks;
    TasksInfo updated_tasks;
    TasksInfo untouched_tasks;

    /* TEST 1 */

    std::cout << "Alice" << std::endl;

    for (auto i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
    PrintTasksInfo(updated_tasks, untouched_tasks);

    for (auto i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 2);
    PrintTasksInfo(updated_tasks, untouched_tasks);

    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
    PrintTasksInfo(updated_tasks, untouched_tasks);

    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    std::cout << std::endl;

    return 0;
}

// ПРИМЕР ЧУЖОГО КОДА:

/*
#include <algorithm>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

// Выделим в отдельную функцию получение следующего по приоритету типа задачи
// Функция налагает требование на входной параметр: он не должен быть равен DONE
// При этом task_status явно не сравнивается с DONE, что позволяет
// сделать эту функцию максимально эффективной
TaskStatus Next(TaskStatus task_status) {
  return static_cast<TaskStatus>(static_cast<int>(task_status) + 1);
}

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
 public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const;

  // Добавить новую задачу (в статусе NEW) для конкретного разработчика
  void AddNewTask(const string& person);

  // Обновить статусы по данному количеству задач конкретного разработчика
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count);

 private:
  map<string, TasksInfo> person_tasks_;
};


const TasksInfo& TeamTasks::GetPersonTasksInfo(const string& person) const {
  return person_tasks_.at(person);
}

void TeamTasks::AddNewTask(const string& person) {
  ++person_tasks_[person][TaskStatus::NEW];
}

// Функция для удаления нулей из словаря
void RemoveZeros(TasksInfo& tasks_info) {
  // Соберём те статусы, которые нужно убрать из словаря
  vector<TaskStatus> statuses_to_remove;
  for (const auto& task_item : tasks_info) {
    if (task_item.second == 0) {
      statuses_to_remove.push_back(task_item.first);
    }
  }
  for (const TaskStatus status : statuses_to_remove) {
    tasks_info.erase(status);
  }
}


tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(
    const string& person, int task_count) {
  TasksInfo updated_tasks, untouched_tasks;

  // Здесь и далее мы будем пользоваться тем фактом, что в std::map оператор []
  // в случае отсутствия ключа инициализирует значение по умолчанию,
  // если это возможно.
  // std::map::operator[] ->
  // http://ru.cppreference.com/w/cpp/container/map/operator_at
  TasksInfo& tasks = person_tasks_[person];

  for (TaskStatus status = TaskStatus::NEW;
       status != TaskStatus::DONE;
       status = Next(status)) {
    // Считаем обновлённые
    updated_tasks[Next(status)] = min(task_count, tasks[status]);
    // Считаем, сколько осталось обновить
    task_count -= updated_tasks[Next(status)];
  }

  // Обновляем статус текущих задач в соответствии с информацией об обновлённых
  // и находим количество нетронутых
  for (TaskStatus status = TaskStatus::NEW;
       status != TaskStatus::DONE;
       status = Next(status)) {
    untouched_tasks[status] = tasks[status] - updated_tasks[Next(status)];
    tasks[status] += updated_tasks[status] - updated_tasks[Next(status)];
  }
  // По условию, DONE задачи не нужно возвращать в не обновлённых задачах
  tasks[TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];

  // По условию в словарях не должно быть нулей
  RemoveZeros(updated_tasks);
  RemoveZeros(untouched_tasks);
  RemoveZeros(person_tasks_.at(person));

  return {updated_tasks, untouched_tasks};

}
*/
