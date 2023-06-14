#include "Communication.h"

char UART_buff[UART_BUFF_LEN];



void msgToCommand( String msg )
{
  
  // PWM Test
  String words[MAX_WORDS_IN_PROMPT];
  const uint8_t n_words = stringToWords( msg, words );
  float numFromStr = parseFloat(words[0]);
  if( numFromStr != -1.0f ) SetPwmDuty( numFromStr );
  

  // String words[MAX_WORDS_IN_PROMPT];
  // const uint8_t n_words = stringToWords( msg, words );

};


/*
  Add exeption for two or more spaces !
*/
uint8_t stringToWords( String msg, String words[MAX_WORDS_IN_PROMPT] )
{
  uint8_t wordCount = 0;              // Number of words in string msg
  uint8_t idx = 0;                    // Current char of string msg
  uint8_t idx_word = 0;               // Current char of string[word_count][idx_word]
  char tmp_word[COMMAND_MAX_CHAR];    // Temporary word buffer char string

  const char delimiter = ' ';

  for( idx; idx < msg.length(); idx++ )
  {
    if( msg[idx] != delimiter ) 
    {
      tmp_word[idx_word++] = msg[idx];
    }
    else
    {
      tmp_word[idx_word] = '\0';     // End the char string
      idx_word = 0;
      words[wordCount++] = tmp_word;
    }
  }   
  tmp_word[idx_word] = '\0';
  words[wordCount++] = tmp_word;

  return ( wordCount );
};

float parseFloat( String strNum )
{
  uint8_t num_idx = 0;  // variable for indexing char in char string
  const char decimalPoint = '.';  
  boolean foundDecimalPoint = 0;  // flag for reading decimal part of string
  char integer[16] = {0};   // char string containing integer part
  char decimal[16] = {0};   // char string containing decimal part

  uint8_t idx;
  for( idx = 0; idx < strNum.length(); idx++ )
  {
    if( ( strNum[idx] < '0' || strNum[idx] > '9') &&  strNum[idx] != '.' ) return -1.0f;    // Return -1.0f if the string contains non number character withou
    if( strNum[idx] == decimalPoint )
    {
      foundDecimalPoint = 1;
      num_idx = 0;
      continue;
    }
    if( foundDecimalPoint ) decimal[num_idx++] = strNum[idx];
    else integer[num_idx++] = strNum[idx];
  }
  uint32_t parsedInteger = charStrToDec( integer ); // integer representation of integer part
  uint32_t parsedDecimal = charStrToDec( decimal ); // integer representation of decimal part

  float parsedFloat = 0.0f;
  setPin();
  parsedFloat = (float)parsedDecimal / (float)powerOf10( (uint8_t)strlen(decimal) );
  clearPin();
  parsedFloat += (float)parsedInteger;
  return parsedFloat;
};

uint32_t charStrToDec( char* numStr)
{
  uint32_t num = 0;
  for( uint8_t idx = 0; idx < strlen(numStr); idx++ )
  {
    num *= 10;
    num += charToDec( numStr[idx] );
  }
  return num;
};

uint8_t charToDec( char ch )
{
  ch -= 48;   // char - 48 => integer represented by char
  return ( ch < 0 || ch > 9 ) ? 0 : ch; // if char is not representing number => returning 0
}; 

uint32_t powerOf10( uint8_t n )
{
  uint32_t power = 1;
  for( int i = 0; i < n; i++  ) power *= 10;
  return power;
};