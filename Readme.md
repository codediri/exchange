# AE Exchange Demo Program

Version 0.02

## Overview

This is a basic exchange program prototype

## Building 

To compile:
1) Go to the 'com' folder
2) Run 'make app'
3) A "Exchange" binary will be created in the 'bin' folder.

## Running the Application

1) Go to 'bin' folder
2) Running the Application will have the following format:
   
   ./Exchange <Orders Output file> <Trades output file>

   where:
    - <Orders Output file>: the file that stores the working orders
    - <Trades output file>: the file that stores the trades
   
   Sample run:
    ./Exchange orders.txt trades.txt
  
## Console
The Main Display will be the following:

AE Exchange Demo Program
1) Enter Order
2) Display Orders and Trades in console
3) Pint Orders and Trades in files and Exit

### 1. Entering Order
To enter order, use the following format:
  <buyer/sellerid>:<instrument>:<signedquantity>:<limitprice>

For example, an order to sell 100 AUD (against USD) at a price of 1.47 (or more) would be,
  A:AUDUSD:100:1.47
  
After entering order, the program will ask to enter another order, or press 'x' to go back to Main Menu.
  
Note: The matching will occur immediately as soon as the order is processed succesfully.

### 2. Displaying Orders and Trades
Displaying orders will show all the orders inputted, along with its latest status.
List of trades will also be displayed.

The order/trade status will consists of:
* NEW --> means the order was not yet matched
* WORKING --> the order has been partially matched, but still has a working quantity
* EXPIRED --> the order has been fully matched, and already fully traded
* PARTIAL_FILLED --> the trade was not yet fully filled
* FILLED --> the trade was fully filled
   
### 3. Printing Orders/Trades to output files and Exit Program
The same orders/trades will be printed in the output files given as parameter when executing the program.

Note: Printed output files has lesser detail than in "Displayed Orders and Trades (Menu 2)", e.g. the printed file has no status

   
## Sample Run-Thru

[***** bin]$ ./Exchange orders.txt trades.txt

AE Exchange Demo Program
1) Enter Order
2) Display Orders and Trades in console
3) Print Orders and Trades in files and Exit
Choice: 1
Order Format: <buyer/sellerid>:<instrument>:<signedquantity>:<limitprice>

Enter New Order or 'x' to go back: A:GBPUSD:100:1.66

Enter New Order or 'x' to go back: B:EURUSD:-100:1.11

Enter New Order or 'x' to go back: F:EURUSD:-50:1.1

Enter New Order or 'x' to go back: C:GBPUSD:-10:1.5

Enter New Order or 'x' to go back: C:GBPUSD:-20:1.6

Enter New Order or 'x' to go back: C:GBPUSD:-20:1.7

Enter New Order or 'x' to go back: D:EURUSD:100:1.11

Enter New Order or 'x' to go back: x
AE Exchange Demo Program
1) Enter Order
2) Display Orders and Trades in console
3) Pint Orders and Trades in files and Exit
Choice: 2
List of Orders:
 * A:GBPUSD:70:1.660000:WORKING
 * B:EURUSD:-50:1.110000:WORKING
 * F:EURUSD:0:1.100000:EXPIRED
 * C:GBPUSD:0:1.500000:EXPIRED
 * C:GBPUSD:0:1.600000:EXPIRED
 * C:GBPUSD:-20:1.700000:NEW
 * D:EURUSD:0:1.110000:EXPIRED

List of Trades:
 * A:C:GBPUSD:10:1.660000:15453732911:FILLED
 * A:C:GBPUSD:20:1.660000:15453732942:FILLED
 * D:F:EURUSD:50:1.100000:15453733033:FILLED
 * D:B:EURUSD:50:1.110000:15453733034:FILLED


Enter any key to go back: x

AE Exchange Demo Program
1) Enter Order
2) Display Orders and Trades in console
3) Pint Orders and Trades in files and Exit
Choice: 3

Please check the output files 'orders.txt' and 'trades.txt'. Goodbye!
[***** bin]$ cat orders.txt
A:GBPUSD:70:1.660000
B:EURUSD:-50:1.110000
C:GBPUSD:-20:1.700000
[***** bin]$ cat trades.txt
A:C:GBPUSD:10:1.660000
A:C:GBPUSD:20:1.660000
D:F:EURUSD:50:1.100000
D:B:EURUSD:50:1.110000
[***** bin]$


