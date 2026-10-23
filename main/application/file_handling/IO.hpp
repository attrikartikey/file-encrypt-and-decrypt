#ifndef IO_HPP   //compiled only once. rest are passed by reference
#define IO_HPP

#include <fstream>
#include <string>
#include <iostream>

class IO{
    public:
      IO(const std::string &file_path);  //CONSTRUCTOR
      ~IO();                             //DESTRUCTOR
      std::fstream getFileStream();

    private:
      std::fstream file_stream;
};



#endif