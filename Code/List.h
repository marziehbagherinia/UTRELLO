#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Task;

class List
{
public:
    List(string _list_id);

    void set_list_id(string _list_id);
    void delete_task(string task);
    
    int remaining_task_time();
    int bede();

    bool existance_tasks(string task);

    string add_task(Task* new_task);
    string complete_task(string _task);
    string get_list_id();

    vector<Task*> get_tasks();
    vector<string> get_task_id();
    string bargardon();
    
private:
	string list_id;
    vector<Task*> tasks;
    vector<Task*> remaining_tasks;
    vector<Task*> completed_tasks;
};

#endif