// (...)
// Berechnet den Index (x,y) der Matrix c aus den Matrizen a und b:
bool multiplyindex(Matrix *a, Matrix *b, Matrix *c, size_t x, size_t y)
{
	int v = 0;
	// Wenn die multiplikation nicht möglich ist, wird false zurueckgegeben
	if (y > a->ncols || x > b->nrows)
	{
		return false;
	}
	for (size_t i = 0; i < a->ncols; i++)
	{
		v += a->array[y][i] * b->array[i][x];
	}
	c->array[y][x] = v;
	return true;
}

bool singlethreaded_multiply(Matrix *a, Matrix *b, Matrix *c)
{
	for (size_t y = 0; y < c->nrows; y++)
	{
		for (size_t x = 0; x < c->ncols; x++)
		{
			if (!multiplyindex(a, b, c, x, y))
			{
				// Sollte es bei der Multiplikation zu Fehlern kommen, wird false zurueckgegeben
				return false;
			}
		}
	}
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
	// Bevor die Berechnung gestartet wird, wird die Ergebnismatrix erstellt
	c->nrows = a->nrows;
	c->ncols = b->ncols;
	c->array = (int **)calloc(c->nrows, sizeof(int *));
	// Sollte der Speicher nicht angefordert werden koennen, wird false zurueckgegeben
	if (c->array == NULL)
	{
		return false;
	}
	for (size_t i = 0; i < c->nrows; i++)
	{
		c->array[i] = (int *)calloc(c->ncols, sizeof(int));
		// Sollte der Speicher nicht angefordert werden koennen, wird false zurueckgegeben und der bisherige Speicher freigegeben
		if (c->array[i] == NULL)
		{
			i--;
			while (i--)
			{
				free(c->array[i]);
			}
			return false;
		}
	}
	bool res;
	if (numthreads == 0)
		res = singlethreaded_multiply(a, b, c);
	else
		res = multithreaded_multiply(a, b, c, numthreads);
	if (!res)
		freeMatrix(c);

	return res;
}
// (...)