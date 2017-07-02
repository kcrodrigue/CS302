using namespace std;

struct Game_Type
{
    string name;
    int games_won;
    int win_rate;
    int games_played;
    int fastest_win;
    int fewest_moves;
    int top_score;
};

struct Player
{
    string name;
    vector<Game_Type> games;
    Game_Type overview;
};

class JSON
{
public:
    JSON();
    ~JSON();
    void parse(string);
    void print();
    bool valid_format(string);
private:
    void read_player(Player&,ifstream&);
    void read_games(int,Player&,ifstream&);
    void print_overview();
    void print_games();
    vector<Player> list_players;
};

JSON::JSON()
{
    list_players.resize(2);
    list_players[0].games.resize(3);
    list_players[1].games.resize(3);
}

JSON::~JSON()
{

}

void JSON::print()
{
    int index, index_two;
    ofstream fout("PlayerStatisticsUpdated.json");

    // print info to the terminal
    for(index = 0; index < 2; index++)
    {
        cout << list_players[index].name << endl;

        cout << list_players[index].overview.games_won << endl;
        cout << list_players[index].overview.win_rate << endl;
        cout << list_players[index].overview.games_played << endl;
        cout << list_players[index].overview.fastest_win << endl;
        cout << list_players[index].overview.fewest_moves << endl;
        cout << list_players[index].overview.top_score << endl;

        for(index_two = 0; index_two < 3; index_two++)
        {
            cout << "\t" << list_players[index].games[index_two].name << endl;
            cout << "\t" << list_players[index].games[index_two].games_won << endl;
            cout << "\t" << list_players[index].games[index_two].win_rate << endl;
            cout << "\t" << list_players[index].games[index_two].games_played << endl;
            cout << "\t" << list_players[index].games[index_two].fastest_win << endl;
            cout << "\t" << list_players[index].games[index_two].fewest_moves << endl;
            cout << "\t" << list_players[index].games[index_two].top_score << endl;
        }
    }

    // print info to new json file
    fout << "[{" << endl;

    for(index = 0; index < 2; index ++)
    {
        if(index == 1)
        {
            fout << ", {" << endl;
        }
        fout << "\t\"Player Name\": \"" << list_players[index].name << "\"," <<  endl;
        fout << "\t\"Overview\": {" << endl;

        fout << "\t\t\"Games Won\":" << list_players[index].overview.games_won << "," <<  endl;
        fout << "\t\t\"Win Rate\":" << list_players[index].overview.win_rate << "," <<  endl;
        fout << "\t\t\"Games Played\":" << list_players[index].overview.games_played << "," <<  endl;
        fout << "\t\t\"Fastest Win\":" << list_players[index].overview.fastest_win << "," <<  endl;
        fout << "\t\t\"Fewest Moves\":" << list_players[index].overview.fewest_moves << "," <<  endl;
        fout << "\t\t\"Top Score\":" << list_players[index].overview.top_score << "," <<  endl;

        fout << "\t}," << endl;

        fout << "\t\"Suits\": [{" << endl;
        for(index_two = 0; index_two < 3; index_two++)
        {
            if(index_two != 0)
            {
                fout << "\t\t{" << endl;
            }

            fout << "\t\t\t\"Games Won\":" << list_players[index].games[index_two].games_won << "," <<  endl;
            fout << "\t\t\t\"Win Rate\":" << list_players[index].games[index_two].win_rate << "," <<  endl;
            fout << "\t\t\t\"Games Played\":" << list_players[index].games[index_two].games_played << "," <<  endl;
            fout << "\t\t\t\"Fastest Win\":" << list_players[index].games[index_two].fastest_win << "," <<  endl;
            fout << "\t\t\t\"Fewest Moves\":" << list_players[index].games[index_two].fewest_moves << "," <<  endl;
            fout << "\t\t\t\"Top Score\":" << list_players[index].games[index_two].top_score << "," <<  endl;

            fout << "\t\t}," << endl;
        }

        fout << "\t]" << endl;
        fout << "}" ;
    }

    fout << "]" << endl;
}

void JSON::parse(string file_name)
{
    ifstream fin(file_name.c_str());
    char test_char;
    string test_string;
    int player_index = 0;


    // print players
    for(player_index = 0; player_index < 2; player_index++)
    {
        read_player(list_players[player_index], fin);
        read_games(3, list_players[player_index], fin);
    }

}

void JSON::read_player(Player &info, ifstream &fin)
{
    char test_char;
    int string_length = 0;

    fin >> test_char;

    fin.ignore(200, ':');

    fin >> test_char;

    fin >> info.name;

    while(info.name[string_length] != '\"')
    {
        string_length++;
    }

    info.name = info.name.substr(0, string_length);

    fin.ignore(200, '{');

    fin.ignore(200, ':');

    fin >> info.overview.games_won;

    fin >> test_char;

    fin.ignore(200, ':');

    fin >> info.overview.win_rate;

    fin >> test_char;

    fin.ignore(200, ':');

    fin >> info.overview.games_played;

    fin >> test_char;

    fin.ignore(200, ':');

    fin >> info.overview.fastest_win;

    fin >> test_char;

    fin.ignore(200, ':');

    fin >> info.overview.fewest_moves;

    fin >> test_char;

    fin.ignore(200, ':');

    fin >> info.overview.top_score;
}

void JSON::read_games(int num_games, Player &info, ifstream &fin)
{
    int index;
    char test_char;
    int string_length = 0;

    fin >> test_char;

    fin.ignore(200, '[');

    for(index = 0; index < num_games; index++)
    {

        fin.ignore(200, ':');

        fin >> test_char;

        getline(fin, info.games[index].name, '\"');

        fin.ignore(200, ':');

        fin >> info.games[index].games_won;

        fin >> test_char;

        fin.ignore(200, ':');

        fin >> info.games[index].win_rate;

        fin >> test_char;

        fin.ignore(200, ':');

        fin >> info.games[index].games_played;

        fin >> test_char;

        fin.ignore(200, ':');

        fin >> info.games[index].fastest_win;

        fin >> test_char;

        fin.ignore(200, ':');

        fin >> info.games[index].fewest_moves;

        fin >> test_char;

        fin.ignore(200, ':');

        fin >> info.games[index].top_score;
    }
}

bool JSON::valid_format(string file_name)
{
    stack<char> square_brackets;
    stack<char> curly_brackets;
    ifstream fin(file_name.c_str());
    char test_char;

    while(fin.good())
    {
        fin >> test_char;

        while(test_char != '[' || test_char != ']'
            ||test_char != '{' || test_char != '}')
            {
                switch(test_char)
                {
                    case '[':
                        square_brackets.push('[');
                        break;

                    case ']':
                        if(!square_brackets.empty())
                        {
                            square_brackets.pop();
                        }

                        else
                        {
                            return false;
                        }
                        break;

                    case '{':
                        curly_brackets.push('{');
                        break;

                    case '}':
                        if(!curly_brackets.empty())
                        {
                            curly_brackets.pop();
                        }

                        else
                        {
                            return false;
                        }
                        break;
                }
            }
    }
    return true;
}
