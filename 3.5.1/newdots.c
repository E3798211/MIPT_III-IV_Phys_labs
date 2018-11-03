
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#define  INPUT_FILENAME  "dots"
#define OUTPUT_FILENAME  "out"

#define MAX_DOTS 1024

int main(int argc, char const *argv[])
{
	FILE* file = fopen(INPUT_FILENAME, "r");
	if (!file)
	{
		perror("Failed to open input");
		return EXIT_FAILURE;
	}

	double x_coordinates[MAX_DOTS] = {};
	double y_coordinates[MAX_DOTS] = {};
	size_t n_dots = 0;

	int last = 0;
	while( isspace((last = fgetc(file))) );
	ungetc(last, file);
	
	while( fgetc(file) == '(' )
	{
		while( isspace((last = fgetc(file))) );
		ungetc(last, file);

		fscanf(file, "%lg", &x_coordinates[n_dots]);

		while( isspace((last = fgetc(file))) );
		// Comma is skipped
		while( isspace((last = fgetc(file))) );
		ungetc(last, file);

		fscanf(file, "%lg", &y_coordinates[n_dots++]);
		
		while( isspace((last = fgetc(file))) );
		// ')' is skipped
		while( isspace((last = fgetc(file))) );
		ungetc(last, file);
	}

	double offset = -6;

	FILE* output = fopen(OUTPUT_FILENAME, "w");
	if (!output)
	{
		perror("Failet to open output");
		fclose(file);

		return EXIT_FAILURE;
	}

	printf("%lu\n", n_dots);

	for(size_t i = 0; i < n_dots; i++)
		fprintf(output, "(%lg, %lg)\n", 
				x_coordinates[i], y_coordinates[i] - offset);
	
	fclose(output);

	return 0;
}
