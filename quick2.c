/*--- quick2.c ----------------------------------------- Listing 5-8 -----
 * Quicksort with median-of-three partitioning and insertion sort on
 * small subfiles.
 *
 * Uses InsertionSort() from insert.c 
 *---------------------------------------------------------------------*/

#include "sorthdr.h"

static CompFunc StoredCompare;
static Element **StoredArray;

static void xQuickSort2(int L, int R)
{
    if (R - L >= 9) // if there are at least 10 elements
    {
        int i, j, mid;
        Element *temp;

        // sort Lth, Rth, and middle element. Then swap the
        // middle element with the R-1th element. This will
        // obviate the need for bound checking.
        mid = (L + R) / 2;  // this is the middle element
        if (StoredCompare(StoredArray[L],
                    StoredArray[mid]) > 0)
        {
            temp = StoredArray[L];
            StoredArray[L] = StoredArray[mid];
            StoredArray[mid] = temp;
        }

        if (StoredCompare(StoredArray[L],
                    StoredArray[R]) > 0)
        {
            temp = StoredArray[L];
            StoredArray[L] = StoredArray[R];
            StoredArray[R] = temp;
        }

        if (StoredCompare(StoredArray[mid],
                    StoredArray[R]) > 0)
        {
            temp = StoredArray[mid];
            StoredArray[mid] = StoredArray[R];
            StoredArray[R] = temp;
        }

        temp = StoredArray[mid];
        StoredArray[mid] = StoredArray[R - 1];
        StoredArray[R - 1] = temp;

        // Now, we know the Array[L] <= Array[R-1] <= Array[R].
        // We use Array[R-1] as the pivot, so this relationship
        // gives us known sentinels. Also, we need to partition
        // only between L+1 and R-2.
        i = L;      // Scan up from here
        j = R - 1;  //Scan down from here
        for ( ; ; )
        {
            while (StoredCompare(StoredArray[++i],
                        StoredArray[R - 1]) < 0)
                ;

            while (StoredCompare(StoredArray[--j],
                        StoredArray[R - 1]) > 0)
                ;

            if (i >= j)
                break;

            // swap ith and jth elements
            temp = StoredArray[i];
            StoredArray[i] = StoredArray[j];
            StoredArray[j] = temp;
        }

        temp = StoredArray[i];
        StoredArray[i] = StoredArray[R - 1];
        StoredArray[R - 1] = temp;

        xQuickSort2(L, i - 1);
        xQuickSort2(i + 1, R);
    }
}

void QuickSort2(Element **Array, int Items, CompFunc Compare)
{
    void InsertionSort(Elements **, int, CompFunc);

    // save some things
    StoredArray = Array;
    StoredCompare = Compare;

    xQuickSort2(0, Items - 1);

    // Do an insertion sort on the now nearly sorted file
    InsertionSort(Array, Items, Compare);
}
