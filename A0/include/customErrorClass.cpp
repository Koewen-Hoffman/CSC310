#include <iostream>
#include "customErrorClass.h"

using namespace std;

CustomException::CustomException(void){
    this->errString = "No Error Set";
}

CustomException::CustomException(const string &err){
    this->errString = err;
}

CustomException::CustomException(const char *err){
    this->errString = err;
}