typedef union  {
	int pos;
	int ival;
	string sval;
	} YYSTYPE;
extern YYSTYPE yylval;


#define ID 257
#define STRING 258
#define INT 259
#define ARRAY  260
#define IF 261
#define THEN  262
#define ELSE 263
#define WHILE 264
#define FOR 265
#define TO 266
#define DO 267
#define LET 268
#define IN  269
#define END 270
#define OF 271
#define BREAK 272
#define NIL 273
#define FUNCTION 274
#define VAR 275
#define TYPE 276
#define COMMA 277
#define COLON 278
#define SEMICOLON 279
#define LPARENTHESIS 280
#define RPARENTHESIS 281
#define LBRACKET 282
#define RBRACKET 283
#define LBRACE 284
#define RBRACE 285
#define DOT 286
#define PLUS 287
#define MINUS 288
#define TIMES 289
#define DIVIDE 290
#define EQ 291
#define NEQ 292
#define LT 293
#define LE 294
#define GT 295
#define GE 296
#define AND 297
#define OR 298
#define ASSIGN 299