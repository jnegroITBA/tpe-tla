#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <string.h>
#include <stdlib.h>

/**
 * Implementación de "flex-rules.h".
 */

token IntegerPatternAction(const char * lexeme) {
	LogDebug("IntegerPatternAction: '%s'.", lexeme);
    yylval.integer = atoi(lexeme);
	return INTEGER;
}

token BooleanPatternAction(const char * lexeme) {
	LogDebug("IntegerPatternAction: '%s'.", lexeme);
	if (strcmp(lexeme, "true") == 0) {
		yylval.boolean = true;
	} else {
		yylval.boolean = false;
	}
	return BOOLEAN;
}

token TonePatternAction(const char * lexeme) {
	LogDebug("TonePatternAction: '%s'.", lexeme);
	int index = 0;
	yylval.tone.name = lexeme[index++];
    if (lexeme[index] == '#' || lexeme[index] == 'b')
        yylval.tone.type = lexeme[index++];
    else
        yylval.tone.type = '0';
	yylval.tone.octave = lexeme[index];
	return TONE;
}

enum rythm stor(const char * lexeme) {
	if (strcmp(lexeme, "whole") == 0) {
		return WHOLE;
	} else if (strcmp(lexeme, "half") == 0) {
		return HALF;
	}  else if (strcmp(lexeme, "quarter") == 0) {
		return QUARTER;
	}  else if (strcmp(lexeme, "eight") == 0) {
		return EIGHTH;
	}  else if (strcmp(lexeme, "sixteenth") == 0) {
		return SIXTEENTH;
	}  else if (strcmp(lexeme, "thirtySecond") == 0) {
		return THIRTYSECOND;
	} else if (strcmp(lexeme, "sixtyFourth") == 0) {
		return SIXTYFOURTH;
	}
}

token RythmPatternAction(const char * lexeme) {
	LogDebug("RythmPatternAction: '%s'.", lexeme);

	yylval.rythm = stor(lexeme);
	return RYTHM;
}

void IgnoredPatternAction(const char * lexeme) {
	LogDebug("IgnoredPatternAction: '%s'.", lexeme);
}

void IgnoredCommentPatternAction(const char * lexeme) {
	LogDebug("IgnoredCommentPatternAction: '%s'.", lexeme);
}

token StartComment() {
	LogDebug("Start_Comment");
	return START_COMMENT;
}

token EndComment() {
	LogDebug("End_Comment");
	return END_COMMENT;
}

token StartString() {
	LogDebug("Start_String");
	return START_STRING;
}

token EndString() {
	LogDebug("End_String");
	return END_STRING;
}

token UnknownPatternAction(const char * lexeme) {
	LogDebug("UnknownPatternAction: '%s'.", lexeme);
	return YYUNDEF;
}

token VariablePatternAction(char * lexeme) {
	LogDebug("VariablePatternAction: '%s'.", lexeme);
    char * toRet = (char*) malloc((yyleng + 1)*sizeof(char));
    strncpy(toRet, lexeme, yyleng);
	toRet[yyleng] = '\0';
	yylval.string = toRet;
	return VARIABLE;
}

token PlusOperatorPatternAction(const char * lexeme){
	LogDebug("PlusOperatorPatternAction: '%s'.", lexeme);
	yylval.token = PLUS;
	return PLUS;
}

token SubOperatorPatternAction(const char * lexeme){
	LogDebug("SubOperatorPatternAction: '%s'.", lexeme);
	yylval.token = SUB;
	return SUB;
}

token MulOperatorPatternAction(const char * lexeme){
	LogDebug("MulOperatorPatternAction: '%s'.", lexeme);
	yylval.token = MUL;
	return MUL;
}

token CharPatternAction(const char * lexeme) {
	LogDebug("CharPatternAction: '%s'.", lexeme);
	yylval.c = *lexeme;
	return CHAR;
}