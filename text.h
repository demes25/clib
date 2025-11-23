/* Demetre Seturidze
 * Library
 * Text
 * [Header]
 */


#ifndef TEXT
#define TEXT

#include"./string.h"

#define buffer_size 100

#define init_text_size 30

#define max_write_line 10000


// this represents a full line of text from some file
// i.e. loads everything until it reaches a '\n', '\0', or EOF
typedef struct StringLine {
    nat len;
    nat size;
    String** line;

    boolean isFinalLine;

    nat refs;
} StringLine;


// back-end ("behind the scenes") functions

StringLine* bts__newStringLine();

void bts__resizeStringLine(StringLine* strL);
void bts__stringLineAppend(StringLine* strL, String* s);

void bts__readLine(StringLine* empty, FILE* f);
void bts__writeLine(FILE* f, StringLine* strL);


// front-end functions

void print_StringLine(StringLine* strL);
void println_StringLine(StringLine* strL);

void deleteLine(StringLine* strL);

void skipLine(FILE* f);
StringLine* readLine(FILE* f);
void writeLine(FILE* f, StringLine* strL);



// this represents a full file
// i.e, reads the entire file from beginning to end.
typedef struct Text {
    nat len;
    nat size;
    StringLine** lines;
    
    nat refs;
} Text;


// back-end ("behind the scenes") functions

void bts__wipeText(Text* t);
void bts__deleteText(Text* t);
Text* bts__emptyText();
void bts__initText(Text* t);

void bts__resizeText(Text* t);
void bts__textAppend(Text* t, StringLine* s);

boolean bts__readFile(Text* empty, cstr filename);


// front-end functions

void print_Text(Text* t);
void println_Text(Text* t);

void deleteText(Text* t);
Text* newText();

Text* readFile(cstr filename);
void writeFile(cstr filename, Text* t);


#endif