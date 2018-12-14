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
                
                // Buy Order may still have working quantity or 0,
                // Sell Order is filled
                if( orderQty > 0 )
                {
                    // Fill the Sell Order
                    TradePtr tradeSell = tradeObj->AddTrade(
                        order->GetTraderId(),
                        (*itV)->GetTraderId(),
                        (*itV)->GetInstrument(),
                        labs((*itV)->GetQuantity()),
                        (*itV)->GetPrice() );
                    tradeSell->SetOrderType( exch::OrderType::FILLED );
                        
                    // Set Order to expired
                    (*itV)->SetQuantity(0);
                }
                else
                {
                    // Fill the Buy Order
                    TradePtr tradeBuy = tradeObj->AddTrade(
                        order->GetTraderId(),
                        (*itV)->GetTraderId(),
                        (*itV)->GetInstrument(),
                        order->GetQuantity(),
                        (*itV)->GetPrice() );
                    tradeBuy->SetOrderType( exch::OrderType::FILLED );
                    
                    (*itV)->SetQuantity( orderQty );
                    orderQty = 0;
                }
                
                order->SetQuantity(orderQty);
                
                if( order->GetQuantity() > 0 )
                    order->SetOrderType( exch::OrderType::WORKING );
                else
                    order->SetOrderType( exch::OrderType::EXPIRED );
                
                if( (*itV)->GetQuantity() < 0 )
                    (*itV)->SetOrderType( exch::OrderType::WORKING );
                else
                    (*itV)->SetOrderType( exch::OrderType::EXPIRED );
                
                if( orderQty == 0 )
                    break;
            }
        }
        
        void SetMatchSell( OrderPtr order, TradeObject* tradeObj )
        {
            long orderQty = order->GetQuantity();
            
            for( PriceOrderList::iterator itV = mPriceList.begin();
                 itV != mPriceList.end();
                 ++itV )
            {
                orderQty += (*itV)->GetQuantity();
                
                // Sell Order may still have working quantity or 0,
                // Buy Order is filled
                if( orderQty < 0 )
                {
                    // Create FILLED trade for the Buy Order
                    TradePtr tradeSell = tradeObj->AddTrade(
                        (*itV)->GetTraderId(),
                        order->GetTraderId(),
                        (*itV)->GetInstrument(),
                        (*itV)->GetQuantity(),
                        (*itV)->GetPrice() );
                    tradeSell->SetOrderType( exch::OrderType::FILLED );
                        
                    // Set Order to expired
                    (*itV)->SetQuantity(0);
                }
                else
                {
                    // Create trade for the Sell Order
                    TradePtr tradeBuy = tradeObj->AddTrade(
                        (*itV)->GetTraderId(),
                        order->GetTraderId(),
                        (*itV)->GetInstrument(),
                        labs(order->GetQuantity()),
                        (*itV)->GetPrice() );
                    tradeBuy->SetOrderType( exch::OrderType::FILLED );
                    
                    (*itV)->SetQuantity( orderQty );
                    orderQty = 0;
                }
                
                order->SetQuantity(orderQty);
                
                if( order->GetQuantity() < 0 )
                    order->SetOrderType( exch::OrderType::WORKING );
                else
                    order->SetOrderType( exch::OrderType::EXPIRED );
                
                if( (*itV)->GetQuantity() > 0 )
                    (*itV)->SetOrderType( exch::OrderType::WORKING );
                else
                    (*itV)->SetOrderType( exch::OrderType::EXPIRED );
                
                if( orderQty == 0 )
                    break;
            }
        }
        
        ~PriceLevel()
        {
            //mPriceList.clear();
        }

};

#endif // _PriceLevel_H_
