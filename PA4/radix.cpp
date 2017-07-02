

using namespace std;
// get max -- tool for radix sort, simply finds the max number in the array.
int get_max(vector<int>& array);

// count sort -- a tool for radix sort that uses array positioning to sort numbers.
void count_sort(vector<int>& array, int exponent, long &swaps, long &comparisons);

// radix sort -- sorts numbers by exponents
long double radix_sort(vector<int>& array, long &swaps, long &comparisons);

int get_max(vector<int>& array)
{
    int max = array[0];

    // loop through array to find max
    for (int index = 1; index < array.size(); index++)
    {
        if (array[index] > max)
        {
            max = array[index];
        }
    }
    return max;
}

void count_sort(vector<int>& array, int exponent, long &swaps, long &comparisons)
{
    int output[array.size()];
    int index, count[10] = {0};

    for (index = 0; index < array.size(); index++)
    {
        count[ (array[index]/exponent)%10 ]++;
    }

    for (index = 1; index < 10; index++)
    {
        count[index] += count[index - 1];
    }

    for (index = array.size() - 1; index >= 0; index--)
    {
        output[count[ (array[index]/exponent)%10 ] - 1] = array[index];
        count[ (array[index]/exponent)%10 ]--;
    }

    for (index = 0; index < array.size(); index++)
    {
        array[index] = output[index];
    }
}

long double radix_sort(vector<int>& array, long &swaps, long &comparisons)
{
    int max = get_max(array);
    clock_t start = clock();

    for (int exponent = 1; max/exponent > 0; exponent *= 10)
    {
        count_sort(array, exponent, swaps, comparisons);
    }

    return ( ( (long double) (clock()-start)) / CLOCKS_PER_SEC );
}
