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
 * @brief Firebed: Cloud synchronized database for connected embedded systems.
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define PRINT_OPAQUE_STRUCT(p)  print_mem((p), sizeof(*(p)))
#define JSON_OPENCURLY "{"
#define JSON_CLOSECURLY "}"
#define JSON_COMMA ","
#define JSON_DQUOTES "\""
#define JSON_COLON ":"

typedef void* VPTR;
typedef int DB;

//Types of data
typedef enum 
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
} VTYPE;

//Key-value pair struct
typedef struct PAIR
{
    VTYPE           kt;         //Key type
    VPTR            kp;         //Key pointer
    uint16_t        klen;       //Key length
    VTYPE           vt;         //Value type
    VPTR            vp;         //value pointer
    uint16_t        vlen;       //value length
    struct PAIR     *next;      //Next pair
    struct PAIR     *child;     //Pointer to child, another object key or array
} PAIR;

void print_mem(void const *vp, size_t n)
{
    unsigned char const *p = vp;
    size_t i;
    for (i=0; i<n; i++)
        printf("%02x\n", p[i]);
        // printf("%d\n", p[i]);
    putchar('\n');
};

void jsonParseObject(char* json, int index){
    // //Right now index is at open curly bracket
    // char *start = json + index;
    // char *end;
    // //Find opening double quotes
    // start = strstr(start, JSON_DQUOTES);
    // //Find closing double quotes
    // end = strstr(start, JSON_DQUOTES);

    // printf("String length: %d\n", end - start);

}
void jsonParseString(char* json, int index){

}
void jsonParseValue(char* json, int index){

}

//Main entry point
int main(void)
{
    PAIR       o1k1;
    PAIR       o1k2;
    
    PAIR       o2k1;
    PAIR       o2k2;

    PAIR       o1k3;

    char *json = "{\"identification\":1,\"name\":{\"first\":\"Joe\",\"last\":\"Doe\"},\"some\":\"thing\"}";
    char *ptr;
    int index;

    ptr = json;

    //Find open curly bracket
    //Find double quote
    //Find next double quote
    //Extract token string

    // for(index = 0; index < strlen(json); index++) {

    //     switch (json[index]){
    //         case JSON_OPENCURLY:
    //         printf("Open curly found at %d\n", index);
    //         jsonParseObject(json, index);
    //         break;

    //         case JSON_DQUOTES:
    //         printf("Double quotes found at %d\n", index);
    //         jsonParseString(json, index);
    //         break;

    //         case JSON_COLON:
    //         printf("Colon found at %d\n", index);
    //         jsonParseValue(json, index);
    //         break;

    //         // case JSON_COMMA:
    //         // printf("Comma found at %d\n", index);
    //         // break;

    //         // case JSON_CLOSECURLY:
    //         // printf("Close curly found at %d\n", index);
    //         // break;
    //     }

    // }

    //Find open curly bracket
    ptr = strstr(json, JSON_OPENCURLY);
    index = ptr-json;
    int kstart;
    int kend;
    int vstart;
    int vend;
    if(strncmp(ptr++, JSON_OPENCURLY, 1) == 0)
    {
        printf("Open curly found at %d\n", index);

        //Parse string
        //Find open double quote
        ptr = strstr(ptr, JSON_DQUOTES);
        index = ptr-json;
        if (strncmp(ptr++, JSON_DQUOTES, 1) == 0)
        {
            printf("Open double quotes found at %d\n", index);
             kstart = index;
            //Find closing double quote
            ptr = strstr(ptr, JSON_DQUOTES);
            index = ptr-json;
            if (strncmp(ptr++, JSON_DQUOTES, 1) == 0)
            {
             printf("Close double quotes found at %d\n", index);
             kend = index - 1;

            //Find colon
             ptr = strstr(ptr, JSON_COLON);
             index = ptr-json;
             if (strncmp(ptr++, JSON_COLON, 1) == 0)
             {
                 printf("Colon found at %d\n", index);

                 //Find open double quote
                 //FIXME: This only recognizes strings, not numbers 
                ptr = strstr(ptr, JSON_DQUOTES);
                index = ptr-json;
                if (strncmp(ptr++, JSON_DQUOTES, 1) == 0)
                {
                    printf("Open double quotes found at %d\n", index);
                     vstart = index;
                    //Find closing double quote
                    ptr = strstr(ptr, JSON_DQUOTES);
                    index = ptr-json;
                    if (strncmp(ptr++, JSON_DQUOTES, 1) == 0)
                    {
                     printf("Close double quotes found at %d\n", index);
                     vend = index - 1;
                     }

            }
        }


    }
}
}


     ptr = strstr(ptr, JSON_COLON);
     index = ptr-json;
     if (strncmp(ptr++, JSON_COLON, 1) == 0)
     {
         printf("Colon found at %d\n", index);
     }

     ptr = strstr(ptr, JSON_COMMA);
     index = ptr-json;
     if (strncmp(ptr++, JSON_COMMA, 1) == 0)
     {
         printf("Comma found at %d\n", index);
     }

     ptr = strstr(ptr, JSON_DQUOTES);
     index = ptr-json;
     if (strncmp(ptr++, JSON_DQUOTES, 1) == 0)
     {
         printf("Open double quotes found at %d\n", index);
     }


    // printf("%d\n", index);

    //Manual parsing
    //"id":1
    o1k1.kt = VT_STR;
    o1k1.kp = json + 2;
    o1k1.klen = 2;
    o1k1.vt = VT_U8;
    o1k1.vp = json + 2;
    o1k1.vlen = 1;
    o1k1.next = &o1k2;
    o1k1.child = NULL;

    //"name"
    o1k2.kt = VT_STR;
    o1k2.kp = json + 9;
    o1k2.klen = 4;
    o1k2.vt = VT_OBJ;
    o1k2.vp = NULL;
    o1k2.vlen = 0;
    o1k2.next = &o1k3;
    o1k2.child = &o2k1;

    //Nested object
    //"first":"Jose"
    o2k1.kt = VT_STR;
    o2k1.kp = json + 16;
    o2k1.klen = 4;
    o2k1.vt = VT_STR;
    o2k1.vp = json + 24; 
    o2k1.vlen = 5;
    o2k1.next = &o2k2;
    o2k1.child = NULL;

    //"last":"Doe"
    o2k2.kt = VT_STR;
    o2k2.kp = json + 16;
    o2k2.klen = 4;
    o2k2.vt = VT_STR;
    o2k2.vp = json + 16;
    o2k2.vlen = 5;
    o2k2.next = NULL;
    o2k2.child = NULL;
    
    //Previous object continuation
    //"some":"thing"
    o1k3.kt = VT_STR;
    o1k3.kp = json + 16;
    o1k3.klen = 4;
    o1k3.vt = VT_STR;
    o1k3.vp = json + 16;
    o1k3.vlen = 5;
    o1k3.next = NULL;
    o1k3.child = NULL;

    PAIR *jsonArr[] = {&o1k1, &o1k2, &o2k1, &o2k2, &o1k3};

    printf("kt:     %d\n", sizeof(o1k3.kt));
    printf("kp:     %d\n", sizeof(o1k3.kp));
    printf("klen:   %d\n", sizeof(o1k3.klen));
    printf("vt:     %d\n", sizeof(o1k3.vt));
    printf("vp:     %d\n", sizeof(o1k3.vp));
    printf("vlen:   %d\n", sizeof(o1k3.vlen));
    printf("next:   %d\n", sizeof(o1k3.next));
    printf("child:  %d\n", sizeof(o1k3.child));

    printf("Total size: %d\n", sizeof(o1k3));
    printf("Total size json: %d\n", sizeof(jsonArr));
    // printf("%x\n", o1k3.kp);
    // PRINT_OPAQUE_STRUCT(&o1k3);
    printf("Json: %d\n", json);
    //Reconstruction of JSON from data structure
    // printf("{\"%s", o1k1);

    return 0;
}
