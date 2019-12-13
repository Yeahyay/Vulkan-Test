#ifndef OOC_H
#define OOC_H

// #include <main.h>

// #include <stdio.h>
#include <stdlib.h>
// #include <string.h>
#include <stdarg.h>
// #include <assert.h>
#include <ctype.h>
#include <stdbool.h>
// #include <stddef.h>

typedef struct _class class;
typedef struct _object object;

struct _class {
	const class* super;
	char* name;
	int size;
	void* (*ctor) (const class* class, object* self, va_list* app);	// constructor with variable initialization
	void* (*init) (object* self);													// initializer
	void (*dtor) (object* self);													// destructor
};

struct _object {
	// void* data; // points to data
	const class* class; // points to actual class; can be any class
};

object* new(const class* class, ...);
void delete(object*);
// size_t sizeOf(object*);


#define INIT_CLASS_VERBOSE(CLASS, SUPER, CTOR, INIT, DTOR)	\
	const class CLASS = {	\
		(SUPER),	\
		#CLASS,	\
		sizeof(struct CLASS),	\
		(CTOR),	\
		(INIT),	\
		(DTOR)	\
	}

#define INIT_CLASS(CLASS, SUPER)	\
	const class CLASS = {	\
		(SUPER),	\
		#CLASS,	\
		sizeof(struct CLASS),	\
		&(CLASS##_ctor),	\
		NULL, /*&(CLASS##_init),	*/\
		&(CLASS##_dtor),	\
	}

#define DEFINE_CLASS(CLASS/*, SUPER*/, MEMBERS)	\
	struct CLASS {	\
		struct CLASS* object;	\
		/*SUPER;*/	\
		MEMBERS	\
	};

#define DECLARE_CLASS_OBJECT(CLASS)	\
	const class CLASS

#define DEFINE_CLASS_INITIALIZER(CLASS, INITIALIZERS)	\
	static void* CLASS##_init(object* obj) {	\
		struct CLASS* self = (struct CLASS*) obj;	\
		INITIALIZERS	\
		return self;	\
	}

#define INITIALIZER(MEMBER, VALUE)	\
	self->MEMBER = VALUE

#define DEFINE_CLASS_CONSTRUCTOR(CLASS/*, SUPER*/, CONSTRUCTORS)	\
	static void* CLASS##_ctor(const class* class, object* _object, va_list* args) {	\
		struct CLASS* object = (struct CLASS*) _object;	\
		if (class->init) {	\
			/*object = class->init(_object);	*/\
		}	\
		/* CONSTRUCTOR SPECIFIC */	\
		/*SUPER*/	\
		CONSTRUCTORS	\
		object->object = object;	\
		_object->class = class;	\
		return object;	\
	}

#define DEFINE_CLASS_METHOD(CLASS, TYPE, NAME, ARGS, FUNCTION)	\
	static TYPE NAME(object* object, ARGS) {	\
		struct CLASS* self = (struct CLASS*) object/*->data*/;	\
		FUNCTION	\
	}

#define METHOD_ARGS(...)	\
	__VA_ARGS__

#define METHOD(CLASS, OBJECT, NAME, ...)	\
	((struct CLASS*) OBJECT/*->data*/)->NAME(OBJECT/*->data*/, ##__VA_ARGS__)
	// ((struct CLASS*) (OBJECT)->data)->NAME(OBJECT->self, ##__VA_ARGS__)

#define METHOD_PRIVATE(CLASS, OBJECT, NAME, ...)	\
	NAME(OBJECT/*->data*/, ##__VA_ARGS__)
	// ((struct CLASS*) (OBJECT)->data)->NAME(OBJECT->self, ##__VA_ARGS__)

#define OBJECT_DATA_ALL(CLASS, OBJECT)	\
	(struct CLASS*) (OBJECT)/*->data*/

#define OBJECT_DATA(CLASS, OBJECT, MEMBER)	\
	(((struct CLASS*) OBJECT/*->data*/)->MEMBER)

#define METHOD_PROTOTYPE(RETURN, NAME, ...)	\
	RETURN (*NAME)(object* object, ##__VA_ARGS__)
// void (*set)();// FUNCTION_PROTOTYPE(vector2, void, set, double, double);

#define GENERIC_PROTOTYPE(GENERIC_TYPE)	\
	_GENERIC()

#define GENERIC_INIT_ARG(TYPE)	\
	(TYPE){0};

#define CONSTRUCTOR(MEMBER, TYPE)	\
	object->MEMBER = va_arg(*args, TYPE)//object->MEMBER ? object->MEMBER : va_arg(*args, TYPE);

#define CONSTRUCTOR_STATIC(MEMBER, VALUE)	\
	object->MEMBER = (VALUE)//object->MEMBER ? object->MEMBER : va_arg(*args, TYPE);

#define CONSTRUCTOR_STRING(NAME)	\
	char* NAME = va_arg(*args, char*);	\
	object->NAME = malloc(strlen(NAME));	\
	object->NAME = NAME

#define CONSTRUCTOR_FUNCTION(NAME/*, TYPE, ARGS*/)	\
	object->NAME = /*(TYPE (*)(ARGS))*/ va_arg(*args, void*)

#define SUPER	\
	printf("CONSTRUCTOR FROM SUPER\n");	\
	class->super->ctor(NULL, _object, args);

#define DEFINE_CLASS_DESTRUCTOR(CLASS, DESTRUCTORS)	\
	static void CLASS##_dtor(object* obj) {	\
		struct CLASS* self = (struct CLASS*) obj;	\
		DESTRUCTORS	\
	}

#define DESTRUCTOR(VALUE)	\
	free(self->VALUE);	\
	self->VALUE = 0;

#define DESTRUCTOR_OBJECT(OBJECT)	\
	delete(self->OBJECT);
	// free(self->VALUE);
	// self->VALUE = 0;

	size_t MEM_USED;
	bool __IS_OBJECT__;


	#if defined(DEBUG_MEM)
		#define malloc(SIZE)	\
			malloc(SIZE);	\
			MEM_USED += (size_t) SIZE;	\
			printf("ALLOCATED %I64d BYTES AT LINE %d\n", (size_t) SIZE, __LINE__);

		#define free(OBJECT)	\
			MEM_USED -= sizeof(OBJECT);	\
			free(OBJECT);	\
			if (!__IS_OBJECT__)	\
				printf("FREED %d BYTES AT LINE %d\n", (int) sizeof(OBJECT), __LINE__)

		#define freeObject(OBJECT)	\
			MEM_USED -= OBJECT->class->size;	\
			printf("FREED %d BYTES AT LINE %d\n", OBJECT->class->size, __LINE__);	\
			__IS_OBJECT__ = true;	\
			free(OBJECT);	\
			__IS_OBJECT__ = false
	#else
		#define freeObject(OBJECT)	\
			free(OBJECT)
	#endif

	#define GET_MEM_USED	\
		printf("%I64d BYTES OF MEMORY ALLOCATED\n", MEM_USED);

// DEBUG
#if defined(DEBUG)
	#if defined(CLASS_DEBUG)
		#define CONSTRUCTOR_DEBUG(CLASS, OBJECT)\
			printf("CONSTRUCTED\tOBJECT OF CLASS (%s) NAME (%s)\n", (CLASS)->name, (OBJECT)->name);
		#define DESTRUCTOR_DEBUG(CLASS, OBJECT)\
			printf("DESTROYED\tOBJECT OF OBJECT (%s) NAME (%s)\n", (CLASS)->name, (OBJECT)->name);
		#define INSTANTIATOR_DEBUG(CLASS, OBJECT)\
			printf("INSTANTIATED\tOBJECT OF CLASS (%s) NAME (%s)\n", (CLASS)->name, (OBJECT)->name);
	#elif defined(CLASS_DEBUG_VERBOSE)
		#define CONSTRUCTOR_DEBUG(CLASS, OBJECT)\
			printf("CONSTRUCTED\tOBJECT OF CLASS (%s) SIZE (%d): (0x%p) NAME (%s)\n", (CLASS)->name, (CLASS)->size, (OBJECT), (CLASS)->name);
		#define DESTRUCTOR_DEBUG(CLASS, OBJECT)\
			printf("DESTROYED\tOBJECT OF CLASS (%s) SIZE (%d): (0x%p) NAME (%s)\n", (CLASS)->name, (CLASS)->size, (OBJECT), (CLASS)->name);
		#define INSTANTIATOR_DEBUG(CLASS, OBJECT)\
			printf("INSTANTIATED\tOBJECT OF CLASS (%s) SIZE (%d): (0x%p) NAME (%s)\n", (CLASS)->name, (CLASS)->size, (OBJECT), (CLASS)->name);
	#endif
#else
	#define CONSTRUCTOR_DEBUG(CLASS_NAME, OBJECT)
	#define DESTRUCTOR_DEBUG(CLASS_NAME, OBJECT)
	#define INSTANTIATOR_DEBUG(CLASS_NAME, OBJECT)
#endif

// DEBUGGING
	/*
	#define DEBUG_VARARG(VARARGS, CLASS, FUNCTION)	\
		va_list VARARGS;	\
		va_start(VARARGS, CLASS);	\
		FUNCTION;	\
		va_end(VARARGS);

	#if defined(CLASS_DEBUG)
		#define CONSTRUCTOR_DEBUG(VARARGS, CLASS, OBJECT)\
			DEBUG_VARARG(VARARGS, CLASS,	\
				printf("CONSTRUCTED\tCLASS OBJECT (%s) NAME (%s)\n", CLASS->name, va_arg(VARARGS, const char*));	\
			)
		#define DESTRUCTOR_DEBUG(VARARGS, CLASS, OBJECT)\
			DEBUG_VARARG(VARARGS, CLASS,	\
				printf("DESTROYED\tCLASS OBJECT (%s) NAME (%s)\n", CLASS->name, va_arg(VARARGS, const char*));	\
			)
		#define INSTANTIATOR_DEBUG(VARARGS, CLASS, OBJECT)\
			DEBUG_VARARG(VARARGS, CLASS,	\
				printf("INSTANTIATED\tOBJECT OF CLASS (%s) NAME (%s)\n", CLASS->name, va_arg(VARARGS, const char*));	\
			)
	#elif defined(CLASS_DEBUG_VERBOSE)
		#define CONSTRUCTOR_DEBUG(VARARGS, CLASS, OBJECT)\
			DEBUG_VARARG(VARARGS, CLASS,	\
				printf("CONSTRUCTED\tCLASS OBJECT (%s) SIZE (%I64d): (0x%p) NAME (%s)\n", CLASS->name, CLASS->size, OBJECT, va_arg(VARARGS, const char*));	\
			)
		#define DESTRUCTOR_DEBUG(VARARGS, CLASS, OBJECT)\
			DEBUG_VARARG(VARARGS, CLASS,	\
				printf("DESTROYED\tCLASS OBJECT (%s) SIZE (%I64d): (0x%p) NAME (%s)\n", CLASS->name, CLASS->size, OBJECT, va_arg(VARARGS, const char*));	\
			)
		#define INSTANTIATOR_DEBUG(VARARGS, CLASS, OBJECT)\
			DEBUG_VARARG(VARARGS, CLASS,	\
				printf("INSTANTIATED\tOBJECT OF CLASS (%s) SIZE (%I64d): (0x%p) NAME (%s)\n", CLASS->name, CLASS->size, OBJECT, va_arg(VARARGS, const char*));	\
			)
	#else
		#define CONSTRUCTOR_DEBUG(VARARGS, CLASS, OBJECT)
		#define DESTRUCTOR_DEBUG(VARARGS, CLASS, OBJECT)
		#define INSTANTIATOR_DEBUG(VARARGS, CLASS, OBJECT)
	#endif
	*/
// DEBUGGING
/*
	#if defined(CLASS_DEBUG)
		#define CONSTRUCTOR_DEBUG(CLASS_NAME, OBJECT)\
			printf("CONSTRUCTED\tCLASS OBJECT (%s) NAME (%s)\n", #CLASS_NAME, OBJECT->name);
		#define DESTRUCTOR_DEBUG(CLASS_NAME, OBJECT)\
			printf("DESTROYED\tCLASS OBJECT (%s) NAME (%s)\n", #CLASS_NAME, OBJECT->name);
		#define INSTANTIATOR_DEBUG(CLASS_NAME, OBJECT)\
			printf("INSTANTIATED\tOBJECT OF CLASS (%s) NAME (%s)\n", #CLASS_NAME, OBJECT->name);
	#elif defined(CLASS_DEBUG_VERBOSE)
		#define CONSTRUCTOR_DEBUG(CLASS_NAME, OBJECT)\
			printf("CONSTRUCTED\tCLASS OBJECT (%s) SIZE (%I64d): (0x%p) NAME (%s)\n", #CLASS_NAME, sizeof(OBJECT), OBJECT, OBJECT->name);
		#define DESTRUCTOR_DEBUG(CLASS_NAME, OBJECT)\
			printf("DESTROYED\tCLASS OBJECT (%s) SIZE (%I64d): (0x%p) NAME (%s)\n", #CLASS_NAME, sizeof(OBJECT), OBJECT, OBJECT->name);
		#define INSTANTIATOR_DEBUG(CLASS_NAME, OBJECT)\
			printf("INSTANTIATED\tOBJECT OF CLASS (%s) SIZE(%I64d): (0x%p) NAME (%s)\n", #CLASS_NAME, sizeof(OBJECT), OBJECT, OBJECT->name);
	#else
		#define CONSTRUCTOR_DEBUG(CLASS_NAME, OBJECT)
		#define DESTRUCTOR_DEBUG(CLASS_NAME, OBJECT)
		#define INSTANTIATOR_DEBUG(CLASS_NAME, OBJECT)
	#endif
*/

#endif
