#ifndef __AS_H__
#define __AS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum AsmSyntax_enum
{
    AsmSyntax_patt,
    AsmSyntax_lccc
} AsmSyntax;

typedef struct Program_str
{
    VVector * localSymbols;     // symbols declared in this unit
    VVector * externalSymbols;  // symbols that are
    VVector * exportSymbols;
} Program;

typedef struct Symbol_str
{
} Symbol;

typedef struct Line_str
{
    int number;
    const char * code;    // filtered code
} Line;

typedef enum ParseError_enum
{
    ParseError_Okay,
} ParseError;

#ifdef __cplusplus
}
#endif

#endif//__AS_H__
