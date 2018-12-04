/******************************************************************************
 *
 * Title:           TradeObject Class
 *
 * Description:     TradeObject Main Program
 *
 * Author:          Arman (https://github.com/codediri)
 *
 ******************************************************************************
 */
 
#ifndef _TradeObject_H_
#define _TradeObject_H_

#include "Trade.hpp"
#include "FileHandler.hpp"

class TradeObject :
    public FileHandler
{
    private:
        std::vector<TradeShd> mTradeList;
		
    protected:		
    
    public:
        TradeObject( const std::string& p_tradeFile ) : 
            FileHandler( p_tradeFile )
        {

        }
        
        ~TradeObject() 
        {
            mTradeList.clear();
        };
        
        TradePtr AddTrade( const std::string& p_buyerId,
                       const std::string& p_selledId,
                       const std::string& p_instrument,
                       const long& p_quantity,
                       const float& p_price )
        {
            TradeShd trade = std::make_shared<Trade>(
                    p_buyerId,
                    p_selledId,
                    p_instrument,
                    p_quantity,
                    p_price );
                    
            trade->SetMatchId("fsda");
                    
            mTradeList.push_back( std::move( trade ) );
            
            return mTradeList[mTradeList.size()-1].get();
        }
        
        void PrintTrades()
        {
            for( auto & trade : mTradeList )
                write( trade->Print() );
        }
        
        void DisplayTrades()
        {
            for( auto & trade : mTradeList )
                write( trade->Display() );
        }
        
        TradeObject* GetTradeObject()
        {
            return this;
        }

};

#endif // _TradeObject_H_
