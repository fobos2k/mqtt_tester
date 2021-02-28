#ifndef _CHILD_SERVICE_B_H_
#define _CHILD_SERVICE_B_H_

#include "parent_service.h"

class ChildServiceB : public ParentService
{
 public:
    ChildServiceB();
    ~ChildServiceB();

    virtual int start();

 private:

};


#endif  // _CHILD_SERVICE_B_H_
