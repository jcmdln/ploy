#include <ploy.h>

void eval_nil(void);
void eval_boolean(void);
void eval_error(void);
void eval_lambda(void);
void eval_list(void);
void eval_number(void);
void eval_string(void);
void eval_symbol(void);

Ploy *
PloyEval(Ploy *object)
{
	if (!object) return PloyError("Eval: object is NULL");

	Ploy *head = object;

	return head;
}
