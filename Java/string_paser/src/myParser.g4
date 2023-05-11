parser grammar myParser;

options {
    tokenVocab = myLexer;
}

program
    : statement*
    ;
statement
    : APPEND ID expression END
    | LIST END
    | EXIT END
    | PRINT expression END
    | PRINTLENGTH expression END
    | PRINTWORDS expression END
    | PRINTWORDCOUNT expression END
    | SET ID expression END
    | REVERSE ID END
    ;
expression
    : value (PLUS value)*
    ;
value
    :ID|LITERAL
    ;