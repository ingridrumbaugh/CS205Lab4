#include "baseclass.h"


//Initialize the static variable that tracks the number
//of objects created
int BaseClass::idCnt = 0;

BaseClass::BaseClass()
{
    //Uniquely identifying the object
    id = idCnt;

    //Increment the created object count
    idCnt ++;

}
