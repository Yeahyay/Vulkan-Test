#ifndef VECTOR_CLASS_H
#define VECTOR_CLASS_H

// #include <Core/Class/cOO.h>

#define vector_init(TYPE, VECTOR, THRESHOLD, SIZE, INIT)	\
{	\
	.data			= INIT,	\
	.append		= &VECTOR##_vec_append,	\
	.appendP 	= &VECTOR##_vec_appendP,	\
	.resize		= &VECTOR##_vec_resize,	\
	.remove		= &VECTOR##_vec_remove,	\
	.isEmpty		= &VECTOR##_vec_isEmpty,	\
	.free			= &VECTOR##_vec_free,	\
	.threshold	= THRESHOLD,	\
	.size			= SIZE,	\
	.empty		= SIZE > 0 ? false : true,	\
	.typeSize	= sizeof(TYPE),	\
	.factor		= 2,	\
}	\

#define vector_static_null(TYPE, VECTOR, NAME)	\
	VECTOR##_vector NAME = 	\
		vector_init(TYPE, VECTOR, 1, 0, NULL)

#define vector_static(TYPE, VECTOR, NAME, SIZE, ...)	\
	VECTOR##_vector NAME = 	\
		vector_init(TYPE, VECTOR, SIZE, SIZE, (TYPE[]){__VA_ARGS__})

#define vector_reinterpret(VECTOR, TO_TYPE)	\
	(TO_TYPE)VECTOR->data

#define generate_vector(TYPE, NAME)	\
	typedef struct NAME##_vector NAME##_vector;	\
	struct NAME##_vector {	\
		TYPE* data;	\
		void (*append)(NAME##_vector*, TYPE data);	\
		void (*appendP)(NAME##_vector*, TYPE* data);	\
		void (*resize)(NAME##_vector*, size_t newSize);	\
		void (*remove)(NAME##_vector*, long int index);	\
		bool (*isEmpty)(NAME##_vector*);	\
		void (*free)(NAME##_vector*);	\
		size_t threshold;	\
		size_t size;	\
		bool empty;	\
		size_t typeSize;	\
		double factor;	\
	};	\
	static void NAME##_vec_resize(NAME##_vector* self, size_t newSize) {	\
		size_t threshold = self->threshold;	\
		size_t typeSize = self->typeSize;	\
		/*info(1, "RESIZED VECTOR FROM %I64d ELEMENTS TO %I64d ELEMENTS\n", threshold, newSize);	*/\
		/*info(1, "RESIZED VECTOR FROM %.4lf mb TO %.4lf mb\n", threshold*typeSize/1048576.0, newSize*typeSize/1048576.0);	*/\
		self->threshold = newSize;	\
		self->size = self->size > newSize ? newSize : self->size;	\
		self->empty = self->size > 0 ? false : true;	\
		self->data = realloc(self->data, newSize*typeSize);	\
	}	\
	static void NAME##_vec_expand(NAME##_vector* self) {	\
		size_t threshold = self->threshold;	\
		double factor = self->factor;	\
		size_t newSize = ceil(threshold*factor);	\
		size_t typeSize = self->typeSize;	\
		/*info(1, "EXPANDED VECTOR FROM %I64d ELEMENTS TO %I64d ELEMENTS\n", threshold, newSize);	*/\
		/*info(1, "EXPANDED VECTOR FROM %.4lf mb TO %.4lf mb\n", threshold*typeSize/1048576.0, newSize*typeSize/1048576.0);	*/\
		self->threshold = newSize;	\
		self->empty = false;	\
		self->data = realloc(self->data, newSize*typeSize);	\
	}	\
	static void NAME##_vec_append(NAME##_vector* self, TYPE data) {	\
		if (self->size > self->threshold) {	\
			NAME##_vec_expand(self);	\
		}	\
		self->data[self->size] = data;	\
		self->size += 1;	\
		self->empty = false;	\
	}	\
	static void NAME##_vec_appendP(NAME##_vector* self, TYPE* data) {	\
		if (self->size > self->threshold) {	\
			NAME##_vec_expand(self);	\
		}	\
		self->data[self->size] = *data;	\
		self->size += 1;	\
		self->empty = false;	\
	}	\
	static void NAME##_vec_remove(NAME##_vector* self, long int index) {	\
	}	\
	static bool NAME##_vec_isEmpty(NAME##_vector* self) {	\
		return self->size > 0 ? true : false;	\
	}	\
	static void NAME##_vec_free(NAME##_vector* self) {	\
		free(self->data);	\
		self->data = 0;	\
		free(self);	\
		self = 0;	\
	}	\
	NAME##_vector* NAME##_vector_new(double factor, size_t size) {	\
		NAME##_vector* newVector = malloc(sizeof(NAME##_vector));	\
		newVector->append = &NAME##_vec_append;	\
		newVector->appendP = &NAME##_vec_appendP;	\
		newVector->resize = &NAME##_vec_resize;	\
		newVector->remove = &NAME##_vec_remove;	\
		newVector->isEmpty = &NAME##_vec_isEmpty;	\
		newVector->free = &NAME##_vec_free;	\
		newVector->threshold = size > 0 ? size : 1;	\
		newVector->size = 0;	\
		newVector->empty = true;	\
		newVector->typeSize = sizeof(TYPE);	\
		newVector->factor = factor;	\
		newVector->data = malloc(sizeof(TYPE)*newVector->threshold);	\
		return newVector;	\
	}	\
	const NAME##_vector NAME##_vector_INIT = {	\
		.data			= NULL,	\
		.append		= &NAME##_vec_append,	\
		.appendP 	= &NAME##_vec_appendP,	\
		.resize		= &NAME##_vec_resize,	\
		.remove		= &NAME##_vec_remove,	\
		.isEmpty		= &NAME##_vec_isEmpty,	\
		.free			= &NAME##_vec_free,	\
		.threshold 	= 1,	\
		.size			= 0,	\
	 	.empty		= true,	\
		.typeSize	= sizeof(TYPE),	\
		.factor		= 2,	\
	}

#endif
