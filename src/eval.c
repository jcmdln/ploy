#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ploy.h>

Object *
Eval(Object *object)
{
	if (!object) return Error("Eval: object is NULL");

	Object *head = object;
	return head;
}
