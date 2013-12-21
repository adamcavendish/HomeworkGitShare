#pragma once

namespace PL0 {

enum Token {
	tk_eof = -1000,
	tk_linebreak,

	tk_begin = 1000,
	tk_call,
	tk_const,
	tk_do,
	tk_end,
	tk_if,
	tk_odd,
	tk_procedure,
	tk_read,
	tk_then,
	tk_var,
	tk_while,
	tk_write,

	tk_identifier = 2000,

	tk_number = 3000,

	tk_plus = 4000,
	tk_minus,
	tk_multiply,
	tk_divide,
	tk_equal,
	tk_notequal,
	tk_less,
	tk_lessequal,
	tk_greater,
	tk_greaterequal,
	tk_assign,

	tk_lparenthesis = 5000,
	tk_rparenthesis,
	tk_comma,
	tk_semicolon,
	tk_period
};

}//namespace PL0

