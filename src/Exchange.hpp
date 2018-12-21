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
#define _Exchange_VERSION_ "0.3"
#define _Exchange_DATEMODIFIED_ (__DATE__)
#define _Exchange_TIMEMODIFIED_ (__TIME__)

// Map Container of Instruments with their working orders (OrderObject)
using MapInsOrderBook = std::map<std::string, OrderBook>;

class Exchange :
    public OrderObject,
    public TradeObject
{
    private:
        MapInsOrderBook mOrderBookMap;
        
    public:
        // Constructor
        Exchange( const std::string& p_orderFile, const std::string& p_tradeFile ) :
            OrderObject( p_orderFile ),
            TradeObject( p_tradeFile )
        {
            
        }
        
        ~Exchange() {}
        
        // Called by the main function, starting point of the program
        void Start()
        {
            exch::MenuType menuT = exch::MenuType::UNKNOWN;
            while( menuT != exch::MenuType::EXIT )
            {
                menuT = Menu();
                
                switch( menuT )
                {
                    case exch::MenuType::ADD_NEW_ORDER:
                        AddOrderDisplay();
                        break;
                    case exch::MenuType::DISPLAY_ORDERS:
                        DisplayOrdersAndTrades();
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
        
        exch::MenuType Menu()
        {
            std::string choiceS {""};
            int choiceI = 0;
            
            std::cout << "\x1B[2J\x1B[H";
            std::cout << "AE Exchange Demo Program" << std::endl;
            std::cout << "1) Enter Order" << std::endl;
            std::cout << "2) Display Orders and Trades in console" << std::endl;
            std::cout << "3) Pint Orders and Trades in files and Exit" << std::endl;
            std::cout << "Choice: " ;
            
            std::cin >> choiceS;
            
            try {
                choiceI = std::stoi( choiceS );
            }
            catch (const std::invalid_argument& ia) {
              choiceI = 0;
            }
            
            return (exch::MenuType) choiceI;
        }
        
        void DisplayOrdersAndTrades()
        {
            std::cout << DisplayOrders() << std::endl;
            std::cout << DisplayTrades() << std::endl;
            
            std::string key {""};
            std::cout << std::endl << "Enter any key to go back: ";
            std::cin >> key;
        }
        
        void AddOrderDisplay()
        {
            std::cout << "Order Format: <buyer/sellerid>:<instrument>:<signedquantity>:<limitprice>" 
                      << std::endl;
            std::string exitS;
            
            exch::MenuType menuT = exch::MenuType::UNKNOWN;
            do
            {
                menuT = AddOrderMenu() ;
                
                if( menuT == exch::MenuType::SET_FAILURE )
                {
                    std::cout << "Adding New Order FAILED."
                        << " Please check formatting and Price/Quantity values."
                        << std::endl;
                        
                    //continue;
                }
                
            } while( menuT != exch::MenuType::BACK_TO_PREV );
        }
        
        exch::MenuType AddOrderMenu()
        {
            std::string orderS {""};
            std::cout << std::endl << "Enter New Order or 'x' to go back: ";
            std::cin >> orderS;
            
            if( orderS == "x" ) return exch::MenuType::BACK_TO_PREV;
            
            OrderShd order;
            if( !AddNewOrder( orderS, order ) ) 
                return exch::MenuType::SET_FAILURE;
            
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
            
            return exch::MenuType::SET_MATCHING;
        }

};

#endif // _Exchange_H_
