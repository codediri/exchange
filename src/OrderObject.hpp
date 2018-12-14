/******************************************************************************
 *
 * Title:           OrderObject Class
 *
 * Description:     OrderObject Main Program
 *
 * Author:          Arman (https://github.com/codediri)
 *
 ******************************************************************************
 */
 
#ifndef _OrderObject_H_
#define _OrderObject_H_

#include "FileHandler.hpp"
#include "Order.hpp"
#include <sstream>

class OrderObject :
    public FileHandler
{
    private:
        std::vector<OrderShd> mOrderList;
		
    protected:		
        
    public:
        OrderObject( const std::string& p_orderFile ) :
            FileHandler( p_orderFile )
        {
            
        }
            
        ~OrderObject() 
        {
            mOrderList.clear();
        }
        
        bool AddNewOrder( const std::string& p_orderStr, OrderShd& p_order )
        {            
            if( !Parse( p_orderStr, p_order ) ) return false;
            
            if( !Validate( p_order ) ) return false;
            
            mOrderList.push_back( std::move(p_order) );
            
            p_order = mOrderList[ mOrderList.size() - 1 ];
            
            return true;
        }
        
        bool Parse( const std::string& p_orderStr, OrderShd& p_order )
        {
            std::istringstream _streamLine( p_orderStr );
            std::vector<std::string> stringVec;
            
            while (_streamLine)
			{
                std::string sValue;
				if ( std::getline( _streamLine, sValue, ':' ) )
                {
                    stringVec.emplace_back( sValue );
                }
            }
            
            if( stringVec.size() != 4 ) return false;
            
            p_order = std::make_shared<Order>( stringVec.at(0),
                                               stringVec.at(1),
                                               std::stol( stringVec.at(2) ),
                                               std::stof( stringVec.at(3) ) );
            
            return true;
        }
        
        bool Validate( const OrderShd& p_order )
        {
            if( p_order->GetQuantity() == 0 ) return false;
            
            if( p_order->GetPrice() <= 0 ) return false;
            
            return true;
        }
        
        void PrintOrders()
        {
            for( auto & order : mOrderList )
                if( order->GetQuantity() > 0 )
                    write( order->Print() );
        }
        
        const std::string& DisplayOrders()
        {
            std::string sOrders = "List of Orders: \n";
            
            for( auto & order : mOrderList )
                sOrders += " * " + order->Display() + "\n";
            
            return sOrders;
        }

};

#endif // _OrderObject_H_
