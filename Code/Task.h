#ifndef TASK_H_
#define TASK_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class List;

class Task
{
public:
    
    Task(string _task_id, unsigned int _estimated_Time, unsigned int _priority, string _description);
    Task(List* _list, string _task_id, unsigned int _estimated_Time, unsigned int _priority, string _description);
    
    List* get_list();

    string get_list_id();
    string get_description();
    string get_task_id();
    string get_user_id();

    unsigned int get_estimated_Time();
    unsigned int get_priority();   
    
    void set_user_id(string _user_id);

private:
    string task_id;
    string user_id;
    string description;
    unsigned int estimated_Time;
    unsigned int priority;
    List* list;
    
};

#endif