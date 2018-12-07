/******************************************************************************
 *
 * Title:           FileHandler Class
 *
 * Description:     FileHandler Main Program
 *
 * Author:          https://github.com/codediri
 *
 ******************************************************************************
 */
 
#ifndef _FileHandler_H_
#define _FileHandler_H_

#include <fstream>

class FileHandler
{
    private:
        std::ofstream       fileStream;
        std::string         fileName;
		
    protected:		
        
    public:
        FileHandler( const std::string& p_file ) :
            fileName( p_file )
        {
            fileStream.open( fileName, std::ofstream::trunc );
            std::cout << "File Opened: " << fileName << std::endl;
        }
        
        ~FileHandler() 
        {
            if ( fileStream.is_open() )
                fileStream.close();
        }
        
        const std::string& GetFilename() { return fileName; }
        
        void write( std::string&& p_stringLine )
        {
            if ( !fileStream.is_open() )
                fileStream.open( fileName, std::ofstream::app );
            
            fileStream << p_stringLine << "\n";
            fileStream.close();
        }

};

#endif // _FileHandler_H_
