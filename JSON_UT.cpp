/**
  *@file FifoTest.cpp
  *@brief unit tests for the Fifo class
  *@author Jason Berger
  *@date 02/16/2019
  */
#ifdef UNIT_TESTING_ENABLED

extern "C"{

  #include "json.c"
}
#include <gtest/gtest.h>

json_obj_t obj;

const char* keys[] = {"name","valA","valB","valC"};
const char* vals[] = {"jason","25","4.67","28"};

char json_string[256];
char tmp_key[32];
char tmp_val[32];

//Test pushing data to Fifo
TEST(JSONTest, parse)
{
  sprintf(json_string, "{ \"%s\": \"%s\", \"%s\" : %s , \"%s\" : %s , \"%s\" : %s  }", keys[0], vals[0],keys[1], vals[1],keys[2], vals[2],keys[3], vals[3] );

  json_parse_string(&obj, json_string, strlen(json_string));

  //verify count
  ASSERT_EQ(obj.mAttributeCount, 4);

  //verify strings
  for(int i=0; i < obj.mAttributeCount; i++)
  {


    //printf("[%s]:[%s]\n",tmp_key,tmp_val);
    //printf("%i:%i = %i:%i\n",obj.mAttributes[i].mKey - json_string,obj.mAttributes[i].mKeyLen,obj.mAttributes[i].mVal - json_string,obj.mAttributes[i].mValLen );

     ASSERT_STREQ(obj.mAttributes[i].mKey, keys[i]);
     ASSERT_STREQ(obj.mAttributes[i].mVal, vals[i]);
  }
}




#endif
