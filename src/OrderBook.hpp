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
        
        ~OrderBook()
        {
            //OrderMap.clear();
        }

};

#endif // _OrderBook_H_
