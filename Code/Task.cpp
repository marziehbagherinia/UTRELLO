#include "Task.h"
#include "List.h"
#include "User.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

Task::Task(string _task_id, unsigned int _estimated_Time, unsigned int _priority, string _description)
:estimated_Time(_estimated_Time)
,priority(_priority)
,description(_description)
,task_id(_task_id)
{
}

Task::Task(List* _list, string _task_id, unsigned int _estimated_Time, unsigned int _priority, string _description)
:estimated_Time(_estimated_Time)
,priority(_priority)
,description(_description)
,list(_list)
,task_id(_task_id)
{
}

unsigned int Task::get_estimated_Time()
{
    return estimated_Time;
}

unsigned int Task::get_priority()
{
    return priority;
}

string Task::get_task_id()
{
    return task_id;
}

string Task::get_description()
{
    return description;
}

List* Task::get_list()
{
    return list;
}

string Task::get_list_id()
{
    string list_id = list->get_list_id();
    return list_id;
}
void Task::set_user_id(string _user_id)
{
    User* user = new User(_user_id);
    user_id = user->get_user_id();
}

string Task::get_user_id()
{
    return user_id;
}