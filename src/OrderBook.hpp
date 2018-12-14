/******************************************************************************
 *
 * Title:           OrderBook Class
 *
 * Description:     OrderBook Main Program
 *
 * Author:          https://github.com/codediri
 *
 ******************************************************************************
 */
 
#ifndef _OrderBook_H_
#define _OrderBook_H_

#include "Order.hpp"
#include "Instrument.hpp"
#include "PriceLevel.hpp"

using MapPriceLevel = std::map<float, PriceLevel>;

class OrderBook :
    public Instrument
{
    private:
        MapPriceLevel mPriceLevelBuy;
        MapPriceLevel mPriceLevelSell;
		
    protected:		
        
    public:
        OrderBook( std::string p_instrument ) :
            Instrument( p_instrument )
        {
        }
        
        void AddToOrderBook( OrderPtr order )
        {
            std::pair<MapPriceLevel::iterator, bool> itM;
            
            if( order->GetQuantity() > 0 )
                itM =
                    mPriceLevelBuy.emplace( order->GetPrice(), PriceLevel() );
            else
                itM =
                    mPriceLevelSell.emplace( order->GetPrice(), PriceLevel() );
                    
            itM.first->second.AddPriceLevelOrder( order );
        }
        
        void SetMatch( OrderPtr order, TradeObject* tradeObj )
        {
            if( order->GetQuantity() > 0 ) // Buy Order
            {
                for( MapPriceLevel::iterator itM = mPriceLevelSell.begin(); 
                     itM != mPriceLevelSell.end(); 
                     ++itM )
                {
                    // if Buy Price is greater than or equal to iterated 'Sell' price level
                    if( order->GetPrice() >= itM->first ) 
                    {
                        itM->second.SetMatchBuy( order, tradeObj );
                        if( order->GetQuantity() == 0 )
                        {
                            //Matching completed, order was filled
                            //Set the order to expired
                            order->SetOrderType( exch::OrderType::EXPIRED );
                            order->SetQuantity(0);
                            
                            //no need to continue further
                            break;
                        }
                    }
                    // this is an ordered map (ascending), so NO need to continue further
                    else 
                        break;
                        
                }
            }
            else // Sell Order
            {
                
                for( MapPriceLevel::reverse_iterator itM = mPriceLevelBuy.rbegin(); 
                     itM != mPriceLevelBuy.rend(); 
                     ++itM )
                {
                    // if Sell Price is lesser than or equal to iterated 'Buy' price level
                    if( order->GetPrice() <= itM->first ) 
                    {
                        itM->second.SetMatchSell( order, tradeObj );
                        if( order->GetQuantity() == 0 )
                        {
                            //Matching completed, order was filled
                            //Add trade in the TradeObject
                            
                            //no need to continue further
                            break;
                        }
                    }
                    // this is an ordered map (descending), so NO need to continue further
                    else 
                        break;
                }
            }
        }
        
        ~OrderBook()
        {
            //OrderMap.clear();
        }

};

#endif // _OrderBook_H_
