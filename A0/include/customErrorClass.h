#ifndef __CUSTOM_ERROR_CLASS_H__
#define __CUSTOM_ERROR_CLASS_H__

#include <exception>
#include <string>

using namespace std;

class CustomException : public exception {
    public:
        CustomException(void);
        CustomException(const char*);
        CustomException(const string&);
        virtual const string what(){
            return this->errString;
        }
    private:
        string errString;
};

#endif