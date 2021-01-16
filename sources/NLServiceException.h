//
// Created by dimich on 03/09/15.
//

#ifndef NOOLIGHTRX64_NLSERVICEEXCEPTION_H
#define NOOLIGHTRX64_NLSERVICEEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class NLServiceException : public exception {
private:
    string mReason;

public:
    NLServiceException(string reason) : mReason(reason) {

    }

    virtual ~NLServiceException() throw() {}
    virtual const char *what() const throw() {
        return mReason.c_str();
    }
};
#endif //NOOLIGHTRX64_NLSERVICEEXCEPTION_H
