#include <stdlib.h>
#include <string.h>

#include <brandon/tok.h>
#include <brandon/vvector.h>

#include "as.h"
// Preprocessor for the assembler

// turn raw source code into a vector of lines with comments filtered out
static Line * newLine( int lineNum, const char * code )
{
    Line * line = (Line *) malloc( sizeof(Line) );
    line->number = lineNum;
    line->code = strdup(code);
    return line;
}

static void delLine( Line * line )
{
    free( line->code );
    free( line );
}

#define INITIAL_BUFFER 128
VVector * processSource( const char * src )
{
    // split into lines
    Tokenizer * tok = Tokenizer_new( src, "\n" );
    int numTokens = Tokenizer_countTokens( tok );
    const char * const * rawLines = Tokenizer_tokens( tok );

    // heuristic: 1/4th is empty meaningless lines
    VVector * output = VVector_new_reg( numTokens*3/4, delLine );

    char * buffer = (char *) malloc( INITIAL_BUFFER );
    for (int i = 0; i < numTokens; ++i)
    {
        const char * line = rawLines[i];
        int len = strlen( line );

        // scan for non-whitespace; end at comment
        int pos = 0;
        char c;
        int hasContent = 0;
        for (pos = 0; pos < len; ++pos)
        {
            char c = line[pos];
            if (c == ';')
            {
                break;
            }

            // if a non-space or non-tab is found, content is found
            if ( !hasContent && c != ' ' && c != '\t')
            {
                hasContent = 1;
            }
        }

        // if there is meaningful content, copy it
        if (hasContent)
        {
            int contentLen = pos;
            buffer =  (char *) realloc( buffer, contentLen+1 );
            strncpy( buffer, line, contentLen );
            buffer[contentLen] = '\0'; // add the null term

            // add to our lines
            VVector_push( output, newLine( i, buffer ) );
        }
    }

    free( buffer );
    Tokenizer_delete( tok );
    return output;
}
