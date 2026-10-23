#ifndef TASK_HPP   //compiled only once. rest are passed by reference
#define TASK_HPP

#include<string>
#include<iostream>
#include"../file_handling/IO.hpp"
#include<sstream>

enum class Action{
    ENCRYPT,
    DECRYPT
};

struct Task{
    std::string filePath;
    std::fstream f_stream;
    Action action;

    Task(std::fstream &&stream, Action act, std::string filePath): f_stream(std::move(stream)), filePath(filePath), action(act){}    //&& creates a temp file that is volatile to be assigned / moved forward without creating a new file.

    std::string toString(){
        std::ostringstream oss;
        oss<<filePath<<","<<(action == Action::ENCRYPT? "ENCRYPT": "DECRYPT"); //text.txt ENCRYPT f_stream => "text.txt,ENCRYPT"
        return oss.str();
    }

    static Task fromString(const std::string &taskData){
        std::istringstream iss(taskData);
        std::string filePath;
        std::string actionStr;

        if(std::getline(iss, filePath, ',') && std::getline(iss, actionStr)){
            //test.txt goes to filepath, encrypt goes to action string
            Action action = (actionStr == "ENCRYPT"?Action::ENCRYPT: Action::DECRYPT);
            IO io(filePath);
            std::fstream f_stream = io.getFileStream();

            if(f_stream.is_open()){
                return Task(std::move(f_stream), action, filePath);
            }else{
                throw std::runtime_error("Failed to open file: " + filePath);
            }
        }else{
            throw std::runtime_error("invalid task data format");
        }
    }
};




#endif