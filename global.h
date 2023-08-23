#ifdef DEFINE_VARIABLES
#define EXTERN /* nothing */
#else
#define EXTERN extern
#endif /* DEFINE_VARIABLES */

/**
 * struct monty_global_data_s - global data
 * @arg: arg
 * Description: global data
 */
typedef struct monty_global_data_s
{
	char *arg;
} monty_global_data_t;
EXTERN monty_global_data_t global_data;
