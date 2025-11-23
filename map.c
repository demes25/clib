/* Demetre Seturidze
 * Library
 * Maps
 */

#include"./map.h"

static void bts__print_MapNode(bts__MapNode* mn) {
    putchar('[');
    print_String(mn -> key);
    printf(" : %d", mn -> val);
    putchar(']');
}

static void bts__deleteMapNode(bts__MapNode* mn) {
    deleteString(mn -> key);
    if (mn -> next) bts__deleteMapNode(mn -> next);
    free(mn);
}

static bts__MapNode* bts__newMapNode(String* key, nat val) {
    bts__MapNode* result = (bts__MapNode*)malloc(sizeof(bts__MapNode));

    result -> next = 0;
    result -> key = key; key -> refs++;
    result -> val = val;

    return result;
}




Map* bts__emptyMap() {
    return (Map*)malloc(sizeof(Map));
}

void bts__initMap(Map* m) {
    for (nat i = 0; i < map_size; i++)
        m -> entries[i] = 0;
    
    m -> size = 0;
    m -> usedIndices = 0;

    m -> refs = 0;
}


bts__MapNode* bts__getNode(Map* m, String* key) {
    nat index = key -> hash % map_size;

    if (m -> entries[index]) {
        bts__MapNode* current = m -> entries[index];

        while(!equalStrings(current -> key, key)){
            // nat_max is returned if the given key cannot be found
            if (!current -> next) return null;
            else current = current -> next;
        }

        return current;
    } else return null;
}

bts__MapNode* bts__getNode_cstr(Map* m, cstr key) {
    nat index = init_hash;

    for (nat i = 0; key[i]; i++){
        index ^= key[i];
        index *= hash_prime;
        index &= nat_max;
    }

    index %= map_size;


    if (m -> entries[index]) {
        bts__MapNode* current = m -> entries[index];

        while(!equalStrings_cstr(current -> key, key)){
            if (!current -> next) return null;
            else current = current -> next;
        }

        return current;
    } else return null;
}



nat getVal(Map* m, String* key) {
    bts__MapNode* keyNode = bts__getNode(m, key);
    // returns nat_max if the given key cannot be found
    return keyNode ? keyNode -> val : nat_max;
}

nat getVal_cstr(Map* m, cstr key) {
    bts__MapNode* keyNode = bts__getNode_cstr(m, key);
    return keyNode ? keyNode -> val : nat_max;
}

boolean setVal(Map* m, String* key, nat val) {
    bts__MapNode* keyNode = bts__getNode(m, key);
    if (keyNode){
        keyNode -> val = val;
        return True;
    // returns False if the given key cannot be found
    } else return False;
}


boolean defMapEntry(Map* m, String* key, nat val) {
    // nat_max cannot be used here, as it is used to signify the lack of 
    // a corresponding value in the getVal method.
    if (val == nat_max) return False;

    nat index = key -> hash % map_size;

    if (m -> entries[index]){
        bts__MapNode* current = m -> entries[index];

        while(current -> next)
            if (equalStrings(current -> key, key)) return False;
            else current = current -> next;
        
        current -> next = bts__newMapNode(key, val);
    } else {
        m -> entries[index] = bts__newMapNode(key, val);
        m -> indices[m -> usedIndices++] = index;
    }

    m -> size++;
    return True;
}

boolean defMapEntry_cstr(Map* m, cstr key, nat val) {
    return defMapEntry(m, newString_cstr(key), val);
}


void print_Map(Map* m) {
    print_char('{');
    for (nat i = 0; i < m -> usedIndices; i++)
        for (bts__MapNode* mn = m -> entries[m -> indices[i]]; mn; mn = mn -> next)
            bts__print_MapNode(mn);
    print_char('}');
}

void println_Map(Map* m) {
    print_Map(m); println();
}


void deleteMap(Map* m) {
    if (m && !(m -> refs && --(m -> refs))) {
        for (nat i = 0; i < m -> usedIndices; i++)
            bts__deleteMapNode(m -> entries[m -> indices[i]]);
        
        free(m);
    }
}

Map* newMap() {
    Map* result = bts__emptyMap();
    bts__initMap(result);
    return result;
}


