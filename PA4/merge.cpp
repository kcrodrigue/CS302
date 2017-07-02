

using namespace std;

// merge sort -- recursively separates array into sub arrays, for quicker sorting.
// O(n log(n)) time complexity
double merge_sort(vector<int>& array, int left, int right, long &swaps, long &comparisons);

// tool for merge sort to take two parts of an array and merge them
void merge(vector<int>& array, int left, int middle, int right, long &swaps, long &comparisons);


void merge(vector<int>& array, int left, int middle, int right, long &swaps, long &comparisons)
{
    int index_one, index_two, index_three;
    int size_1 = middle - left + 1;
    int size_2 =  right - middle;
    int left_array[size_1], right_array[size_2];

    //copy original array into two sub arrays
    for (index_one = 0; index_one < size_1; index_one++)
    {
        left_array[index_one] = array[left + index_one];
    }

    for (index_two = 0; index_two < size_2; index_two++)
    {
        right_array[index_two] = array[middle + 1+ index_two];
    }


    index_one = 0; // Initial index of first subarray
    index_two = 0; // Initial index of second subarray
    index_three = left; // Initial index of merged subarray

    // merge temporary array into sub arrays
    while (index_one < size_1 && index_two < size_2)
    {
        if (left_array[index_one] <= right_array[index_two])
        {
            array[index_three] = left_array[index_one];
            index_one++;
        }
        else
        {
            array[index_three] = right_array[index_two];
            index_two++;
        }
        index_three++;
        comparisons++;
    }

    // copy the rest of the left side into the array
    while (index_one < size_1)
    {
        array[index_three] = left_array[index_one];
        index_one++;
        index_three++;
    }

    //copy the rest of the right side into the array
    while (index_two < size_2)
    {
        array[index_three] = right_array[index_two];
        index_two++;
        index_three++;
    }
}

double merge_sort(vector<int>& array, int left, int right, long &swaps, long &comparisons)
{
    clock_t start = clock();
    if (left < right)
    {
        int middle = left+(right-left)/2;

        // sort each half
        merge_sort(array, left, middle, swaps, comparisons);
        merge_sort(array, middle+1, right, swaps, comparisons);

        // merge sorted halves
        merge(array, left, middle, right, swaps, comparisons);
    }

    return ( ( (long double) (clock()-start)) / CLOCKS_PER_SEC );
}
