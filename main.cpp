#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <stdlib.h>

using namespace std;

void pretty_print(vector<vector<int>> base);

int main(int argc, char const *argv[])
{
    vector<vector<int>> dimension_plot;
    int dimes[] = {20, 10};
    int score = 0;
    for (size_t i = 0; i < dimes[1]; i++)
    {
        for (size_t j = 0; j < dimes[0]; j++)
        {

            if (!dimension_plot.size())
                dimension_plot.push_back((vector<int>){(int)j});
            else
                dimension_plot.back().push_back(0);
        }
        dimension_plot.push_back((vector<int>){});
    }
    HANDLE rhnd = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events = 0;
    DWORD EventsRead = 0;
    int count = 0, dimension = 0, __size = 5;
    vector<vector<int>> tail_s = {{0, 0}}, apple_quad = {{rand() % 10, rand() % 19}};
    int lx = tail_s.back().front(), ly = tail_s.back().back() + 1; // * lx is y coord, ly is x coord
    vector<int> last_ev = {1};
    while (true)
    {
        system("CLS");
        cout << "Score: " << score << endl;
        while (tail_s.size() >= __size)
        {
            tail_s.erase(tail_s.begin());
        }
        dimension_plot[apple_quad[0].front()][apple_quad[0].back()] = 2;
        GetNumberOfConsoleInputEvents(rhnd, &Events);
        if (Events != 0)
        {
            INPUT_RECORD eventBuffer[Events];
            ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead);
            for (DWORD i = 0; i < EventsRead; ++i)
            {
                if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown)
                {
                    switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode)
                    {
                    case VK_LEFT:
                        ly--;
                        last_ev.push_back(0);
                        break;
                    case VK_RIGHT:
                        ly++;
                        last_ev.push_back(1);
                        break;
                    case VK_UP:
                        lx--;
                        last_ev.push_back(2);
                        break;
                    case VK_DOWN:
                        lx++;
                        last_ev.push_back(3);
                        break;
                    case VK_ESCAPE:
                        std::cout << "escape key pressed.\n";
                        exit(0);
                        break;

                    default:
                        //std::cout << "key not handled pressed.\n";
                        break;
                    }
                }
            }
        }
        else
        {
            switch (last_ev.back())
            {
            case 0:
                ly--;
                break;
            case 1:
                ly++;
                break;
            case 2:
                lx--;
                break;
            case 3:
                lx++;
                break;
            default:
                break;
            }
        }
        if (tail_s.back() != (vector<int>) {lx, ly})
        {
            int occurances = 0;
            for (size_t i = 0; i < tail_s.size(); i++)
                if (tail_s[i] == (vector<int>) {lx, ly})
                    occurances++;
            if (occurances != 1)
                tail_s.push_back((vector<int>){lx, ly});
            else
            {
                cout << "Oops, you bit yourself";
                break;
            }
        }
        /* if (find(tail_s.begin(), tail_s.end(), apple_quad.front()) != tail_s.end())
        {
            apple_quad.front() = (vector<int>) {rand() % 19, rand() % 9};
        } */
        bool c_true = false;
        for (auto x: tail_s)
        {
            if (x == apple_quad.front())
                c_true = true;
        }
        if (c_true)
        {
            score++;
            __size++;
            apple_quad.front() = (vector<int>) {rand() % 10, rand() % 19};
        }
        dimension_plot.clear();
        // cout << dimension_plot[apple_quad[0][0]][apple_quad[0][1]] << endl;
        for (size_t i = 0; i < dimes[1]; i++)
        {
            for (size_t j = 0; j < dimes[0]; j++)
            {

                if (!dimension_plot.size())
                    dimension_plot.push_back((vector<int>){(int)j});
                else
                    dimension_plot.back().push_back(0);
            }
            dimension_plot.push_back((vector<int>){});
        }
        dimension_plot[apple_quad[0][0]][apple_quad[0][1]] = 2;
        for (auto x: tail_s)
        {
            // cout << x[0] << ", " << x[1] << endl;
            dimension_plot[x[0]][x[1]] = 1;
        }
        for (size_t i = 0; i < dimes[0]; i++)
        {
            cout << "* ";
        }
        cout << endl;
        pretty_print(dimension_plot);
        for (size_t i = 0; i < dimes[0]; i++)
        {
            cout << "* ";
        }
        cout << endl;
        // apple_quad.back() = (vector<int>) {rand() % 5, rand() % 5};
        sleep(0.02);
    }
    return 0;
}

void pretty_print(vector<vector<int>> base)
{
    for (vector<int> x : base)
    {
        for (int y : x)
        {
            if (y == 1)
                cout << "* ";
            else if (y == 2)
                cout << "o ";
            else
                cout << "  ";
        }
        cout << endl;
    }
}