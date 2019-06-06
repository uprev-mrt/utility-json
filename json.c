/**
  *@file json.h
  *@brief header for c implementation of json parsing
  *@author Jason Berger
  *@date 06/5/2019
  */

#include "json.h"



json_parse_status_e json_parse_string(json_obj_t* json, const char* str, int len)
{
  bool inQuotes = false;
  int isEscaped = 0;

  int state = JSON_IDLE;


  int lastStart = 0;
  int strLen =0;
  int idx = 0;


  json->mAttributeCount =0;


  //count attributes
  for(int i=0; i < len; i++)
  {
    if((str[i] == '\\') )
    {
      isEscaped = !isEscaped;
    }
    else
    {
      if(!isEscaped)
      {
        switch(str[i])
        {
          case '"':
            inQuotes = !inQuotes; //toggle quote state
            break;
          case ':':
            if(!inQuotes)
            {
              json->mAttributeCount++;
            }
            break;
        }
      }
      isEscaped = false;
    }
  }

  //allocate mem for pairs
  json->mAttributes = (json_pair_t*) malloc(sizeof(json_pair_t) * json->mAttributeCount);


  //split into pairs
  for(int i=0; i < len; i++)
  {
    if((str[i] == '\\') )
    {
      isEscaped = !isEscaped;
    }
    else
    {
      if(!isEscaped)
      {
        switch(str[i])
        {
          case '"':
            inQuotes = !inQuotes; //toggle quote state
            state++;
            if(state == JSON_KEY_FINISHED)
            {
              strLen = i -lastStart;
              json->mAttributes[idx].mKey = (char*) malloc(strLen+1);
              memcpy(json->mAttributes[idx].mKey,&str[lastStart],strLen  );
              json->mAttributes[idx].mKey[strLen] =0;
            }
            else if(state == JSON_VAL_FINISHED)
            {
              strLen = i -lastStart;
              json->mAttributes[idx].mVal = (char*) malloc(strLen+1);
              memcpy(json->mAttributes[idx].mVal,&str[lastStart],strLen  );
              json->mAttributes[idx].mVal[strLen] =0;
            }
            lastStart = i+1;
            break;
          case ':':
            if((!inQuotes))
            {
              state = JSON_VAL_SEEK;
            }
            break;
          case ' ':
          case '}':
            if((!inQuotes) && (state == JSON_VAL_STARTED))
            {
              state = JSON_VAL_FINISHED;
              strLen = i -lastStart;
              json->mAttributes[idx].mVal = (char*) malloc(strLen+1);
              memcpy(json->mAttributes[idx].mVal,&str[lastStart],strLen );
              json->mAttributes[idx].mVal[strLen] =0;
            }
            break;
          default:
            if(state == JSON_VAL_SEEK)
            {
              lastStart = i;
              state = JSON_VAL_STARTED;
            }
            break;
        }
      }
      isEscaped = false;
    }

    if(state == JSON_VAL_FINISHED)
    {
      idx++;
      state = JSON_IDLE;
    }
  }
}

void json_clean(json_obj_t* json)
{
  if(json->mAttributeCount > 0)
  {
    for(int i=0; i < json->mAttributeCount; i++)
    {
      free(json->mAttributes[i].mKey);
      free(json->mAttributes[i].mVal);
    }

    free(json->mAttributes);
  }
}
