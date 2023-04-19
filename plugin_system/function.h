#ifndef FUNCTION_H
#define FUNCTION_H

#define TYPE_NOTLOAD 0
#define TYPE_NOARG 1
#define TYPE_IN 2
#define TYPE_OUT 3
#define TYPE_INOUT 4

#ifdef __linux__
	#define TRUE 1
	#define FALSE 0
	typedef char BOOL;
#endif

typedef union {
	long int int_number;
	double flt_number;
	char *str_text;
	void *rnd_data;
} pfarg;

typedef struct {
	char *name;
	char type;
} function_info;

typedef BOOL (*function)(pfarg *result,pfarg *arg_tuple);
#endif