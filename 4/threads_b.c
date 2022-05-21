// (...)
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
	size_t x;
	size_t y;
	// Berechne die Werte für die übergebenen Zellen
	for (size_t i = threadarg->start_index; i < threadarg->end_index; i++)
	{
		// Sollte der Index ungültig sein wird der Thread beendet
		if (i >= threadarg->max_index)
		{
			return threadarg;
		}
		// Berechne die Position des Indizes in der Matrix
		y = i / threadarg->c->ncols;
		x = i - (y * threadarg->c->ncols);
		// Versuche den Wert zu berechnen, sollte dabei ein Fehler auftreten gibt die Methode zurück
		threadarg->success &= multiplyindex(threadarg->a, threadarg->b, threadarg->c, x, y);
		if (!threadarg->success)
		{
			return threadarg;
		}
	}
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
	size_t max = c->nrows * c->ncols;
	//Sollten weniger Threads als Indizes existieren muss die Arbeit fair aufgeteilt werden.
	if (max >= numthreads)
	{
		size_t part = 0;
		// Wenn die Anzahl der Indizes durch die Anzahl der Threads teilbar sein,
		// bekommt jeder Thread die gleiche Anzahl an Indizes
		if (max % numthreads == 0)
		{
			part = max / numthreads;
		}
		// Sollte dies nicht so sein, wird die Anzahl der Indizes pro Thread so erhöht, dass alle Indizes bearbeitet werden.
		// Dadurch werden dem letzten Thread zwar zu hohe Indizes uebergeben, jedoch wird darauf im Thread selbst geprueft
		else
		{
			part = max / (numthreads - 1);
		}
		for (unsigned int i = 0; i < numthreads; i++)
		{
			threadargs[i].a = a;
			threadargs[i].b = b;
			threadargs[i].c = c;
			threadargs[i].start_index = i * part;
			threadargs[i].end_index = i * part + part;
			threadargs[i].max_index = max;
			threadargs[i].success = true;
		}
	}
	else
	{
		// Sollten mehr Threads vorhanden sein als Indizes,
		// werden den Ueberzähligen ungültige Indizes uebergeben, so dass diese direkt zurueckgeben.
		// Dies ist zwar keine gute Loesung, da man die Anzahl der Threads auch an die Zahl der Indizes anpassen könnte, jedoch
		// waren wir uns unsicher ob wir dies in diesem Fall dürfen.
		for (unsigned int i = 0; i < numthreads; i++)
		{
			threadargs[i].a = a;
			threadargs[i].b = b;
			threadargs[i].c = c;
			threadargs[i].start_index = i;
			threadargs[i].end_index = i + 1;
			threadargs[i].max_index = max;
			threadargs[i].success = true;
		}
	}

	// Erstellen Sie anschließend die Worker-Threads mittels der Funktion
	// pthread_create. (Man-Page lesen!)
	// Es sollen genau numthreads Worker-Threads erstellt werden.
	// TODO
	for (unsigned int i = 0; i < numthreads; i++)
	{
		// Sollte ein Thread nicht erstellt werden können wird die Berechnung abgebrochen
		// und alle bisher erstellten Threads abgebrochen.
		if (pthread_create(&tinfo[i], NULL, thread_routine, (void *)&threadargs[i]) != 0)
		{
			i--;
			while (i < numthreads)
			{
				pthread_cancel(tinfo[i]);
			}
			return false;
		}
	}

	void *res_voidp = NULL;
	// Warten Sie nun der Reihe nach auf die Threads mit Hilfe
	// der Funktion pthread_join. (Man-Page lesen!)
	// Sie müssen der Funktion einen Pointer auf einen void-Pointer
	// übergeben. Sie können dazu den res_voidp nutzen.
	// TODO
	for (unsigned int i = 0; i < numthreads; i++)
	{
		pthread_join(tinfo[i], &res_voidp);
		ThreadArg *res = (ThreadArg *)res_voidp;
		// Da uns wir von unseren Threads einen ThreadArg-Pointer
		// zurückbekommen, können wir den erhaltenen void-Pointer in einen
		// ebensolchen casten. Überprüfen Sie, ob der Thread erfolreich
		// war.
		// TODO
		// Wenn eine Berechnung Fehlerhaft war wird false zurückgegeben
		if (!res->success)
		{
			return false;
		}
	}
	return true;
}
// (...)