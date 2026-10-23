// encription key
#include<iostream>
#include<string>
#include<fstream>
#include"IO.hpp"
#include<sstream>

class ReadEnv{
    public:
      std::string getenv(){
        std::string env_path = ".env";
        IO io(env_path);   //open file fstream
        std::fstream f_stream = io.getFileStream();
        std::stringstream buffer;
        buffer<<f_stream.rdbuf();  //returns filestream from buffer
        std::string content = buffer.str();
        return content;
      }
};

