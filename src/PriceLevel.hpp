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
        
        void SetMatchBuy( OrderPtr order )
        {
            long orderQty = order->GetQuantity();
            
            for( PriceOrderList::iterator itV = mPriceList.begin();
                 itV != mPriceList.end();
                 ++itV )
            {
                
            }
        }
        
        void SetMatchSell( OrderPtr order )
        {
        }
        
        ~PriceLevel()
        {
            //mPriceList.clear();
        }

};

#endif // _PriceLevel_H_
