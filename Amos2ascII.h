
// enums are used to format text, by know the last command we know if need a space or not between,

enum
{
	is_newline = 0,
	is_command,
	is_symbol,
	is_number,
	is_string,
	is_var,
	is_procedure,
};

extern int token_is ;
extern int last_token_is ;
