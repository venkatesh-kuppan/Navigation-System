/* Generated by Together */

#ifndef CGPSSENSOR_H
#define CGPSSENSOR_H
#include "CWayPoint.h"

/**
 * The class objective is to get the current position from the user.
 */
class CGPSSensor {
public:

    /**
     * The default constructor 
     */
    CGPSSensor();

    /**
     * The function expects an input to be provided by the user by manually typing in the co-ordinates.
     * 
     * Arguments:
     * None.
     * 
     * Return:
     * CWayPoint : the object created after taking the inputs from the user. 
     */
    CWayPoint getCurrentPosition();
private:

    /** @link dependency */
    /*# CWayPoint lnkCWayPoint; */
};
#endif //CGPSSENSOR_H
