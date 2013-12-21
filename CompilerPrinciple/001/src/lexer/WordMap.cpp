#include <lexer/WordMap.hpp>

namespace PL0 {

WordMap::WordMap() :
	m_word_map({
			{ "begin",		Token::tk_begin			},
			{ "call",		Token::tk_call			},
			{ "const",		Token::tk_const			},
			{ "do",			Token::tk_do			},
			{ "end",		Token::tk_end			},
			{ "if",			Token::tk_if			},
			{ "odd",		Token::tk_odd			},
			{ "procedure",	Token::tk_procedure		},
			{ "read",		Token::tk_read			},
			{ "then",		Token::tk_then			},
			{ "var",		Token::tk_var			},
			{ "while",		Token::tk_while			},
			{ "write",		Token::tk_write			}
	}),
	m_operator_pool("+-*/=<>:(),;."),
	m_operator_map({
			{ "+",			{ Token::tk_plus,			priority(10)	}	},
			{ "-",			{ Token::tk_minus,			priority(10)	}	},
			{ "*",			{ Token::tk_multiply,		priority(20)	}	},
			{ "/",			{ Token::tk_divide,			priority(20)	}	},
			{ "=",			{ Token::tk_equal,			priority(10)	}	},
			{ "<>",			{ Token::tk_notequal,		priority(10)	}	},
			{ "<",			{ Token::tk_less,			priority(10)	}	},
			{ "<=",			{ Token::tk_lessequal,		priority(10)	}	},
			{ ">",			{ Token::tk_greater,		priority(10)	}	},
			{ ">=",			{ Token::tk_greaterequal,	priority(10)	}	},
			{ ":=",			{ Token::tk_assign,			priority(10)	}	},
			{ "(",			{ Token::tk_lparenthesis,	priority(10)	}	},
			{ ")",			{ Token::tk_rparenthesis,	priority(10)	}	},
			{ ",",			{ Token::tk_comma,			priority(10)	}	},
			{ ";",			{ Token::tk_semicolon,		priority(10)	}	},
			{ ".",			{ Token::tk_period,			priority(10)	}	},
	})
{}

WordMap::~WordMap()
{}

}//namespace PL0

