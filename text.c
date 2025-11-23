/* Demetre Seturidze
 * Library
 * Text
 */


#include"./text.h"

StringLine* bts__newStringLine() {
    StringLine* result = (StringLine*)malloc(sizeof(StringLine));

    result -> len = 0;
    result -> size = init_text_size;
    result -> line = (String**)malloc(init_text_size * sizeof(String*));

    result -> isFinalLine = False;

    result -> refs = 0;

    return result;
}


void bts__resizeStringLine(StringLine* strL) {
    strL -> size *= resize_ratio;
    String** newStrPtr = (String**)malloc(strL -> size * sizeof(String*));

    move(newStrPtr, strL -> line, strL -> len * sizeof(String*));

    strL -> line = newStrPtr;
}

void bts__stringLineAppend(StringLine* strL, String* s) {
    if (strL -> len >= strL -> size) bts__resizeStringLine(strL);

    strL -> line[strL -> len++] = s;
    s -> refs++;
}


void print_StringLine(StringLine* strL) {
    for (nat i = 0; i < strL -> len; i++)
        print_String(strL -> line[i]);
}

void println_StringLine(StringLine* strL) {
    print_StringLine(strL); println();
}


void deleteLine(StringLine* strL) {
    if (!(strL -> refs && --(strL -> refs))) {
        for (nat i = 0; i < strL -> len; i++)
            deleteString(strL -> line[i]);
        free(strL -> line);
        free(strL);
    }
}


void bts__readLine(StringLine* empty, FILE* f) {
    char buffer[buffer_size];
    nat lastInBuffer = buffer_size - 1;

    String* nextEntry = newString();

    boolean finish = False;
    
    while(!finish) {

        if (!fgets(buffer, 100, f)) {
            if (nextEntry -> len != 0)
                bts__stringLineAppend(empty, nextEntry);
            finish = True;
            empty -> isFinalLine = True;
            break;
        }

        for(nat k = 0; k < lastInBuffer; k++){
            if (buffer[k] == null){
                if (nextEntry -> len != 0)
                    bts__stringLineAppend(empty, nextEntry);
                finish = True;
                empty -> isFinalLine = True;
                break;
            } else if (buffer[k] == new_line) {
                if (nextEntry -> len != 0)
                    bts__stringLineAppend(empty, nextEntry);
                finish = True;
                break;
            } else if (buffer[k] == space || is_punct(buffer[k])){
                if (nextEntry -> len != 0){
                    bts__stringLineAppend(empty, nextEntry);
                    nextEntry = newString();
                } 
                bts__stringLineAppend(empty, newString_char(buffer[k]));
            } else stringAppend(nextEntry, buffer[k]);
        }
    }

    if (empty -> len != 0 && nextEntry != empty -> line[empty -> len - 1]) deleteString(nextEntry);
}

void bts__writeLine(FILE* f, StringLine* strL) {
    for(nat i = 0; i < strL -> len; i++)
        fwrite(strL -> line[i] -> str, sizeof(char), strL -> line[i] -> len, f);
}


void skipLine(FILE* f) {
    char buffer[buffer_size];
    nat lastInBuffer = buffer_size - 1;

    boolean finish = False;
    
    while(!finish) {

        if (!fgets(buffer, 100, f)) {
            finish = True;
            break;
        }

        for(nat k = 0; k < lastInBuffer; k++){
            if (buffer[k] == null || buffer[k] == new_line){
                finish = True;
                break;
            }
        }
    }
}

StringLine* readLine(FILE* f) {
    StringLine* result = bts__newStringLine();
    bts__readLine(result, f);
    return result;
}

void writeLine(FILE* f, StringLine* strL) {
    bts__writeLine(f, strL);
    if (!(strL -> isFinalLine)) fputc('\n', f);
}





void bts__wipeText(Text* t) {
    for (nat i = 0; i < t -> len; i++)
        deleteLine(t -> lines[i]);
    free(t -> lines);
}

void bts__deleteText(Text* t) {
    bts__wipeText(t);
    free(t);
}

Text* bts__emptyText() {
    return (Text*)malloc(sizeof(Text));
}

void bts__initText(Text* t) {
    t -> len = 0;
    t -> size = init_text_size;
    t -> lines = (StringLine**)malloc(init_text_size * sizeof(StringLine*));

    t -> refs = 0;
}


void bts__resizeText(Text* t) {
    t -> size *= resize_ratio;
    StringLine** newStrLPtr = (StringLine**)malloc(t -> size * sizeof(StringLine*));

    move(newStrLPtr, t -> lines, t -> len * sizeof(StringLine*));

    t -> lines = newStrLPtr;
}

void bts__textAppend(Text* t, StringLine* s) {
    if (t -> len >= t -> size) bts__resizeText(t);

    t -> lines[t -> len++] = s;
    s -> refs++;
}


void print_Text(Text* t) {
    nat lastEntry = t -> len - 1;
    for (nat i = 0; i < lastEntry; i++)
        println_StringLine(t -> lines[i]);
    print_StringLine(t -> lines[lastEntry]);
}

void println_Text(Text* t) {
    print_Text(t); println();
}



void deleteText(Text* t) {
    if (t && !(t -> refs && --(t -> refs)))
        bts__deleteText(t);
}

Text* newText() {
    Text* result = bts__emptyText();
    bts__initText(result);
    return result;
}


boolean bts__readFile(Text* empty, cstr filename) {
    FILE* f = fopen(filename, "r");
    
    if (!f) return False;

    StringLine* s;

    do {
        s = readLine(f);
        bts__textAppend(empty, s);
    } while(!(s -> isFinalLine));

    fclose(f);

    return True;
}

Text* readFile(cstr filename) {
    Text* result = newText();
    if (bts__readFile(result, filename))
        return result;
    else {deleteText(result); return null;}
}

void writeFile(cstr filename, Text* t) {
    FILE* f = fopen(filename, "w");

    for(nat i = 0; i < t -> len; i++)
        writeLine(f, t -> lines[i]);

    fclose(f);
}

