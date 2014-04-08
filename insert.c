#include "sorthdr.h"

void InsertionSort(Element **Array, int N, CompFunc Compare)
{
    int step;

    // Look at 2nd thru Nth elements, putting each in place
    for (step = 1; step < N; step++)
    {
        int i;
        Element *temp;

        // Now, look to the left and find our spot
        temp = Array[step];
        for (i = step - 1; i >= 0; i--)
        {
            if (Compare(Array[i], temp) > 0)
            {
                // Not there yet, so make room
                Array[i + 1] = Array[i];
            }
            else  // Found it!
                break;
        }

        // Now insert original value from Array[step]
        Array[i + 1] = temp;
    }
}
