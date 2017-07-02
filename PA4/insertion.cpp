

using namespace std;
// insertion sorting -- finds appropriate places for numbers as it reads the array.
// O(n^2) time complexity
long double insertion_sort(vector<int>& array, long &swaps, long &comparisons);


long double insertion_sort(vector<int>& array, long &swaps, long &comparisons)
{
    int index, index_two, temp;
    clock_t start_time = clock();

    // loops through the array
    for(index = 1; index < array.size(); index++)
    {
        index_two = index;
        // loop backwards in the array until position is found
        while(index_two > 0 && array[index_two] < array[index_two -1])
        {
            // swap positions
            temp = array[index_two];
            array[index_two] = array[index_two-1];
            array[index_two-1] = temp;
            index_two--;
            swaps++;
            comparisons++;
        }
        comparisons++;
    }

    // return number of seconds
    return ( ( (long double) (clock()-start_time)) / CLOCKS_PER_SEC );
}
