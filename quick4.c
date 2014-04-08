#include <stddef.h>     // for typedef of ptrdiff_t
#include <stdlib.h>     // for rand()
#include "sorthdr.h"


static CompFunc StoredCompare;

static void xQuickSort4(Element **pL, Element **pR)
{
    ptrdiff_t diff;   /* ptrdiff_t is a signed type that can hold
                        the difference between two pointers */

    while ((diff = (pR - pL)) >= 9)
    {
        int mid;
        Element *temp, **pmid, **pi, **pj, **ppivot;

        // select a random mid element
        mid = abs(rand()) % diff;
        if (mid < 1 || mid > diff - 2)
            mid = 1;
        pmid = pL + mid;

        /*
         * Sort Lth, Rth, and middle element. Then swap the middle
         * element with the R-1'th element. This will obviate the
         * need for bound checking.
         */
        if (StoredCompare(*pL, *pmid) > 0)
        {
            temp = *pL;
            *pL = *pmid;
            *pmid = temp;
        }

        if (StoredCompare(*pL, *pR) > 0)
        {
            temp = *pL;
            *pL = *pR;
            *pR = temp;
        }

        if (StoredCompare(*pmid, *pR) > 0)
        {
            temp = *pmid;
            *pmid = *pR;
            *pR = temp;
        }
        
        temp = *pmid;
        *pmid = *(pR - 1);
        *(pR - 1) = temp;

        // Now we know that A[L] <= A[R-1] <= A[R].
        // We use A[R-1] as the pivot, so this relationship
        // gives us known sentinels. Also, we need to partition
        // only between L+1 and R-2.
        pi = pL;
        pj = pR - 1;
        ppivot = *pj;
        
        for ( ; ; )
        {
            while (StoredCompare(*++pi, ppivot) < 0)
                ;

            while (StoredCompare(*--pj, ppivot) > 0)
                ;

            if (pi >= pj)
                break;

            // swap ith and jth elements
            temp = *pi;
            *pi = *pj;
            *pj = temp;
        }

        // swap ith and the pivot
        *(pR - 1) = *pi;
        *pi = ppivot;

        if (pi - pL > pR - pi)  // left half is larger
        {
            xQuickSort4(pi + 1, pR);    // recurse on smaller half
            pR = pi - 1;
        }
        else    // right half is larger
        {
            xQuickSort4(pL, pi - 1);
            pL = pi + 1;
        }
    }
}

void QuickSort4(Element **Array, int Items, CompFunc Compare)
{
    void InsertionSort(Element **, int, CompFunc);

    // save some things
    StoredCompare = Compare;

    xQuickSort4(Array, Array + Items - 1);
    
    InsertionSort(Array, Items, Compare);
}
