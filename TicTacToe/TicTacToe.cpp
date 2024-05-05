#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

struct Players
{
    unsigned int id=0;
    char sign='1';
    unsigned int wins=0, draws=0, loses=0, points=0;
    
};
bool comparePlayers(const Players& p1, const Players& p2)
{
    return p1.points > p2.points; //malejace
}
void readPlayersFile(std::vector<Players> &vec,std::string file)
{
    std::ifstream f(file);
    for (int i = 0; !f.eof(); ++i)
    {
        Players p;
        f >> p.id;
        f >> p.sign;
        if (f.eof())
            break;
        vec.push_back(p);
    }
    f.close();
}
void ticTacToe(std::vector<Players>& vec, std::string file)
{
    std::ifstream f(file);
    std::string board[3];
    while (f >> board[0] >> board[1] >> board[2])
    {
        char p1='1', p2='1';
        for (int i = 0; i < 3; i++)
        {
            for (auto it : board[i])
            {
                if (p1 == '1' && it != '.')
                {
                    p1 = it;
                }
                else if (p2 == '1' && p1 != it && it != '.')
                {
                    p2 = it;
                }
                else if (p2 != '1' && p1 != '1')
                {
                    break;
                }
            }
        }
        bool p1Done = false, p2Done = false;
        for (int i = 0; i < 3; i++)
        {
            if ((board[i][0] == p1 && board[i][1] == p1 && board[i][2] == p1) ||
                (board[0][i] == p1 && board[1][i] == p1 && board[2][i] == p1) ||
                (board[0][0] == p1 && board[1][1] == p1 && board[2][2] == p1) ||
                (board[0][2] == p1 && board[1][1] == p1 && board[2][0] == p1))
            {
                for (auto& it : vec)
                {
                    if (it.sign == p1)
                    {
                        it.wins++;
                        p1Done = true;
                    }
                    if (it.sign == p2)
                    {
                        it.loses++;
                        p2Done = true;
                    }
                    if (p2Done && p1Done)
                    {
                        break;
                    }
                }
            }
            else if ((board[i][0] == p2 && board[i][1] == p2 && board[i][2] == p2) ||
                    (board[0][i] == p2 && board[1][i] == p2 && board[2][i] == p2) ||
                    (board[0][0] == p2 && board[1][1] == p2 && board[2][2] == p2) ||
                    (board[0][2] == p2 && board[1][1] == p2 && board[2][0] == p2))
            {
                
                for (auto& it : vec)
                {
                    if (it.sign == p1)
                    {
                        it.loses++;
                        p1Done = true;
                    }
                    if (it.sign == p2)
                    {
                        it.wins++;
                        p2Done = true;
                    }
                    if (p2Done && p1Done)
                    {
                        break;
                    }
                }
            }
            if (!p1Done && !p2Done)
            {
                for (auto& it : vec)
                {
                    if (it.sign == p1 || it.sign == p2)
                    {
                        it.draws++;
                    }
                }
            }
        }
    }
    for (auto& player : vec) 
    {
        player.points = player.wins * 3 + player.draws;
    }
    std::sort(vec.begin(), vec.end(), comparePlayers);
}
void mainLoop(std::vector<Players>& vec , std::string file)
{
    int option=-1;
    do
    {   
        printf("1 - Show table\n");
        printf("2 - Show results\n");
        printf("3 - Player stats\n");
        printf("4 - Exit\n");
        printf("Choose option: ");
        std::cin >> option;
        if (option == 1)
        {
            for (auto &it : vec)
            {
                std::cout << it.id << " " << it.sign << " " << it.wins << " " << it.draws << " " << it.loses <<" " << it.points << "\n";
            }
            printf("\n");
        }
        else if (option == 2)
        {
            std::ifstream f(file); 
            std::string s;
            for(int i=0;f>>s;i++)
            {
                if (i%3==0&&i!=0)
                {
                    printf("\n");
                }
                std::cout << s << "\n";
            }
            printf("\n");
        }
        else if (option == 3)
        {
            unsigned int id;
            printf("Enter player ID: ");
            std::cin >> id;
            bool done = false;
            for (auto& it : vec)
            {
                if (it.id == id)
                {
                    std::cout << it.id << " " << it.sign << " " << it.wins << " " << it.draws << " " << it.loses << " " << it.points << "\n";
                    done = true;
                }
                else
                {
                    break;
                }
            }
            if (!done)
            {
                printf("We didn't find any player with that id");
            }
            printf("\n");
        }
        else if (option != 4)
        {
            printf("\nNiewlasciwa opcja\n\n");
        }
    }while (option!=4);
}
int main()
{
    std::vector<Players> players;
    readPlayersFile(players, "files/players.txt");
    ticTacToe(players, "files/tictactoe.txt");
    mainLoop(players, "files/tictactoe.txt");
    return 0;
}