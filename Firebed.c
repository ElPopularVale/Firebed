/*
 * Copyright (c) 2016 Grana2.co
 *
 * This file is part of Grana2 software.
 *
 * Grana2 software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Grana2 software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Grana2 software.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @author Jose Granados <jose@grana2.co> 2016
 *
 * @brief Firebed: Embedded cloud synchronized database for connected embedded systems.
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef void* VPTR;
typedef int DB;

//Types of data
typedef enum VTYPE
{
  VT_PTR  = -1,
  VT_NULL =  0,
  VT_U8   =  1,
  VT_U16  =  2,
  VT_U32  =  4,
  VT_U64  =  8,
  VT_STR  =  16,
  VT_ARR  =  32,
  VT_OBJ  =  64,
} VTYPE_T;

//Key-value pair struct
typedef struct PAIR
{
    VTYPE_T     kt;         //Key type
    VPTR        kp;         //Key pointer
    uint16_t    klen;       //Key length
    VTYPE_T     vt;         //Key type
    VPTR        vp;         //value pointer
    uint16_t    vlen;       //value length
    PAIR_T      *next;      //Next pair
    PAIR_T      *child;     //Pointer to child, another object key or array
} PAIR_T;

//Main entry point
int main(void)
{
    KEY_T       *o1k1 = NULL;
    VALUE_T     *o1v1 = NULL;
    KEY_T       *o1k2 = NULL;
    
    KEY_T       *o2k1 = NULL;
    VALUE_T     *o2v1 = NULL;
    KEY_T       *o2k2 = NULL;
    VALUE_T     *o2v2 = NULL;

    KEY_T       *o3k1 = NULL;
    VALUE_T     *o3v1 = NULL;

    char *json = "{\"id\":1,\"name\":{\"first\":\"Joe\",\"last\":\"Doe\"},\"some\":\"thing\"}";
    char *ptr;

    ptr = strstr(json, '{');
    ptr = strstr(json + ptr, '"');

    printf("%s\n", ptr);

    //Manual parsing
    //"id":1
    o1k1->kt = VT_STR;
    o1k1->kp = 2;
    o1k1->klen = 2;
    o1k1->vt = VT_U8;
    o1k1->vp = 2;
    o1k1->vlen = 1;
    o1k1->next = o1k2;
    o1k1->child = NULL;

    //"name"
    o1k2->kt = VT_STR;
    o1k2->kp = 9;
    o1k2->klen = 4;
    o1k2->vt = VT_OBJ;
    o1k2->vp = NULL;
    o1k2->vlen = NULL;
    o1k2->next = o1k3;
    o1k2->child = o2k1;     //child object, can't point to a key object. When the child is a key object then it means it's a nested object. TODO: detect if child is an object. It looks like I have to do the parser first in order to recognize objects and arrays from strings and numbers in the child field.

    //Nested object
    //"first":"Jose"
    o2k1->p = 16;
    o2k1->len = 4;
    o2k1->next = o2k2;
    o2k1->vt = VT_STR;
    o2k1->child = NULL;
    o2v1->p = 24; 
    o2v1->len = 5;

    //last
    o2k2->vt = VT_STR;
    o2k2->p = 16;
    o2k2->len = 4;
    o2k2->next = NULL;
    o2k2->vt = VT_STR;
    o2k2->child = o2v2;

    //Doe
    o2v2->p = 24;
    o2v2->len = 5;

    //Previous object continuation
    //some
    o1k3->vt = VT_STR;
    o1k3->p = 16;
    o1k3->len = 4;
    o1k3->next = NULL;
    o1v3->vt = VT_STR;
    o1k3->child = o1v3;

    //thing
    o1v3->p = 24;
    o1v3->len = 5;

    return 0;
}
