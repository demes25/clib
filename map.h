/* Demetre Seturidze
 * Library
 * Maps
 * [Header]
 */

#ifndef MAP
#define MAP

#include"./string.h"

#define map_size 0x100

// MapNodes are behind the scenes 

typedef struct bts__MapNode{
    struct bts__MapNode* next;

    String* key;
    nat val;
} bts__MapNode;

static void bts__print_MapNode(bts__MapNode* mn);
static void bts__deleteMapNode(bts__MapNode* mn);
static bts__MapNode* bts__newMapNode(String* key, nat val);



typedef struct Map {
    bts__MapNode* entries[map_size];
    nat size;

    nat indices[map_size];
    nat usedIndices;

    nat refs;
} Map;

// back-end ("behind the scenes") functions

Map* bts__emptyMap();
void bts__initMap(Map* m);

bts__MapNode* bts__getNode(Map* m, String* key);
bts__MapNode* bts__getNode_cstr(Map* m, cstr key);


// front-end functions 

nat getVal(Map* m, String* key);
nat getVal_cstr(Map* m, cstr key);
boolean setVal(Map* m, String* key, nat val);


boolean defMapEntry(Map* m, String* key, nat val);
boolean defMapEntry_cstr(Map* m, cstr key, nat val);

void print_Map(Map* m);
void println_Map(Map* m);

void deleteMap(Map* m);
Map* newMap();



#endif