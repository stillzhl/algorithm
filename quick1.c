/*--- quick1.c ------------------------------------- Listing 5-7 ---
 * A basic quicksort
 *
 * #define DRIVER to compile a test driver
 * Driver must be linked to sortsub.c (Listing 5-1)
 *--------------------------------------------------------------*/

#include "sorthdr.h"

#define DRIVER 1

static CompFunc StoredCompare;
static Element  **StoredArray;

static void xQuickSort1(int L, int R)
{
    if (R > L)
    {
        int i, j;
        Element *temp;

        // First, partition the array using array[R] as pivot
        i = L - 1; // scan up from here
        j = R;      // scan down from here
        for ( ; ; )
        {
            /*
             * Looking from left, find element >= Array[R].
             * No sentinel needed, as Array[R] will stop us
             */
            while (StoredCompare(StoredArray[++i],
                                StoredArray[R]) < 0)
                ;

            /*
             * Look from right, find element <= Array[R]
             * The llp provides boundary checking.
             */
            while (j > 0)
            {
                if (StoredCompare(StoredArray[--j],
                            StoredArray[R]) <= 0)
                    break;
            }

            if (i >= j)
                break;

            // swap ith and jth elements
            temp = StoredArray[i];
            StoredArray[i] = StoredArray[j];
            StoredArray[j] = temp;
        }

        // swap ith and Rth elements
        temp = StoredArray[i];
        StoredArray[i] = StoredArray[R];
        StoredArray[R] = temp;
        
        xQuickSort1(L, i - 1);
        xQuickSort1(i + 1, R);
    }
}

void QuickSort1(Element **Array, int Items, CompFunc Compare)
{
    StoredCompare = Compare;
    StoredArray = Array;
    xQuickSort1(0, Items - 1);
}

