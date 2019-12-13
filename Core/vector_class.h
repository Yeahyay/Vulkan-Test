#ifndef VECTOR_CLASS_H
#define VECTOR_CLASS_H

#include <Core/Class/cOO.h>

#define GENERATE_VECTOR(TYPE, NAME)	\
	DEFINE_CLASS(NAME##_vector,	\
		TYPE* data;	\
		METHOD_PROTOTYPE(void, append, TYPE);	\
		METHOD_PROTOTYPE(void, remove, int);	\
		size_t threshhold;	\
		size_t size;	\
		size_t typeSize;	\
	)	\
	DEFINE_CLASS_METHOD(NAME##_vector, void, NAME##_vec_resize, METHOD_ARGS(float factor),	\
		size_t newSize = self->threshhold*factor;	\
		printf("RESIZED VECTOR FROM %I64d ELEMENTS TO %I64d ELEMENTS\n", self->threshhold, newSize);	\
		printf("RESIZED VECTOR FROM %.4lf mb TO %.4lf mb\n", \
			self->threshhold*self->typeSize/1048576.0, newSize*self->typeSize/1048576.0);	\
		self->threshhold = newSize;	\
		self->data = realloc(self->data, self->threshhold*self->typeSize);	\
	)	\
	DEFINE_CLASS_METHOD(NAME##_vector, void, NAME##_vec_append, METHOD_ARGS(TYPE data),	\
		self->size += 1;	\
		if (self->size > self->threshhold) {	\
			METHOD_PRIVATE(NAME##_vector, object, NAME##_vec_resize, 2);	\
		}	\
		self->data[self->size] = data;	\
	)	\
	DEFINE_CLASS_METHOD(NAME##_vector, void, NAME##_vec_remove, METHOD_ARGS(int index),	\
	)	\
	DEFINE_CLASS_CONSTRUCTOR(NAME##_vector,	\
		CONSTRUCTOR_STATIC(threshhold, 16);	\
		CONSTRUCTOR_STATIC(size, 0);	\
		CONSTRUCTOR_STATIC(typeSize, sizeof(TYPE));	\
		void* mem = malloc(object->threshhold*object->typeSize);	\
		CONSTRUCTOR_STATIC(data, mem);	\
		CONSTRUCTOR_STATIC(append, &NAME##_vec_append);	\
		CONSTRUCTOR_STATIC(remove, &NAME##_vec_remove);	\
	)	\
	DEFINE_CLASS_DESTRUCTOR(NAME##_vector,	\
		DESTRUCTOR(data);	\
	)	\
	INIT_CLASS(NAME##_vector, NULL)

#endif
