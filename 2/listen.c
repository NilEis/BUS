#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stud_type
{
    int matnum;
    char vorname[20];
    char nachname[20];
    struct stud_type *next;
} stud_type;

typedef struct stud_list
{
    stud_type *stud;
    struct stud_list *next;
} stud_list;

/* Ist die Datenbank leer?      */
bool is_empty(stud_type const *liste)
{
    return !liste;
}

/* Einfuegen eines Elementes
 *
 * Bekommt einen Zeiger auf einen Zeiger der auf das 1. Element der Liste zeigt
 * Bekommt MatNr, Vorname und Nachname des Studenten der eingefügt werden soll
 *
 * Gibt true für Erfolg zurück
 * Gibt false für einen Fehler zurück
 */
bool enqueue(stud_type **studenten_liste, int matnum, char const vorname[20], char const nachname[20])
{
    /* Hole dynamischen Speicher für den neuen Listen Eintrag */
    stud_type *tmp = (stud_type *)malloc(sizeof(stud_type));
    /* Teste ob der Speicher angeforderd werden konnte */
    if (tmp == NULL)
    {
        return false;
    }
    /* Befülle den Speicher (vorsicht vor buffer overflows!) */
    tmp->matnum = matnum;
    strcpy(tmp->vorname, vorname);
    strcpy(tmp->nachname, nachname);
    tmp->next = NULL;
    /* Füge den neuen Eintrag in die Liste ein */
    /* Ist die Liste leer ? */
    /* Ist die Liste leer, wird der neue Student als Liste gesetzt */
    if (is_empty(*studenten_liste))
    {
        *studenten_liste = tmp;
        return true;
    }
    /* Sortier den Studenten aufsteigend nach Matrikelnummer ein (matrikelnummern sind einzigartig) */
    stud_type *n = *studenten_liste;
    stud_type *p = NULL;
    /* Sollte das erste Element größer als das einzufügende sein, wird das Einzufügende als erstes eingefügt */
    if ((*studenten_liste)->matnum > matnum)
    {
        tmp->next = *studenten_liste;
        *studenten_liste = tmp;
        return true;
    }
    /* Es wird so lange die liste durch gegangen, bis das Elemet eingefügt werden kann, oder sie leer ist */
    while (!is_empty(n) && n->matnum < tmp->matnum)
    {
        p = n;
        n = n->next;
    }
    /* Sollte das Element gültig sein, wird es eingefügt */
    if (!is_empty(p) && p->matnum < tmp->matnum)
    {
        tmp->next = p->next;
        p->next = tmp;
        return true;
    }
    /* Sollte das Element ungültig sein, wird der Speicher wieder frei gegeben */
    free(tmp);
    return false;
}

/* Löschen eines Elementes.
 *
 * Bekommt einen Zeiger auf einen Zeiger der auf das 1. Element der Liste zeigt
 * Bekommt die MatNr des Studenten der zu löschen ist
 *
 * Gibt true für Erfolg zurück
 * Gibt false für einen Fehler zurück
 */
bool dequeue(stud_type **studenten_liste, int matnum)
{
    stud_type *n = *studenten_liste;
    stud_type *p = NULL;
    bool gefunden = false;
    /* Prüfe Randbedingungen */
    if (is_empty(*studenten_liste))
    {
        return false;
    }
    /* Finde den Studenten */
    /* Was muss passieren wenn das 1. Element gelöscht wird? */
    if ((*studenten_liste)->matnum == matnum)
    {
        *studenten_liste = (*studenten_liste)->next;
        p = n;
        gefunden = true;
    }
    else
    {
        while (n->next != NULL)
        {
            if (n->next->matnum == matnum)
            {
                gefunden = true;
                p = n->next;
                n->next = n->next->next;
                break;
            }
            n = n->next;
        }
    }
    /* Was ist wenn es nicht in der Liste ist? */
    /* Lösche den Studenten und gibt den Speicher frei */
    if (gefunden)
    {
        free(p);
        return true;
    }
    return false;
    /* ... */
}

/* Auslesen eines Elementes
 *
 * Bekommt pointer auf den Listenstart
 * Bekommt MatNr des Studenten der ausgelesen werden soll
 *
 * Schreibt Vorname und Nachname in vorname und nachname
 */
bool get_student(stud_type const *studenten_liste, int matnum, char vorname[20], char nachname[20])
{
    /* Durchsuchen der DB */
    stud_type const *curr = studenten_liste;
    while (curr && curr->matnum < matnum)
    {
        curr = curr->next;
    }

    if (!curr || curr->matnum != matnum)
    {
        /* Rückgabewert: Fehler */
        return false;
    }
    else
    {
        strncpy(vorname, curr->vorname, 19);
        vorname[19] = '\0';
        strncpy(nachname, curr->nachname, 19);
        nachname[19] = '\0';
        /* Rückgabewert: OK */
        return true;
    }
}

static int compare_students_first_name(stud_type const *t1, stud_type const *t2)
{
    return strcmp(t1->vorname, t2->vorname);
}

static int compare_students_last_name(stud_type const *t1, stud_type const *t2)
{
    return strcmp(t1->nachname, t2->nachname);
}

stud_list *sort_students(stud_type *liste, int (*cmp_students)(stud_type const *t1, stud_type const *t2))
{
    if (is_empty(liste))
    {
        return NULL;
    }
    stud_list *l = (stud_list *)calloc(1, sizeof(stud_list));
    if (l == NULL)
    {
        return NULL;
    }
    stud_type *tmp = liste;
    l->stud = tmp;
    tmp = tmp->next;
    while (!is_empty(tmp))
    {
        stud_list *tmp_l = l;
        while (tmp_l != NULL)
        {
            if (cmp_students(tmp_l->stud, tmp) != 1)
            {
                stud_list *t = tmp_l->next;
                tmp_l->next = (stud_list *)malloc(sizeof(stud_list));
                tmp_l->next->stud = tmp;
                tmp_l->next->next = t;
                goto inserted; // Darf man das so?
            }
            tmp_l = tmp_l->next;
        }
        if (cmp_students(l->stud, tmp) == 1)
        {
            stud_list *t = (stud_list *)calloc(1, sizeof(stud_list));
            t->next = l;
            t->stud = tmp;
            l = t;
        }
    inserted:
        tmp = tmp->next;
    }
    return l;
}

static void test_empty(stud_type const *liste)
{
    printf(">>> Test ob die Studentenliste leer ist ...\n");

    if (is_empty(liste))
    {
        printf("    Die Studentenliste ist leer \n");
    }
    else
    {
        printf("    Die Studentenliste ist nicht leer \n");
    }
}

static void test_get(stud_type const *liste, int matnum)
{
    printf(">>> Test, ob die Matrikelnummer %4i bereits erfasst wurde ...\n", matnum);

    char vorname[20];
    char nachname[20];
    if (get_student(liste, matnum, vorname, nachname))
    {
        printf("    Matrikelnummer %4i: %s %s\n", matnum, vorname, nachname);
    }
    else
    {
        printf("    Matrikelnummer %4i ist unbekannt\n", matnum);
    }
}

static void test_enqueue(stud_type **liste, int matnum, char const *vorname, char const *nachname)
{
    printf(">>> Fuege neuen Studenten in die Liste ein: %s %s [%4i] ...\n", vorname, nachname, matnum);
    if (enqueue(liste, matnum, vorname, nachname))
    {
        printf("    Matrikelnummer %4i eingefügt\n", matnum);
    }
    else
    {
        printf("    Matrikelnummer %4i konnte nicht eingefügt werden\n", matnum);
    }
}

static void test_dequeue(stud_type **liste, int matnum)
{
    printf(">>> Loesche die Matrikelnummer %4i ...\n", matnum);

    if (dequeue(liste, matnum))
    {
        printf("    Matrikelnummer %4i geloescht\n", matnum);
    }
    else
    {
        printf("    Matrikelnummer %4i war nicht erfasst\n", matnum);
    }
}

static void test_dump(stud_type const *liste)
{
    printf(">>> Gebe alle erfassten Studenten aus ...\n");
    for (stud_type const *curr = liste; curr; curr = curr->next)
    {
        printf("    Matrikelnummer %4i: %s %s\n", curr->matnum, curr->vorname, curr->nachname);
    }
}

/* Test der Listenfunktionen  */
int main(void)
{
    /* Initialisierung der Datenbank */
    stud_type *studenten_liste = NULL;

    test_empty(studenten_liste);
    test_enqueue(&studenten_liste, 1234, "Eddard", "Stark");
    test_get(studenten_liste, 1234);
    test_enqueue(&studenten_liste, 5678, "Jon", "Snow");
    test_get(studenten_liste, 1234);
    test_enqueue(&studenten_liste, 9999, "Tyrion", "Lannister");
    test_get(studenten_liste, 1235);
    test_enqueue(&studenten_liste, 1289, "Daenerys", "Targaryen");
    test_dequeue(&studenten_liste, 1234);
    test_empty(studenten_liste);
    test_get(studenten_liste, 5678);
    test_dequeue(&studenten_liste, 9998);
    test_enqueue(&studenten_liste, 1289, "Viserys", "Targaryen");
    test_dequeue(&studenten_liste, 5678);
    test_enqueue(&studenten_liste, 1, "Tywin", "Lannister");
    test_dump(studenten_liste);

    {
        test_enqueue(&studenten_liste, 434188, "N", "E");
        puts("Teste sortierung nach Vornamen:");
        /* Erzeuge sortierte Liste nach Vorname */
        stud_list *vn = sort_students(studenten_liste, compare_students_first_name);
        stud_list *tmp = vn;
        /* Gebe Liste aus */
        while (tmp != NULL)
        {
            printf("    %s %s (%d)\n", tmp->stud->vorname, tmp->stud->nachname, tmp->stud->matnum);
            tmp = tmp->next;
        }
        /* Räume erzeugte Liste auf */
        tmp = vn;
        while (vn != NULL)
        {
            tmp = vn;
            vn = vn->next;
            free(tmp);
        }
    }

    {
        puts("Teste sortierung nach Nachnamen:");
        /* Erzeuge sortierte Liste nach Vorname */
        stud_list *vn = sort_students(studenten_liste, compare_students_last_name);
        stud_list *tmp = vn;
        /* Gebe Liste aus */
        {
            while (tmp != NULL)
            {
                printf("    %s %s (%d)\n", tmp->stud->vorname, tmp->stud->nachname, tmp->stud->matnum);
                tmp = tmp->next;
            }
        }
        /* Räume erzeugte Liste auf */
        {
            tmp = vn;
            while (vn != NULL)
            {
                tmp = vn;
                vn = vn->next;
                free(tmp);
            }
        }
    }

    /* Räume studenten_liste auf */
    {
        stud_type *tmp = studenten_liste;
        while (!is_empty(studenten_liste))
        {
            tmp = studenten_liste;
            studenten_liste = studenten_liste->next;
            free(tmp);
        }
    }
    return 0;
}
