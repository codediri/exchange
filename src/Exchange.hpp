/******************************************************************************
 *
 * Title:           Exchange Class
 *
 * Description:     Exchange Main Program
 *
 * Author:          Arman (https://github.com/codediri)
 *
 ******************************************************************************
 */
 
#ifndef _Exchange_H_
#define _Exchange_H_

#include "Common.hpp"
#include "OrderObject.hpp"
#include "TradeObject.hpp"
#include "OrderBook.hpp"

#define _Exchange_NAME_ "Exchange"
#define _Exchange_VERSION_ "0.1"
#define _Exchange_DATEMODIFIED_ (__DATE__)
#define _Exchange_TIMEMODIFIED_ (__TIME__)

using MapInsOrderBook = std::map<std::string, OrderBook>;

class Exchange :
    public OrderObject,
    public TradeObject
{
    private:
        MapInsOrderBook mOrderBookMap;
        
    public:
        Exchange( const std::string& p_orderFile, const std::string& p_tradeFile ) :
            OrderObject( p_orderFile ),
            TradeObject( p_tradeFile )
        {
            
        }
        
        ~Exchange() {}
        
        void Start()
        {
            MenuType menuT = MenuType::UNKNOWN;
            while( menuT != MenuType::EXIT )
            {
                menuT = Menu();
                
                switch( menuT )
                {
                    case MenuType::ADD_NEW_ORDER:
                        AddOrderDisplay();
                        
                        break;
                }
            }
            
            Stop();
        }
        
        void Stop() 
        {
            PrintOrders();
            PrintTrades();
            
            std::cout << std::endl << "Please check the output files '"
                    << OrderObject::GetFilename() << "' and '"
                    << TradeObject::GetFilename() << "'. Goodbye!"
                    << std::endl;
        }
        
        MenuType Menu()
        {
            std::string choiceS {""};
            int choiceI = 0;
            
            std::cout << "\x1B[2J\x1B[H";
            std::cout << "AE Exchange Demo Program" << std::endl;
            std::cout << "1) Enter Order" << std::endl;
            std::cout << "2) Exit" << std::endl;
            std::cout << "Choice: " ;
            
            std::cin >> choiceS;
            
            try {
                choiceI = std::stoi( choiceS );
            }
            catch (const std::invalid_argument& ia) {
              choiceI = 0;
            }
            
            return (MenuType) choiceI;
        }
        
        void AddOrderDisplay()
        {
            std::cout << "Order Format: <buyer/sellerid>:<instrument>:<signedquantity>:<limitprice>" 
                      << std::endl;
            std::string exitS;
            
            MenuType menuT = MenuType::UNKNOWN;
            do
            {
                menuT = AddOrderMenu() ;
                
                if( menuT == MenuType::SET_FAILURE )
                {
                    std::cout << "Adding New Order FAILED."
                        << " Please check formatting and Price/Quantity values."
                        << std::endl;
                        
                    //continue;
                }
                
            } while( menuT != MenuType::BACK_TO_PREV );
        }
        
        MenuType AddOrderMenu()
        {
            std::string orderS {""};
            std::cout << std::endl << "Enter New Order or 'x' to go back: ";
            std::cin >> orderS;
            
            if( orderS == "x" ) return MenuType::BACK_TO_PREV;
            
            OrderShd order;
            if( !AddNewOrder( orderS, order ) ) 
                return MenuType::SET_FAILURE;
            
            //Add the Order to the OrderBook
            //std::cout << "Order Detail: " << order->Print() << std::endl;
            OrderBook orderbook( order->GetInstrument() );
            
            std::pair<MapInsOrderBook::iterator, bool> itR =
                mOrderBookMap.emplace( order->GetInstrument(), 
                    orderbook );
                    
            //Time for Matching
            itR.first->second.SetMatch( order.get(), GetTradeObject() );
                
            if( order->GetQuantity() != 0 )
                itR.first->second.AddToOrderBook( order.get() );
            
            return MenuType::SET_MATCHING;
        }

};

#endif // _Exchange_H_
