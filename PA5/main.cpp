#include <iostream>
#include <fstream>
#include <stdlib.h> // NULL
#include <stdio.h>  // srand, rand
#include <time.h>   // time for random numbers
#include <vector>   // vectors instead of arrays
#include "insertion.cpp"
#include "myqueue.cpp"
#include "priority_queue.cpp"

int simulation_one_run(priority_queue events, ofstream& log_file);

int simulation_two_run(priority_queue events, ofstream& log_file);

int simulation_three_run(priority_queue events, ofstream& log_file);

void new_numbers(priority_queue& events, vector<int>& event_arrival, vector<int>& event_duration, ofstream& data_output, int &data_set);

using namespace std;


int main()
{
    vector<int> event_arrival;
    vector<int> event_duration;
    priority_queue events;
    ofstream data_output("data.txt");
    ofstream log_file("log.txt");
    int temp_one, temp_two;
    int time_taken, user_selection;
    int index, data_set = 1;
    bool continue_program = true;

    // random specification
    srand(time(NULL));

    // create events
    new_numbers(events, event_arrival, event_duration, data_output, data_set);

    while(continue_program)
    {
        cout << "Select what to do:" << endl <<
                 "1. Simulation one (1 queue, 1 teller)" << endl <<
                 "2. Simulation two (3 queues, 3 tellers)" << endl <<
                 "3. Simulation three (1 queue, 3 tellers)" << endl <<
                 "4. Load new numbers" << endl <<
                 "5. Exit program" << endl <<
                 "Enter number 1-5:" ;

        cin >> user_selection;

        cout << endl << endl << endl;

        switch(user_selection)
        {
            case 1:
                // run simulation one
                time_taken = simulation_one_run(events, log_file);
                cout << "This simulation took " << time_taken << " time units\n" ;
                break;

            case 2:
                // run simulation two
                time_taken = simulation_two_run(events, log_file);
                cout << "This simulation took " << time_taken << " time units\n" ;
                break;

            case 3:
                // run simulation three
                time_taken = simulation_three_run(events, log_file);
                cout << "This simulation took " << time_taken << " time units\n" ;
                break;
            case 4:
                new_numbers(events, event_arrival, event_duration, data_output, data_set);
                break;
            case 5:
                continue_program = false;
        }

    }

    return 0;
}


int simulation_one_run(priority_queue events, ofstream& log_file)
{
    int t1_arrival = -1;
    int teller_one = -1;
    int time_index = 0;
    my_queue simulation_one;
/*  SIMULATION 1
        This will count how many seconds it takes to get through all the products
        it will stop the loop if the queue is empty, and no more arrivals,
        hence the while(true) */
    while(true)
    {
        // New arrival check
        while(events.front() == time_index)
        {
            // person gets in line
            simulation_one.push(events.front_duration());
            log_file << time_index << " Person got in line. " << endl;
            events.pop();
        }

        // check if teller is not empty
        if(teller_one != -1)
        {
            // check if teller is finished
            if(t1_arrival + teller_one == time_index )
            {
                // person leaves
                teller_one = -1;
                log_file << time_index << " Person left teller." << endl;
            }
        }

        // fill empty teller with front of queue
        if(teller_one == -1 && !simulation_one.empty())
        {
            teller_one = simulation_one.front();
            simulation_one.pop();
            log_file << time_index << " Person started talking to teller" << endl;
            t1_arrival = time_index;
        }

        else if(teller_one == -1 && simulation_one.empty() && time_index > 540)
        {
            // end loop
            log_file << time_index << " End of simulation" << endl;
            break;

        }

        time_index++;
    }
    return time_index;
}


int simulation_two_run(priority_queue events, ofstream& log_file)
{
    int t1_arrival = -1;
    int t2_arrival = -1;
    int t3_arrival = -1;
    int teller_one = -1;
    int teller_two = -1;
    int teller_three = -1;
    int time_index = 0;
    int index, smallest_queue;
    my_queue simulation_two[3];

/*  SIMULATION 2
        This will count how many seconds it takes to get through all the products
        it will stop the loop if the queue is empty, and no more arrivals,
        hence the while(true) */
    while(true)
    {
        // New arrival check
        while(events.front() == time_index)
        {
            // find smallest queue
            smallest_queue = 0;
            for(index = 0; index < 3; index++)
            {
                if(simulation_two[index].size() < simulation_two[smallest_queue].size())
                {
                    smallest_queue = index;
                }
            }
            simulation_two[smallest_queue].push(events.front_duration());
            events.pop();
            log_file << time_index << " Person got in line " << smallest_queue +1<< endl;

        }

        // check if tellers are not empty
        if(teller_one != -1)
        {
            // check if teller is finished
            if(t1_arrival + teller_one == time_index )
            {
                // person leaves
                teller_one = -1;
                log_file << time_index << " Person left teller 1." << endl;
            }
        }

        if(teller_two != -1)
        {
            // check if teller is finished
            if(t2_arrival + teller_two == time_index )
            {
                // person leaves
                teller_two = -1;
                log_file << time_index << " Person left teller 2." << endl;
            }
        }

        if(teller_three != -1)
        {
            // check if teller is finished
            if(t3_arrival + teller_three == time_index )
            {
                // person leaves
                teller_three = -1;
                log_file << time_index << " Person left teller 3." << endl;
            }
        }

        // fill empty teller with front of queue
        if(teller_one == -1 && !simulation_two[0].empty())
        {
            teller_one = simulation_two[0].front();
            simulation_two[0].pop();
            log_file << time_index << " Person started talking to teller" << endl;
            t1_arrival = time_index;
        }

        if(teller_two == -1 && !simulation_two[1].empty())
        {
            teller_two = simulation_two[1].front();
            simulation_two[1].pop();
            log_file << time_index << " Person started talking to teller" << endl;
            t2_arrival = time_index;
        }

        if(teller_three == -1 && !simulation_two[2].empty())
        {
            teller_three = simulation_two[2].front();
            simulation_two[2].pop();
            log_file << time_index << " Person started talking to teller" << endl;
            t3_arrival = time_index;
        }

        if(teller_one == -1 && simulation_two[0].empty() && time_index > 540 &&
           teller_two == -1 && simulation_two[1].empty() &&
           teller_three == -1 && simulation_two[2].empty())
        {
            // end loop
            log_file << time_index << " End of simulation" << endl;
            break;
        }


        time_index++;
    }

    return time_index;
}


int simulation_three_run(priority_queue events, ofstream& log_file)
{
    int t1_arrival = -1;
    int t2_arrival = -1;
    int t3_arrival = -1;
    int teller_one = -1;
    int teller_two = -1;
    int teller_three = -1;
    int time_index = 0;
    int index, smallest_queue;
    my_queue simulation_three;

/*  SIMULATION 3
        This will count how many seconds it takes to get through all the products
        it will stop the loop if the queue is empty, and no more arrivals,
        hence the while(true) */
    while(true)
    {
        // New arrival check
        while(events.front() == time_index)
        {
            // person gets in line
            simulation_three.push(events.front_duration());
            events.pop();
            log_file << time_index << " Person got in line. " << endl;
        }

        // check if teller is not empty
        if(teller_one != -1)
        {
            // check if teller is finished
            if(t1_arrival + teller_one == time_index )
            {
                // person leaves
                teller_one = -1;
                log_file << time_index << " Person left teller 1." << endl;
            }
        }
        if(teller_two != -1)
        {
            // check if teller is finished
            if(t2_arrival + teller_two == time_index )
            {
                // person leaves
                teller_two = -1;
                log_file << time_index << " Person left teller 2." << endl;
            }
        }
        if(teller_three != -1)
        {
            // check if teller is finished
            if(t3_arrival + teller_three == time_index )
            {
                // person leaves
                teller_three = -1;
                log_file << time_index << " Person left teller 3." << endl;
            }
        }

        // fill empty teller with front of queue
        if(teller_one == -1 && !simulation_three.empty())
        {
            teller_one = simulation_three.front();
            simulation_three.pop();
            log_file << time_index << " Person started talking to teller 1" << endl;
            t1_arrival = time_index;
        }
        if(teller_two == -1 && !simulation_three.empty())
        {
            teller_two = simulation_three.front();
            simulation_three.pop();
            log_file << time_index << " Person started talking to teller 2" << endl;
            t2_arrival = time_index;
        }
        if(teller_three == -1 && !simulation_three.empty())
        {
            teller_three = simulation_three.front();
            simulation_three.pop();
            log_file << time_index << " Person started talking to teller 3" << endl;
            t3_arrival = time_index;
        }


        else if(teller_one == -1 && teller_two == -1 && teller_three == -1
                && simulation_three.empty() && time_index > 540)
        {
            // end loop
            log_file << time_index << " End of simulation" << endl;
            break;

        }

        time_index++;
    }

    return time_index;
}


void new_numbers(priority_queue& events, vector<int>& event_arrival, vector<int>& event_duration, ofstream& data_output, int &data_set)
{
    int index, temp_one, temp_two;

    while(!events.empty())
    {
        events.pop();
    }
    event_arrival.erase(event_arrival.begin(), event_arrival.end());
    event_duration.erase(event_duration.begin(), event_duration.end());
    for(index = 0; index < 100; index++)
    {
        temp_one =  rand() % 540 + 1;
        temp_two =  rand() % 20 + 1;
        events.push(temp_one, temp_two);
        // start time
        event_arrival.push_back(temp_one);

        // duration
        event_duration.push_back(temp_two);
    }

    // sort arrival times
    insertion_sort(event_arrival, event_duration);

    data_output << "Data set " << data_set << ":" << endl;

    for(index = 0; index < 100; index++)
    {
        // start time
        data_output << event_arrival[index] << "\t";

        // duration
        data_output << event_duration[index] << endl;
    }
    data_set++;
}
