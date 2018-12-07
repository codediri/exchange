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
                    /* TradePtr tradeSell = tradeObj->AddTrade(
                        order->GetTraderId(),
                        (*itV)->GetTraderId(),
                        (*itV)->GetInstrument(),
                        ( orderQty * -1 ),
                        (*itV)->GetPrice() );
                    tradeSell->SetOrderType( OrderType::PARTIAL_FILLED ); */
                    
                    (*itV)->SetQuantity( orderQty + (*itV)->GetQuantity() );
                    orderQty = 0;
                }
                
                if( orderQty <= 0 )
                {
                    // Create trade for the Buy Order
                    TradePtr tradeBuy = tradeObj->AddTrade(
                        order->GetTraderId(),
                        (*itV)->GetTraderId(),
                        (*itV)->GetInstrument(),
                        order->GetQuantity() - orderQty,
                        (*itV)->GetPrice() );
                    tradeBuy->SetOrderType( OrderType::FILLED );
                }
                
                order->SetQuantity(orderQty);
                
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
                if( orderQty <= 0 )
                {
                    // Create FILLED trade for the Buy Order
                    TradePtr tradeSell = tradeObj->AddTrade(
                        (*itV)->GetTraderId(),
                        order->GetTraderId(),
                        (*itV)->GetInstrument(),
                        (*itV)->GetQuantity(),
                        (*itV)->GetPrice() );
                    tradeSell->SetOrderType( OrderType::FILLED );
                        
                    // Set Order to expired
                    (*itV)->SetQuantity(0);
                }
                // Sell Order is filled,
                // Buy Order still have working quantity
                else
                {
                    // Create PARTIAL_FILLED trade for the Sell Order
                    /* TradePtr tradeSell = tradeObj->AddTrade(
                        order->GetTraderId(),
                        (*itV)->GetTraderId(),
                        (*itV)->GetInstrument(),
                        orderQty,
                        (*itV)->GetPrice() );
                    tradeSell->SetOrderType( OrderType::PARTIAL_FILLED ); */
                    
                    (*itV)->SetQuantity( (*itV)->GetQuantity() - orderQty );
                    orderQty = 0;
                }
                    
                if( orderQty >= 0 )
                {
                    // Create trade for the Sell Order
                    TradePtr tradeBuy = tradeObj->AddTrade(
                        order->GetTraderId(),
                        (*itV)->GetTraderId(),
                        (*itV)->GetInstrument(),
                        labs(order->GetQuantity()) - labs(orderQty),
                        (*itV)->GetPrice() );
                    tradeBuy->SetOrderType( OrderType::FILLED );
                }
                
                order->SetQuantity(orderQty);
                
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
