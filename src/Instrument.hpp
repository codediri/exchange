/******************************************************************************
 *
 * Title:           Instrument Class
 *
 * Description:     Instrument Main Program
 *
 * Author:          https://github.com/codediri
 *
 ******************************************************************************
 */
 
#ifndef _Instrument_H_
#define _Instrument_H_

#include "Common.hpp"

class Instrument
{
    private:
        std::string mName;
		
    protected:		
        
    public:
        Instrument( std::string p_instrument ) :
            mName( p_instrument )
        {
            
        }
        
        const std::string& GetInstrumentName() { return mName; }
        
        ~Instrument() 
        {}

};

#endif // _Instrument_H_
