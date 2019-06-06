/**
  *@file json.h
  *@brief header for c implementation of json parsing
  *@author Jason Berger
  *@date 06/5/2019
  */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef enum {
  JSON_VALID = 0,
  JSON_INCOMPLETE,
  JSON_PARSING_ERROR,
} json_parse_status_e;

typedef enum {
  JSON_IDLE,
  JSON_KEY_STARTED,
  JSON_KEY_FINISHED,
  JSON_VAL_SEEK,
  JSON_VAL_STARTED,
  JSON_VAL_FINISHED
} json_parse_state_e;

typedef struct{
  char* mKey;
  int mKeyLen;
  char* mVal;
  int mValLen;
} json_pair_t;

typedef struct json_obj{
  json_pair_t* mAttributes;
  int mAttributeCount;
}json_obj_t;


json_parse_status_e json_parse_string(json_obj_t* json, const char* str, int len);

void json_clean(json_obj_t* json);
