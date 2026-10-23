#include <iostream>
#include <fstream>
#include "IO.hpp"

IO::IO(const std::string &file_path){  //constructor of IO.HPP
    file_stream.open(file_path, std::ios::in | std::ios::out | std::ios::binary); // file is stored in the private var of IO after reading, (input, output, read in binary)
    if(!file_stream.is_open()){
        std::cout <<"unable to open file: "<<file_path<<std::endl;       //prompt if file is not opened
    }
}

std::fstream IO::getFileStream(){
    return std::move(file_stream); // return filestream owned by class
}

IO::~IO(){
    if(file_stream.is_open()){
        file_stream.close();         // if io object is going out of memory => close the open file
    }
}