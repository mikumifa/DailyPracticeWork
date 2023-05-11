lexer grammar myLexer;
APPEND : 'append';
EXIT: 'exit';
LIST: 'list';
PRINT : 'print';
PRINTLENGTH : 'printlength';
PRINTWORDS : 'printwords';
PRINTWORDCOUNT : 'printwordcount';
REVERSE : 'reverse';
SET:'set';
CONSTANT: [ \t\n]+ ->skip;
END:';';
PLUS : '+';
ID: [a-zA-Z][a-zA-Z0-9]*;
LITERAL : '"' ( ~["\\] | '\\' . )* '"' {
                  String unquoted = getText().substring(1, getText().length() - 1);

                  setText(unquoted);
                }
              ;