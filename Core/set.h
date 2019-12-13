#ifndef SET_H
#define SET_H

// #include <Core/Class/cOO.h>

#define generate_set(TYPE, NAME, COMPARE)	\
	int NAME##_set_compare(const void* _a, const void* _b) {	\
		TYPE a  = *(TYPE*)_a;	\
		TYPE b  = *(TYPE*)_b;	\
		COMPARE	\
	}	\
	typedef struct NAME##_set NAME##_set;	\
	struct NAME##_set {	\
		TYPE* data;	\
		bool (*append)(NAME##_set*, TYPE data);	\
		bool (*appendP)(NAME##_set*, void* data);	\
		bool (*remove)(NAME##_set*, int index);	\
		bool (*removeByData)(NAME##_set*, TYPE data);	\
		size_t threshold;	\
		size_t size;	\
		size_t typeSize;	\
		double factor;	\
	};	\
	void NAME##_set_expand(NAME##_set* self) {	\
		size_t threshold = self->threshold;	\
		double factor = self->factor;	\
		size_t newSize = ceil(threshold*factor);	\
		size_t typeSize = self->typeSize;	\
		/*printf("RESIZED VECTOR FROM %I64d ELEMENTS TO %I64d ELEMENTS\n", threshold, newSize);	*/\
		/*printf("RESIZED VECTOR FROM %.4lf mb TO %.4lf mb\n", threshold*typeSize/1048576.0, newSize*typeSize/1048576.0);	*/\
		self->threshold = newSize;	\
		self->data = realloc(self->data, newSize*typeSize);	\
	}	\
	bool NAME##_set_checkValid(NAME##_set* self, TYPE data) {	\
		for (int i = 0; i < self->size; i++) {	\
			if (self->data[i] == data) {	\
				return false;	\
			}	\
		}	\
		return true;	\
	}	\
	bool NAME##_set_append(NAME##_set* self, TYPE data) {	\
		/* CHECK IF DUPLICATE VALUE */	\
		if (!NAME##_set_checkValid(self, data)) {	\
			return false;	\
		}	\
		if (self->size > self->threshold) {	\
			NAME##_set_expand(self);	\
		}	\
		self->data[self->size] = data;	\
		qsort(self->data, self->size, self->typeSize, NAME##_set_compare);	\
		self->size += 1;	\
		return true;	\
	}	\
	bool NAME##_set_appendP(NAME##_set* self, void* _data) {	\
		/* CHECK IF DUPLICATE VALUE */	\
		TYPE data = *((TYPE*) _data);	\
		if (!NAME##_set_checkValid(self, data)) {	\
			return false;	\
		}	\
		if (self->size > self->threshold) {	\
			NAME##_set_expand(self);	\
		}	\
		self->data[self->size] = data;	\
		qsort(self->data, self->size, self->typeSize, NAME##_set_compare);	\
		self->size += 1;	\
		return true;	\
	}	\
	bool NAME##_set_remove(NAME##_set* self, int index) {	\
		for (int i = index; i < self->threshold-1; i++) {	\
			self->data[i] = self->data[i+1];	\
		}	\
		self->size -= 1;	\
		return true;	\
	}	\
	bool NAME##_set_removeByData(NAME##_set* self, TYPE data) {	\
		int rem = 0;	\
		for (int i = 0; i < self->size; i++) {	\
			if (self->data[i] == data) {	\
				rem = i;	\
			}	\
		}	\
		for (int i = rem; i < self->threshold-1; i++) {	\
			self->data[i] = self->data[i+1];	\
		}	\
		self->size -= 1;	\
		return true;	\
	}	\
	NAME##_set* NAME##_set_new(double factor, int size) {	\
		NAME##_set* newSet = malloc(sizeof(NAME##_set));	\
		newSet->append = &NAME##_set_append;	\
		newSet->appendP = &NAME##_set_appendP;	\
		newSet->remove = &NAME##_set_remove;	\
		newSet->removeByData = &NAME##_set_removeByData;	\
		newSet->threshold = size > 0 ? size : 1;	\
		newSet->size = 0;	\
		newSet->typeSize = sizeof(TYPE);	\
		newSet->factor = factor;	\
		newSet->data = malloc(sizeof(TYPE)*newSet->threshold);	\
		return newSet;	\
	}	\
	const NAME##_set NAME##_set_INIT = {	\
		NULL,	\
		&NAME##_set_append,	\
		&NAME##_set_appendP,	\
		&NAME##_set_remove,	\
		&NAME##_set_removeByData,	\
		1,	\
		0,	\
		sizeof(TYPE),	\
		2,	\
	}

#endif
