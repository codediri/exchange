/******************************************************************************
 *
 * Title:           Trade Class
 *
 * Description:     Trade Main Program
 *
 * Author:          Arman (https://github.com/codediri)
 *
 ******************************************************************************
 */
 
#ifndef _Trade_H_
#define _Trade_H_

#include "Common.hpp"

class Trade
{
    private:
        std::string mMatchId;
        std::string mBuyerId;
        std::string mSellerId;
        std::string mInstrument;
        long mQuantity;
        float mPrice;
        OrderType mOrderType;
		
    protected:		
        
    public:
        Trade( const std::string& p_buyerId,
               const std::string& p_selledId,
               const std::string& p_instrument,
               const long& p_quantity,
               const float& p_price ) :
               mBuyerId( p_buyerId ),
               mSellerId( p_selledId ),
               mInstrument( p_instrument ),
               mQuantity( p_quantity ),
               mPrice( p_price )
       {
       }
        
        ~Trade()
        {
            mMatchId.clear();
            mBuyerId.clear();
            mSellerId.clear();
            mInstrument.clear();
        };
        
        void SetMatchId( std::string&& p_matchId )
        {
            mMatchId = p_matchId;
        }
        
        void SetOrderType( OrderType&& p_orderType )
        {
            mOrderType = p_orderType;
        }
        
        const std::string& GetMatchId() { return mMatchId; }
        const std::string& GetBuyerId() { return mBuyerId; }
        const std::string& GetSellerId() { return mSellerId; }
        const std::string& GetInstrument() { return mInstrument; }
        const long& GetQuantity() { return mQuantity; }
        const float& GetPrice() { return mPrice; }
        const OrderType& GetOrderType() { return mOrderType; }
        
        std::string&& Print()
        {
            std::string tradeStr = GetBuyerId() + ":" +
                GetSellerId() + ":" +
                GetInstrument() + ":" +
                std::to_string( GetQuantity() ) + ":" +
                std::to_string( GetPrice() );
            return std::move( tradeStr );
        }
        
        std::string&& Display()
        {
            std::string tradeStr = GetMatchId() + ":" +
                Print() + ":" + std::to_string((int)GetOrderType());
            return std::move( tradeStr );
        }

};

using TradeShd = std::shared_ptr<Trade>;
using TradePtr = Trade*;

#endif // _Trade_H_
