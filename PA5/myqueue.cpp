class my_queue
{
public:
    bool push(int input);
    bool pop();
    int front();
    bool empty();
    int size();
private:
    vector<int> values;
};

bool my_queue::push(int input)
{
    values.push_back(input);
    // never fails
    return true;
}

bool my_queue::pop()
{
    if(!values.empty())
    {
        values.erase(values.begin());
        return true;
    }

    else
    {
        return false;
    }

}

int my_queue::front()
{
    return values.front();
}

bool my_queue::empty()
{
    return values.empty();
}

int my_queue::size()
{
    return values.size();
}
