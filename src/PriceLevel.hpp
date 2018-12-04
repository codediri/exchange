/******************************************************************************
 *
 * Title:           PriceLevel Class
 *
 * Description:     PriceLevel Main Program
 *
 * Author:          https://github.com/codediri
 *
 ******************************************************************************
 */
 
#ifndef _PriceLevel_H_
#define _PriceLevel_H_

#include "Common.hpp"

using PriceOrderList = std::vector<OrderPtr>;

class PriceLevel
{
    private:
        PriceOrderList mPriceList;
		
    protected:		
        
    public:
        PriceLevel()
        {
            
        }
        
        void AddPriceLevelOrder( OrderPtr order )
        {
            mPriceList.push_back( order );
        }
        
        void SetMatchBuy( OrderPtr order, TradeObject* tradeObj )
        {
            long orderQty = order->GetQuantity();
            
            for( PriceOrderList::iterator itV = mPriceList.begin();
                 itV != mPriceList.end();
                 ++itV )
            {
                orderQty -= labs((*itV)->GetQuantity());
                
                // Buy Order still have working quantity,
                // Sell Order is filled
                if( orderQty >= 0 )
                {
                    // Create FILLED trade for the Sell Order
                    TradePtr tradeSell = tradeObj->AddTrade(
                        order->GetTraderId(),
                        (*itV)->GetTraderId(),
                        (*itV)->GetInstrument(),
                        labs((*itV)->GetQuantity()),
                        (*itV)->GetPrice() );
                    tradeSell->SetOrderType( OrderType::FILLED );
                        
                    // Set Order to expired
                    (*itV)->SetQuantity(0);
                }
                // Buy Order is filled,
                // Sell Order still have working quantity
                else
                {
                    // Create PARTIAL_FILLED trade for the Sell Order
                    TradePtr tradeSell = tradeObj->AddTrade(
                        order->GetTraderId(),
                        (*itV)->GetTraderId(),
                        (*itV)->GetInstrument(),
                        ( orderQty * -1 ),
                        (*itV)->GetPrice() );
                    tradeSell->SetOrderType( OrderType::PARTIAL_FILLED );
                    
                    (*itV)->SetQuantity( orderQty + (*itV)->GetQuantity() );
                    orderQty = 0;
                }
                
                // Create trade for the Buy Order
                TradePtr tradeBuy = tradeObj->AddTrade(
                    order->GetTraderId(),
                    (*itV)->GetTraderId(),
                    (*itV)->GetInstrument(),
                    order->GetQuantity() - orderQty,
                    (*itV)->GetPrice() );
                    
                if( orderQty > 0 )
                    tradeBuy->SetOrderType( OrderType::PARTIAL_FILLED );
                else
                    tradeBuy->SetOrderType( OrderType::FILLED );
                
                order->SetQuantity(orderQty);
                
                if( orderQty == 0 )
                    itV = mPriceList.end();
            }
        }
        
        void SetMatchSell( OrderPtr order, TradeObject* tradeObj )
        {
        }
        
        ~PriceLevel()
        {
            //mPriceList.clear();
        }

};

#endif // _PriceLevel_H_
