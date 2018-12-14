/******************************************************************************
 *
 * Title:           Order Class
 *
 * Description:     Order Main Program
 *
 * Author:          Arman (https://github.com/codediri)
 *
 ******************************************************************************
 */
 
#ifndef _Order_H_
#define _Order_H_

#include "Common.hpp"

class Order
{
    private:
        std::string mTraderId;
        std::string mInstrument;
        long mQuantity;
        float mPrice;
        exch::OrderType mOrderType = exch::OrderType::NEW;
		
    protected:		
        
    public:
        Order() {}
        Order( const std::string& p_traderId,
               const std::string& p_instrument,
               long&& p_quantity,
               float&& p_price ) :
               mTraderId( p_traderId ),
               mInstrument( p_instrument ),
               mQuantity( p_quantity ),
               mPrice( p_price )
        {}
        
        const std::string& GetTraderId() { return mTraderId; }
        const std::string& GetInstrument() { return mInstrument; }
        const long& GetQuantity() { return mQuantity; }
        const float& GetPrice() { return mPrice; }
        const exch::OrderType& GetOrderType() { return mOrderType; }
        
        void SetQuantity( const long& p_quantity ) { mQuantity = p_quantity; }
        void SetOrderType( exch::OrderType&& p_orderType ) { mOrderType = p_orderType; }
        
        std::string Print()
        {
            std::string orderStr = GetTraderId() + ":" +
                GetInstrument() + ":" +
                std::to_string( GetQuantity() ) + ":" +
                std::to_string( GetPrice() );
            return orderStr;
        }
        
        std::string Display()
        {
            std::string orderStr = Print() + ":" +
                exch::GetOrderTypeStr( GetOrderType() );
            return orderStr;
        }
        
        ~Order()
        {
            mTraderId.clear();
            mInstrument.clear();
        };

};

using OrderShd = std::shared_ptr<Order>;
using OrderPtr = Order*;

#endif // _Order_H_
