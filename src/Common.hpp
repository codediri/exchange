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

namespace exch
{
    enum class MenuType
    {
        UNKNOWN,
        ADD_NEW_ORDER,
        DISPLAY_ORDERS,
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
        EXPIRED,
        UNKNOWN
    };
    
    std::string GetOrderTypeStr( OrderType oType )
    {
        std::string sOType = "UNKNOWN";
        
        switch( oType )
        {
            case OrderType::NEW:
                sOType = "NEW";
                break;
            case OrderType::WORKING:
                sOType = "WORKING";
                break;
            case OrderType::PARTIAL_FILLED:
                sOType = "PARTIAL_FILLED";
                break;
            case OrderType::FILLED:
                sOType = "FILLED";
                break;
            case OrderType::EXPIRED:
                sOType = "EXPIRED";
                break;
        }
        
        return sOType;
    }
    
    std::string CreateId( int p_counter )
    {
        return std::to_string( (long) time(NULL) ) + std::to_string(p_counter);
    }
}

#endif // _Common_H_
