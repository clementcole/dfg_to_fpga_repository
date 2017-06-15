#pragma once
#ifndef IEEE735_DECIMAL_TO_BINARY_HPP
#define IEEE735_DECIMAL_TO_BINARY_HPP
#include <ctype.h>
#include <cstddef>
#include <iostream> //cout, streambuf
#include <algorithm>
#include <fstream>  //std::ifstream
#include <list>
#include <functional>
#include <cstdio> //EOF detection
#include <string>
#include <sstream>
#include <stack>
#include <vector>
#include <map>
//#include "read_csv_sources/includes/enums.hpp"
#include <iterator>
#include <cstring>
#include <set>
#include <limits.h>
#include <iostream>
#include <math.h>
#include <bitset>
#include <random>
#include <ctime>
//#include "CPP_xrange/xrange.hpp"
//#include "population.hpp"
//#include "individual.hpp"
using std::cout;
using std::endl;
//using std::cout.precision(5);
using namespace std;



// Convert the 32-bit binary encoding into hexadecimal


//template to convert to string values
template <typename T>
std::string NumberToString ( T Number)
{
      ostringstream ss;
      ss << Number;
      return ss.str();
}
class data_formatter
{
    private:
      std::vector<std::string> data_hexadecimal;
      std::vector<std::string> data_decimal;
      std::vector<std::string> data_binary;
    
      
    public:
      //Constructors and Destructors
      //data_formatter(const std::string& symbol);
      //~data_formatter();
      
      //
      inline int Binary2Hex(std::string Binary);
      inline std::string binary(int i);
      inline std::string bin2hex(int iter);
      inline std::string ConvertBin2Hex(std::string sbin);
      inline std::string bcd(int iter);
      inline float Convert2FloatFormat_32( std::string Binary );
      inline std::string Convert2BinFormat_32( float value );
      
      inline void write_data_hexadecimal(string filename);
      inline void write_data_decimal(string filename);
      inline void write_data_binary(string filename);
      
};


inline int data_formatter::Binary2Hex( std::string Binary )
{
    std::bitset<32> set(Binary);      
    int hex = set.to_ulong();
     
    return hex;
}
 
inline std::string data_formatter::binary(int i)
{
      //Bin base 2
      int temp = i;
      string binary = "0000\t0000";
      for (int n = 8; n >= 0; n--)
      {
            if(n == 4)
            {
                  binary[n] = ' '; //space for readability
                  
            }
            else
            {
                  binary[n] = (temp%2) + 48; //base of 2
                  temp = temp / 2; //base of 2
            }
      }
      return binary;
}


//Binary to Hex 
inline std::string data_formatter::bin2hex(int iter)
{
      //Hex (16)
      int temp = iter;
      string hexadecimal = "00";
      for(int i = 1; i >= 0; i--)
      {
            int leftover = temp%16;
            if(leftover > 0)
            {
                  hexadecimal[i] = leftover + 55;  //making letters A- F for ten tru 15 for base 16
                  ;;
            }
            else 
            {
                  hexadecimal[i] = leftover + 48;
            }
            temp = temp / 16;
      }
      return hexadecimal;
}

//Convert back to bcd
inline std::string data_formatter::bcd(int iter)
{
      string bcd = "0000 0000 0000"; //default string for string size;
      string temp = NumberToString(iter); //Convert the int to string
      if(temp.length() == 1) //pad 0's where needed
      {
            string holder = "00" + temp;
            temp = holder;
      }
      if (temp.length() == 2)
      {
            string holder = "0" + temp;
            temp = holder;
            
      }
      for (int i = 0; i < 3; i++)
      {
            int k = temp[i] - 48; //convert value to an int and hold it
            for (int j = 3; j >= 0; j--) //for each of teh 4 numbers in the bit
            {
                  int position = 4 * (i + 1) + ( 1* i) - 1;
                  position -= ( 3 - j);
                  bcd[position] = k % 2 + 48;
                  k = k/2;
            }
      }return bcd;
}
// Convert the 32-bit binary into the decimal
inline float data_formatter::Convert2FloatFormat_32( std::string Binary )
{
    int HexNumber = Binary2Hex( Binary );
 
    bool negative  = !!(HexNumber & 0x80000000);
    int  exponent  =   (HexNumber & 0x7f800000) >> 23;    
    int sign = negative ? -1 : 1;
 
    // Subtract 127 from the exponent
    exponent -= 127;
 
    // Convert the mantissa into decimal using the
    // last 23 bits
    int power = -1;
    float total = 0.0;
    for ( int i = 0; i < 23; i++ )
    {
        int c = Binary[ i + 9 ] - '0';
        total += (float) c * (float) pow( 2.0, power );
        power--;
    }
    total += 1.0;
 
    float value = sign * (float) pow( 2.0, exponent ) * total;
 
    return value;
}
 
// Get 32-bit IEEE 754 format of the decimal value
inline std::string data_formatter::Convert2BinFormat_32( float value )
{
    union
    {
         float input;   // assumes sizeof(float) == sizeof(int)
         int   output;
    }    data;
 
    data.input = value;
 
    std::bitset<sizeof(float) * CHAR_BIT>   bits(data.output);
 
    std::string mystring = bits.to_string<char, 
                                          std::char_traits<char>,
                                          std::allocator<char> >();
 
    return mystring;
}

//Convert Binary to Hex
inline std::string data_formatter::ConvertBin2Hex(string sbin)
{
      string rest("0x"), temp, ch = "0000";
      int len = sbin.length() / 4;
      ch = ch.substr(0, len);
      sbin = ch+sbin;
      for (int i = 0; i < sbin.length(); i+=4)
      {
            temp = sbin.substr(i, 4);
            if(!temp.compare("0000")){rest = rest + "0";}
            else if(!temp.compare("0001")){rest = rest + "1";}
            else if(!temp.compare("0010")){rest = rest + "2";}
            else if(!temp.compare("0011")){rest = rest + "3";}
            else if(!temp.compare("0100")){rest = rest + "4";}
            else if(!temp.compare("0101")){rest = rest + "5";}
            else if(!temp.compare("0110")){rest = rest + "6";}
            else if(!temp.compare("0111")){rest = rest + "7";}
            else if(!temp.compare("1000")){rest = rest + "8";}
            else if(!temp.compare("1001")){rest = rest + "9";}
            else if(!temp.compare("1010")){rest = rest + "A";}
            else if(!temp.compare("1011")){rest = rest + "B";}
            else if(!temp.compare("1100")){rest = rest + "C";}
            else if(!temp.compare("1101")){rest = rest + "D";}
            else if(!temp.compare("1110")){rest = rest + "E";}
            else if(!temp.compare("1111")){rest = rest + "F";}
            else continue;
      }
      return rest;
}

inline void data_formatter::write_data_hexadecimal(string filename)
{
      
      ofstream fin;
      fin.open (filename, std::ios_base::app);
      std::vector<std::string> hex = data_hexadecimal;
      for(int i = 0; i < hex.size(); i++)
            fin << hex[i] << endl;
}
inline void data_formatter::write_data_decimal(string filename)
{
      ofstream fin;
      fin.open (filename, std::ios_base::app);
      std::vector<std::string> dec = data_decimal;
      for(int i = 0; i < dec.size(); i++)
            fin << dec[i] << endl; 
}
inline void data_formatter::write_data_binary(string filename)
{     
      ofstream fin;
      fin.open (filename, std::ios_base::app);
      std::vector<std::string> bin = data_binary;
      for(int i = 0; i < bin.size(); i++)
            fin << bin[i] << endl;
      
}
//data_formatter thisDataFormatter;
#endif