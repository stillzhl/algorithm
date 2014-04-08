#include "sorthdr.h"

void ShellSort(Element **Array, int N, CompFunc Compare)
{
    int step, h;

    // Find start h
    for (h = 1; h <= N / 9; h = 3 * h + 1)
        ;

    // Now loop thru successively smaller h's
    for ( ; h > 0; h /= 3)
    {
        // Look at hth thru Nth elements
        for (step = h; step < N; step++)
        {
            int i;
            Element *temp;
            
            // Now, look to the left and find our spot
            temp = Array[step];
            for (i = step - h; i >= 0; i -= h)
            {
                if (Compare(temp, Array[i]) < 0)
                {
                    // Not there yet, so make room
                    Array[i + h] = Array[i];
                }
                else    // Found it!
                    break;
            }

            // Now insert original value from Array[step]
            Array[i + h] = temp;
        }
    }
}
