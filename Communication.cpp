#include "Communication.h"

char UART_buff[UART_BUFF_LEN];

// Command CommandStruct[] = 
// {
//   { "clear", &clearTerminal, "Clear output terminal" },
//   { "help", &helper, "Print all possible commands" },
//   { "pid on", NULL, "Turn on PID regulation" },
//   { "__End__", NULL }
// }; 

void msgToCommand( String msg )
{
  String words[MAX_WORDS_IN_PROMPT];
  uint8_t n_words = stringToWords( msg, words );
  for( uint8_t i = 0; i < n_words; i++ )    // DEBUG
  {
    parseFloat(words[i]);
  }
  

  // uint8_t id = 0;  
  // if( msg != "clear" ) Serial.println(msg);

  // while( CommandList[id].cmd != "__End__" )
  // {
  //   if( msg == CommandList[id].cmd )
  //   {      
  //     CommandList[id].p_function( msg );
  //     return;
  //   }    
  //   id++;
  // }  
  // Serial.println( "\t\"" + msg + "\" is invalid command");
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
    if( msg[idx] != ' ' ) 
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

  uint16_t parsedInteger = 0; // integer representation of integer part
  uint16_t parsedDecimal = 0; // integer representation of decimal part
  float parsedFloat = 0.0f;   // parsedInteger + parsedDecimal * strlen(parsedDecimal);

  uint8_t idx;
  for( idx = 0; idx < strNum.length(); idx++ )
  {
    if( strNum[idx] == decimalPoint )
    {
      foundDecimalPoint = 1;
      num_idx = 0;
      continue;
    }
    if( foundDecimalPoint ) decimal[num_idx++] = strNum[idx];
    else integer[num_idx++] = strNum[idx];
  }

  for( uint8_t idx = 0; idx < strlen(integer); idx++ )
  {
    parsedInteger *= 10;
    parsedInteger += charToDec( integer[idx] );
  }

  for( uint8_t idx = 0; idx < strlen(integer); idx++ )
  {
    parsedDecimal *= 10;
    parsedDecimal += charToDec( decimal[idx] );
  }
  Serial.println(parsedDecimal);
  parsedFloat = (float)parsedDecimal / ( 10.0f * (float)strlen(decimal) );
  parsedFloat += (float)parsedInteger;
  return parsedFloat;
};

static inline uint8_t charToDec( char ch )
{
  ch -= 48;   // char - 48 => integer represented by char
  return ( ch < 0 || ch > 9 ) ? 0 : ch; // if char is not representing number => returning 0
}; 