#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>
#include <pthread.h>

typedef struct Matrix
{
	size_t nrows;
	size_t ncols;
	int **array;
} Matrix;

typedef struct ThreadArg
{
	// In dieser Datenstruktur können Sie Daten vom
	// Main-Thread an die Worker-Threads übergeben.
	// Über das bereits angelegte Feld success soll
	// der Thread dann dem Hauptthread mitteilen,
	// ob er die Multiplikation erfolgreich durchgeführt
	// hat.
	// TODO
	bool success;
} ThreadArg;

// Liest eine Matrix aus einer Datei ein.
// Mit dieser Funktion müssen Sie sich nicht weiter beschäftigen.
bool parseMatrix(const char *filepath, Matrix *matrix)
{
	// Check if the file is accessible:
	if (access(filepath, R_OK) != 0)
	{
		fprintf(stderr, "Unable to access file: %s\n", filepath);
		return false;
	}

	// Open the file:
	FILE *fptr = fopen(filepath, "r");
	if (!fptr)
	{
		fprintf(stderr, "Unable to open file: %s\n", filepath);
		return false;
	}

	// Read array dimensions:
	ssize_t nrows = 0, ncols = 0;
	if (fscanf(fptr, "%zd%zd", &nrows, &ncols) != 2) // File format incorrect
	{
		fprintf(stderr, "Illegal file format in file: %s\n", filepath);
		fclose(fptr);
		return false;
	}
	if (nrows < 1 || ncols < 1)
	{
		fprintf(stderr, "Illegal matrix dimensions in file: %s\n", filepath);
		fclose(fptr);
		return false;
	}

	// Allocate memory for column vector:
	matrix->array = malloc(nrows * sizeof(*(matrix->array)));
	if (!matrix->array)
	{
		fprintf(stderr, "Unable to allocate memory for matrix\n");
		fclose(fptr);
		return false;
	}

	// Read matrix:
	bool error = false;
	for (ssize_t x = 0; x < nrows; x++)
	{
		// Allocate memory for row vector:
		matrix->array[x] = malloc(ncols * sizeof(*(matrix->array[x])));
		if (!matrix->array[x])
		{
			fprintf(stderr, "Unable to allocate memory for row %zd\n", x);
			error = true;
		}
		else
		{
			// Read row:
			for (ssize_t y = 0; y < ncols; y++)
			{
				if (fscanf(fptr, "%d", &matrix->array[x][y]) != 1)
				{
					fprintf(stderr, "Encountered illegal entry in file \"%s\" at position (%zd,%zd)\n", filepath, x, y);
					error = true;
					break;
				}
			}
		}
		// If an error occured, we need to clean up:
		if (error)
		{
			fclose(fptr);
			for (ssize_t x2 = 0; x2 < x; x2++)
			{
				free(matrix->array[x2]);
			}
			if (matrix->array[x])
				free(matrix->array[x]);
			free(matrix->array);
			matrix->array = NULL;
			return false;
		}
	}

	// Close file:
	fclose(fptr);

	// Copy rows and cols to file:
	matrix->nrows = nrows;
	matrix->ncols = ncols;

	// Success!
	return true;
}

// Gibt eine Matrix auf dem Bildschirm aus.
// Mit dieser Funktion müssen Sie sich nicht weiter beschäftigen.
void printMatrix(Matrix *m)
{
	for (size_t x = 0; x < m->nrows; x++)
	{
		for (size_t y = 0; y < m->ncols; y++)
		{
			printf("%d ", m->array[x][y]);
		}
		printf("\n");
	}
}

// Gibt den Speicherplatz einer Matrix frei:
void freeMatrix(Matrix *m)
{
	for (size_t x = 0; x < m->nrows; x++)
		free(m->array[x]);
	free(m->array);
}

// Berechnet den Index (x,y) der Matrix c aus den Matrizen a und b:
bool multiplyindex(Matrix *a, Matrix *b, Matrix *c, size_t x, size_t y)
{
	// Implementieren Sie hier die Berechung!
	// TODO
	return true;
}

bool singlethreaded_multiply(Matrix *a, Matrix *b, Matrix *c)
{
	// Implementieren Sie die Matrixmultiplikation sequentiell
	// unter Zuhilfenahme der Funktion mutiplyindex
	// TODO
	return true;
}

// Dies ist die Hauptfunktion eines Threads:
void *thread_routine(void *threadarg_voidp)
{
	ThreadArg *threadarg = (ThreadArg *)threadarg_voidp;
	// Der aktuelle Worker-Thread kann nun auf die Daten zugreifen,
	// die ihm über die ThreadArg Datenstruktur übergeben wurden.
	// Implementieren Sie nun die Teile der Matrixmultiplikation,
	// für die dieser Thread zuständig ist unter Zuhilfenahme
	// der Funktion mutiplyindex
	// TODO
	return threadarg;
}

bool multithreaded_multiply(Matrix *a, Matrix *b, Matrix *c, unsigned int numthreads)
{
	pthread_t tinfo[numthreads];
	ThreadArg threadargs[numthreads];

	// Sie verfügen an dieser Stelle über ein Array threadargs, das für
	// jeden Thread ein ThreadArg-Element enthält, sodass wir die nötigen
	// Daten an den Thread übergeben können.

	// Füllen Sie die Elemente des threadargs Array mit den notwendigen Daten
	// TODO

	// Erstellen Sie anschließend die Worker-Threads mittels der Funktion
	// pthread_create. (Man-Page lesen!)
	// Es sollen genau numthreads Worker-Threads erstellt werden.
	// TODO

	void *res_voidp = NULL;
	// Warten Sie nun der Reihe nach auf die Threads mit Hilfe
	// der Funktion pthread_join. (Man-Page lesen!)
	// Sie müssen der Funktion einen Pointer auf einen void-Pointer
	// übergeben. Sie können dazu den res_voidp nutzen.
	// TODO
	ThreadArg *res = (ThreadArg *)res_voidp;
	// Da uns wir von unseren Threads einen ThreadArg-Pointer
	// zurückbekommen, können wir den erhaltenen void-Pointer in einen
	// ebensolchen casten. Überprüfen Sie, ob der Thread erfolreich
	// war.
	// TODO
	return true;
}

bool multiply(Matrix *a, Matrix *b, Matrix *c, int numthreads)
{
	// Sie bekommen zwei Matrizen a und b, die multipliziert werden sollen.
	// Des weiteren bekommen Sie eine Matrix c, die aber noch gar nicht
	// initialisiert ist.
	// Initialisieren Sie die Matrix c, sodass diese im Anschluss mit
	// dem Ergebnis der Multiplikation gefüllt werden kann.
	// TODO
	//
	bool res;
	if (numthreads == 0)
		res = singlethreaded_multiply(a, b, c);
	else
		res = multithreaded_multiply(a, b, c, numthreads);
	if (!res)
		freeMatrix(c);

	return res;
}

int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		fprintf(stderr, "Usage: %s filename filename numthreads\n", argv[0]);
		return -1;
	}
	unsigned int numthreads;
	if (sscanf(argv[3], "%u", &numthreads) != 1)
	{
		fprintf(stderr, "Could not parse numthreads\n");
		return -1;
	}

	Matrix a, b;
	if (!parseMatrix(argv[1], &a))
	{
		fprintf(stderr, "Error parsing Matrix a\n");
		return -1;
	}
	if (!parseMatrix(argv[2], &b))
	{
		fprintf(stderr, "Error parsing Matrix b\n");
		freeMatrix(&a);
		return -1;
	}

	Matrix c;
	if (!multiply(&a, &b, &c, numthreads))
	{
		fprintf(stderr, "Matrix multiplication failed\n");
		freeMatrix(&a);
		freeMatrix(&b);
		return -1;
	}

	printMatrix(&a);
	printf("*\n");
	printMatrix(&b);
	printf("=\n");
	printMatrix(&c);

	freeMatrix(&a);
	freeMatrix(&b);
	freeMatrix(&c);

	return 0;
}
