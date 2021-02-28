#ifndef _CHILD_SERVICE_A_H_
#define _CHILD_SERVICE_A_H_

#include "parent_service.h"

class ChildServiceA : public ParentService
{
 public:
    ChildServiceA();
    ~ChildServiceA();

    virtual int start();

 private:

};


#endif  // _CHILD_SERVICE_A_H_
