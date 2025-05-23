
#define DEBUG_PARSER 0

#define SUCCESS_WRITECSV 1
#define ERROR_WRITECSV 0

struct csvDoc{

    char **content;
    int contentsCount;

    struct csvDoc* next;
};

struct csvDoc *parseCsvFile(const char *fileName);
void getContentFromFile(char *line,struct csvDoc *doc);
void revisaLoParseado(struct csvDoc *result);
unsigned char writeCsvFile(const char* fileName,struct csvDoc *doc );

