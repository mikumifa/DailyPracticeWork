#include <chrono>
#include <iostream>
#include <ncurses.h>
#include <unistd.h>// for usleep()
#include <vector>
#include <sys/ioctl.h>
#include <termios.h>
using namespace std;
 int my_set=11;
// Define some constants
const int MAP_WIDTH = 40;
const int MAP_HEIGHT = 20;
const int START_X = MAP_WIDTH / 2;
const int START_Y = MAP_HEIGHT / 2;
const int DELAY = 1000; // Delay in microseconds

// Define a structure for the snake segments
struct SnakeSegment {
    int x, y;
};
bool kbhit()
{
    termios term;
    tcgetattr(0, &term);

    termios term2 = term;
    term2.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term2);

    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);

    tcsetattr(0, TCSANOW, &term);

    return byteswaiting > 0;
}
const int AUTO_MOVE_DELAY = 1000; // time interval for automatic movement in microseconds
// Define the main function
int main() {
    // Initialize ncurses
    cout<<"choose the difficulty:"<<endl;
    cout<<"1. easy"<<endl;
    cout<<"2. normal"<<endl;
    cout<<"3. hard"<<endl;
    cin>>my_set;
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);
    curs_set(0);

    // Create the window
    WINDOW* win = newwin(MAP_HEIGHT+2, MAP_WIDTH+2, 0, 0);
    box(win, 0, 0);
    wrefresh(win);

    // Initialize the snake
    vector<SnakeSegment> snake;
    snake.push_back({START_X, START_Y});

    // Initialize the direction
    int direction = KEY_RIGHT;

    // Initialize the food
    int food_x = 0, food_y = 0;
    srand(time(NULL)); // Seed the random number generator
    while (true) {
        food_x = rand() % MAP_WIDTH;
        food_y = rand() % MAP_HEIGHT;
        bool collision = false;
        for (int i = 0; i < snake.size(); ++i) {
            if (snake[i].x == food_x && snake[i].y == food_y) {
                collision = true;
                break;
            }
        }
        if (!collision) break;
    }

    // Main loop
    bool running = true;
    auto last_move_time = std::chrono::system_clock::now(); // 记录上一次蛇移动的时间
    while (running) {
        // Clear the screen
        wclear(win);
        box(win, 0, 0);

        if(kbhit()){
            // Process input
            int ch = getch();
            switch (ch) {
                case KEY_UP:
                    if (direction != KEY_DOWN)
                        direction = KEY_UP;
                    break;
                case KEY_DOWN:
                    if (direction != KEY_UP)
                        direction = KEY_DOWN;
                    break;
                case KEY_LEFT:
                    if (direction != KEY_RIGHT)
                        direction = KEY_LEFT;
                    break;
                case KEY_RIGHT:
                    if (direction != KEY_LEFT)
                        direction = KEY_RIGHT;
                    break;
                case 'q':
                case 'Q':
                    running = false;
                    break;
                default:
                    break;
            }
        } else{
            sleep((1-(snake.size()) / (snake.size() +1))/(double)my_set);
        }


        // Move the snake
        int dx = 0, dy = 0;
        switch (direction) {
            case KEY_UP:
                dy = -1;
                break;
            case KEY_DOWN:
                dy = 1;
                break;
            case KEY_LEFT:
                dx = -1;
                break;
            case KEY_RIGHT:
                dx = 1;
                break;
            default:
                break;
        }
        // 计算时间差，如果时间差大于预设的时间间隔，蛇就会自动往前移动一格
        auto now = std::chrono::system_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(now - last_move_time).count();
        if (elapsed_time > AUTO_MOVE_DELAY) {
            int x = snake.front().x + dx;
            int y = snake.front().y + dy;
            snake.insert(snake.begin(), {x, y});

            if (x == food_x && y == food_y) {
                while (true) {
                    food_x = rand() % MAP_WIDTH;
                    food_y = rand() % MAP_HEIGHT;
                    bool collision = false;
                    for (int i = 0; i < snake.size(); ++i) {
                        if (snake[i].x == food_x && snake[i].y == food_y) {
                            collision = true;
                            break;
                        }
                    }
                    if (!collision) break;
                }
            } else {
                snake.pop_back();
            }
            // Check for collision with the walls
            if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
                running = false;
            }

            // Check for collision with the snake
            for (int i = 1; i < snake.size(); ++i) {
                if (x == snake[i].x && y == snake[i].y) {
                    running = false;
                    break;
                }
            }


            // Draw the snake
            for (int i = 0; i < snake.size(); ++i) {
                mvwaddch(win, snake[i].y + 1, snake[i].x + 1, ACS_BLOCK);
            }

            // Refresh the window
            mvwaddch(win, food_y + 1, food_x + 1, 'X');
            wrefresh(win);

            // Sleep for a bit
            usleep(DELAY);
        }
    }
    // Clean up
    delwin(win);
    endwin();
    cout << "Game over!" << endl;
    cout << "Your score is: " << snake.size() - 1 << endl;
    return 0;
}
