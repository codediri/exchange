#include <iostream>
#include <signal.h>
#include <execinfo.h>
#include <unistd.h>
#include "Exchange.hpp"

using namespace std;
unique_ptr<Exchange> exchangeUnq;

void sighandler(int sig)
{
    cerr << "Exchange SIGNAL Interrupt (" << sig << ")" << endl;
    
    if( sig == SIGINT )
        exchangeUnq->Stop();
    else
    {
        void *array[16];
        size_t size;
        size = backtrace(array, 16);
        backtrace_symbols_fd(array, size, STDERR_FILENO);
    }
    
    exit(0);
}
 
int main(int argc, char** argv)
{
    signal(SIGINT, &sighandler);
    //signal(SIGFPE, &sighandler);
    //signal(SIGSEGV, &sighandler);
    
    if( argc == 3 )
    {
		exchangeUnq.reset( new Exchange ( argv[1], argv[2] ) );
        exchangeUnq->Start();
    }
    else if( argc == 2 )
    {
        if( string(argv[1]) == "-v" )
        {
            cout << string( _Exchange_NAME_ ) << " Program" << endl;
            cout << "Version: " << string( _Exchange_VERSION_ ) << endl;
            cout << "Date Modified: " << string( _Exchange_DATEMODIFIED_ ) << " " << string( _Exchange_TIMEMODIFIED_ ) << endl;
        }
    }	
    else
    {
        cout << "Program usage: (binary) <Orders Output file> <Trades output file>" << endl;
        cout << "      Example: ./Exchange orders.txt trades.txt" << endl;
        cout << "Running the binary must have 2 arguments" << endl;
    }
    
    return 0;
}