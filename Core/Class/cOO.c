#include "cOO.h"

object* new(const class* class, ...) {
	object* object = malloc(class->size);

	if (class->ctor) {												// if class has a constructor, use the given arguments
		va_list args;													// initialize variable argument list
		va_start(args, class);										// start variable argument list
		object = class->ctor(class, object, &args);	// call the class constructor
		va_end(args);													// end variable argument list
		CONSTRUCTOR_DEBUG(class, object)
	}
	return object;
}
void delete(object* obj) {
	const class* class = obj->class;
	if (class->dtor != NULL) {
		class->dtor(obj);
	}
	DESTRUCTOR_DEBUG(class, obj);
	freeObject(obj);
	obj = 0;
}
