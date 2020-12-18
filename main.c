#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <calc.h>

int main(int argc, char *argv[])
{
	if(!calcEvaluate) return -1;
	double result;
	if(argc == 2)
	{
		if(strcmp(argv[1], "--version") == 0)
		{
			printf("calc %d.%d.%d\n", CALC_VERSION_MAJOR, CALC_VERSION_MINOR, CALC_VERSION_PATCH);
			return 0;
		}
		else
		{
			result = calcEvaluate(argv[1]);
			printf("%lf\n", result);
		}
	}
	else
	{
		size_t *lengths = malloc((argc - 1) * sizeof(size_t));
		char *expr = 0;
		if(argc > 1)
		{
			size_t accum_len = 0, last_i = 0;
			for(int i=1; i<argc; ++i)
			{
				size_t len = strlen(argv[i]);
				accum_len += len;
				lengths[i-1] = len;
			}
			expr = malloc((accum_len+1) * sizeof(char));
			for(int i=1; i<argc; ++i)
			{
				size_t len = lengths[i-1];
				strncpy(&expr[last_i], argv[i], len);
				last_i += len;
			}
			expr[(accum_len+1)] = '\0';
		}
		result = calcEvaluate(expr);
		printf("%lf\n", result);
		free(expr);
		free(lengths);
	}
	return !isnan(result);
}