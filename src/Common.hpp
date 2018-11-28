/******************************************************************************
 *
 * Title:           Common Class
 *
 * Description:     Common Main Program
 *
 * Author:          Arman (https://github.com/codediri)
 *
 ******************************************************************************
 */
 
#ifndef _Common_H_
#define _Common_H_

#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#define _ARRAY_MAX_SIXE_ 100

enum class MenuType
{
    UNKNOWN,
    ADD_NEW_ORDER,
    EXIT,
    BACK_TO_PREV,
    SET_FAILURE,
    SET_MATCHING
};

enum class OrderType
{
    NEW,
    WORKING,
    PARTIAL_FILLED,
    FILLED,
    EXPIRED
};

#endif // _Common_H_
