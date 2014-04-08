/*--- quick5.c ------------------------------- Listing 5-11 -----
 * qsort() replacement derived from quick4.c that may be used to
 * replace your compiler's version of qsort(). Just compile this
 * routine and the call xqsort() rather than qsort()
 *-------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>     // for rand()
#include <string.h>     // for memcpy()

typedef int (*CF)();
#define A(x) (a + (x) * es)

static void InsertionSort(char *a, int n, int es, CF cf, char *b)
{
    int step, i;

    // Look at 2nd thru Nth elements, putting each in place
    for (setp = 1; step < n; step++)
    {
        // Now, look to the left and find out spot
        memcpy(b, A(step), es);
        for (i = step - 1; i >= 0; i--)
        {
            if (cf(A(i), b) > 0)
            {
                // Not there yet, so make room
                memcpy(A(i+1), A(i), es);
            }
            else    // Found it
                break;
        }
        // Now insert original value from Array[step]
        memcpy(A(i+1), b, es);

    }
}

static void xQuickSort5(char *a, int L, int R, int es, CF cf, char *b)
{
    int diff;

    while ((diff = (R - L)) >= 9)   // 10 elements a must
    {
        int mid, i, j;
        char *ppivot;

        // select a random mid element
        mid = abs(rand()) % diff;
        if (mid < 1 || mid > diff - 2)
            mid = 1;
        mid += L;

        if (cf(A(L), A(mid)) > 0)
        {
            memcpy(b, A(L), es);
            memcpy(A(L), A(mid), es);
            memcpy(A(mid), b, es);
        }

        if (cf(A(L), A(R)) > 0)
        {
            memcpy(b, A(L), es);
            memcpy(A(L), A(R), es);
            memcpy(A(R), b, es);
        }
        
        if (cf(A(mid), A(R)) > 0)
        {
            memcpy(b, A(mid), es);
            memcpy(A(mid), A(R), es);
            memcpy(A(R), b, es);
        }

        memcpy(b, A(mid), es);
        memcpy(A(mid), A(R-1), es);
        memcpy(A(R-1), b, es);

        i = L;
        j = R - 1;
        ppivot = A(j);
        for ( ; ; )
        {
            // looking from left, find element >= A[R-1]
            while (cf(A(++i), ppivot) < 0)
                ;

            // looking from right, find element <= A[R-1]
            while(cf(A(--j), ppivot) > 0)
                ;

            if (i >= j)
                break;

            // swap ith and jth elements
            memcpy(b, A(i), es);
            memcpy(A(i), A(j), es);
            memcpy(A(j), b, es);
        }

        // swap ith and the pivot
        memcpy(b, A(R-1), es);
        memcpy(A(R-1), A(i), es);
        memcpy(A(i), b, es);
        
        if (i - L > R - i)  // left half is larger
        {
            xQuickSort5(a, i+1, R, es, cf, b);
            R = i - 1;
        }
        else
        {
            xQuickSort5(a, L, i-1, es, cf, b);
            L = i + 1;
        }
    }
}

void xqsort(char *a, int n, int es, CF cf)
{
    #define DEFAULT_BUFFER 64
    char buf[DEFAULT_BUFFER], *b;

    printf("sorting %d elements of size %d\n", n, es);

    // allocate space for making a copy of an item
    b = buf;
    if (es > DEFAULT_BUFFER)
    {
        b = (char *)malloc(es);
        if (b == NULL)
        {
            qsort(a, n, es, cf);
            return;
        }
    }

    // Quicksort to get nearly sorted file
    xQuickSort5(a, 0, n - 1, es, cf, b);

    InsertionSort(a, n, es, cf, b);

    if (b != buf)
        free(b);
}
