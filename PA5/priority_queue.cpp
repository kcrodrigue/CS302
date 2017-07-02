class priority_queue
{
public:
    bool push(int, int);
    bool pop();
    int front();
    int front_duration();
    bool empty();
    int size();
    int smallest_priority();
private:
    vector<int> priority;
    vector<int> duration;
};

bool priority_queue::push(int priority_input, int duration_input)
{
    priority.push_back(priority_input);
    duration.push_back(duration_input);
    // never fails
    return true;
}

bool priority_queue::pop()
{
    int front_element;
    if(!priority.empty())
    {
        front_element = smallest_priority();
        priority.erase(priority.begin() + front_element);
        duration.erase(duration.begin() + front_element);
        return true;
    }

    else
    {
        return false;
    }

}

int priority_queue::front()
{
    if(!priority.empty())
    {
        return priority[smallest_priority()];
    }
    else
    {
        return -1;
    }
}

int priority_queue::front_duration()
{
    if(!priority.empty())
    {
        return duration[smallest_priority()];
    }
    else
    {
        return -1;
    }
}

bool priority_queue::empty()
{
    return priority.empty();
}

int priority_queue::size()
{
    return priority.size();
}

int priority_queue::smallest_priority()
{
    int index, smallest_value;
    int smallest_index = 0;
    smallest_value = priority[0];
    for(index = 0; index < priority.size(); index++)
    {
        if(priority[index] < smallest_value)
        {
            smallest_index = index;
            smallest_value = priority[index];
        }
    }

    return smallest_index;
}
