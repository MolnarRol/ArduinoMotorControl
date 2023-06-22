#include "Communication.h"

CommandTypeDef REG_commands[] = 
{
  { "rpm", &RPM_Callback, "" },
  { "on", &REG_on_Callback, "" },
  { "off", &REG_off_Callback, "" },
  { "__End__", NULL }
};

CommandGroupTypeDef REG =
{
  "reg",
  "Commands for regulation",
  REG_commands
};

CommandTypeDef PWM_commands[] = 
{
  { "duty", &PWM_duty_Callback, "" },
  { "on", &PWM_on_Callback, "" },
  { "off", &PWM_off_Callback, "" },
  { "__End__", NULL }
};

CommandGroupTypeDef PWM = 
{
  "pwm",
  "Commands used for PWM manipulation",
  PWM_commands
};

CommandTypeDef BRAKE_commands[] = 
{
  { "on", &BRAKE_on_Callback, "" },
  { "off", &BRAKE_off_Callback, "" },
  { "__End__", NULL }
};

CommandGroupTypeDef BRAKE = 
{
  "brake",
  "brake",
  BRAKE_commands
};

CommandTypeDef DIR_commands[] = 
{
  { "cw", &DIR_1_Callback, "" },
  { "ccw", &DIR_2_Callback, "" },
  { "chDir", &DIR_change_Callback, "" },
  { "__End__", NULL }
};

CommandGroupTypeDef DIR = 
{
  "dir",
  "dir",
  DIR_commands
};

CommandGroupTypeDef* CommandGroupArr[] = 
{
  &PWM,
  &BRAKE,
  &DIR,
  &REG,
  NULL
};

CommandTypeDef MiscCommands[] =
{
  { "clear", &clearTerminal, "Clear output terminal" },
  { "back", &resetGroup, "" },
  { "__End__", NULL }
};

uint8_t g_group_idx = 255;  // Sellected group index -> 255 = no sellection

void msgToCommand( String msg )
{
  String words[MAX_WORDS_IN_PROMPT] = {""};  // Input parsed to words
  const uint8_t n_words = stringToWords( msg, words );  // Number of words

  uint8_t idx = 0;
  while( MiscCommands[idx].cmd != "__End__" )
  {
    if( MiscCommands[idx].cmd == words[0] )
    {
      MiscCommands[idx].p_function("");
      return;
    }
    idx++;
  } 

  idx = 0;
  if( g_group_idx != 255 )
  {    
    while( CommandGroupArr[g_group_idx]->List[idx].cmd != "__End__" )
    {
      if( CommandGroupArr[g_group_idx]->List[idx].cmd == words[0] )
      {
        CommandGroupArr[g_group_idx]->List[idx].p_function(words[1]);
        return;
      }
      idx++;
    }    
  }
  
  idx = 0;
  while( CommandGroupArr[idx] != NULL )
  {
    if( CommandGroupArr[idx]->identity == words[0] )
    {
      g_group_idx = idx;
      return;
    }
    idx++;
  }
};

void printHeader()
{
 Serial.print(">> ");
  if( g_group_idx != 255 )
  {
    Serial.print( CommandGroupArr[g_group_idx]->identity + " >> ");
  }
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
      if( (idx_word + 1) == COMMAND_MAX_CHAR ) break;
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
  parsedFloat = (float)parsedDecimal / (float)powerOf10( (uint8_t)strlen(decimal) );
  parsedFloat += (float)parsedInteger;
  return parsedFloat;
};

String getStringUART()
{
  while( Serial.available() == 0 ){};                     // Wait for input
  return Serial.readStringUntil( '\n' );
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

void clearTerminal( String msg )
{
  for( uint8_t i; i < 50; i++ ) Serial.println();
};

void resetGroup( String msg )
{
  g_group_idx = 255;
};

// void helper( String msg )
// {
//   Serial.println("All possible commands:");
//   uint8_t id = 0;  

//   while( CommandList[id].cmd != "__End__"  )
//   {
//     Serial.println("\t- " + CommandList[id].cmd + ":\t\t" + CommandList[id].help );
//     id++;
//   }  
// };

// PWM Test
// String words[MAX_WORDS_IN_PROMPT];
// const uint8_t n_words = stringToWords( msg, words );
// float numFromStr = parseFloat(words[0]);
// if( numFromStr != -1.0f ) SetPwmDuty( numFromStr );
//PWM_duty_Callback( words[0] );