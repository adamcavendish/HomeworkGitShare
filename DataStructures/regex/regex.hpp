#pragma once

#include <cctype>

/**

^			beginning of the string
$			end of the string
.			match any character, except for '\n'
*			0 or more times
+			1 or more times
?			0 or 1
/			escape character

/d			any digit
/D			except digits
/s			any space
/S			except space
/w			any alpha/digit/'_'
/W			except alpha/digit/'_'

*/

inline int matchdot(const char * regex, const char * text);

int match(const char * regex, const char * text);
int matchhere(const char * regex, const char * text);
int matchstar(const char pat, const char * regex, const char * text);
int matchslash(const char * regex, const char * text);

/**
 * match: search for regular expression anywhere in text
 */
int match(const char * regex, const char * text)
{
	if(regex[0] == '^')
		return matchhere(regex + 1, text);
	do {
		// must look even if string is empty, eg: '^$'
		if(matchhere(regex, text))
			return 1;
	} while(*text++ != '\0');
	return 0;
}//match

inline int matchdot(const char * regex, const char * text)
{
	return (*regex == '.' && *text != '\n');
}//matchdot(regex, text)

/**
 * matchhere: search for regex at beginning of text
 */
int matchhere(const char * regex, const char * text)
{
	// regex is empty --- a pattern is found
	if(regex[0] == '\0')
		return 1;
	if(regex[0] == '/')
		return matchslash(regex + 1, text);
	if(regex[1] == '*')
		return matchstar(regex[0], regex + 2, text);
	if(regex[1] == '+')
		return (regex[0] == *text) ?
			matchstar(regex[0], regex + 2, text) : 0;
	if(regex[1] == '?')
		return matchhere(regex + 2, text + 1);
	if(regex[0] == '$' && regex[1] == '\0')
		return (*text == '\0');
	if(*text != '\0' && (matchdot(regex, text) || *regex == *text))
		return matchhere(regex + 1, text + 1);
	return 0;
}//matchhere(regex, text)

int matchslash(const char * regex, const char * text)
{
	switch(*regex) {
	case 'd':
		if(isdigit(*text))
			return matchhere(regex + 1, text + 1);
		return 0;
	case 'D':
		if(!isdigit(*text))
			return matchhere(regex + 1, text + 1);
		return 0;
	case 's':
		if(isspace(*text))
			return matchhere(regex + 1, text + 1);
		return 0;
	case 'S':
		if(!isspace(*text))
			return matchhere(regex + 1, text + 1);
		return 0;
	case 'w':
		if(isalnum(*text) || *text == '_')
			return matchhere(regex + 1, text + 1);
		return 0;
	case 'W':
		if(!isalnum(*text) && *text != '_')
			return matchhere(regex + 1, text + 1);
		return 0;
	default:
		if(*regex == *text)
			return matchhere(regex + 1, text + 1);
		return 0;
	}//switch
	return 0;
}//matchslash(regex, text)

int matchstar(const char pat, const char * regex, const char * text)
{
	do {
		if(matchhere(regex, text))
			return 1;
	} while(*text != '\0' &&
		(*text++ == pat ||
		(pat == '.' && *text != '\n')));

	return 0;
}//matchstar(pattern, regex, text)

