#include <string.h>
#include "Sudoku.h"
#include <algorithm>
#include <random>
#include <string>
#include <unistd.h>

Sudoku::Sudoku()
{
    memset(m_Board, 0, sizeof m_Board);

    for (int x = 2; x < WIDTH; ++x)
    {
        m_Board[x][1]			= WALL;
        m_Board[x][HEIGHT - 1]	= WALL;
    }
    for (int y = 2; y < HEIGHT-1; ++y)
    {
        m_Board[2][y]		= WALL;
        m_Board[3][y]		= WALL;

        m_Board[WIDTH-1][y]	= WALL;
        m_Board[WIDTH-2][y]		= WALL;
    }
    initScreen();
}
void Sudoku::initScreen()
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
//	timeout(0);
    start_color();

    //use_default_colors();
    init_pair(1, COLOR_BLUE, COLOR_GREEN);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLUE);
    init_pair(6, COLOR_WHITE, COLOR_YELLOW);
    wbkgd(stdscr, COLOR_PAIR(4));

}

void Sudoku::createEmptyTable()
{
    for (int x = 2; x < WIDTH; ++x)
    {
        for (int y = 1; y < HEIGHT; ++y)
        {

            if (getBoard(x, y) == WALL) {
                mvaddch(y, x, (chtype)(ACS_VLINE) | COLOR_PAIR(1));
            } else {

                mvaddch(y, x, (chtype)(' '));
            }

        }
    }

    for (int x = 4, y1 = 0, y = 4; y1 < 8; y1++) {
        if ((y1 + 1) % 3 == 0) {
            mvhline(y, x, ACS_HLINE | COLOR_PAIR(2), 37);
        } else {

            mvhline(y, x, ACS_HLINE | COLOR_PAIR(3), 37);
        }

        y += 2;
    }
    for (int y = 2, x1 = 0, x = 8; x1 < 8; x1++) {
        if ((x1 + 1) % 3 == 0) {
            mvvline(y, x, ACS_VLINE | COLOR_PAIR(2), 19);

        } else {
            mvvline(y, x, ACS_VLINE | COLOR_PAIR(3), 19);
        }
        x += 4;
    }


    refresh();
}

void Sudoku::print_instruction() {

    win = newwin(20, 31, 2, 47);
    char* mes = "E: Generate an Easy problem\n"
                 "  M: Generate a Middle problem\n"
                 "  H: Generate a Hard problem\n"
                 "  I: Invent a Sudoku problem\n"
                 "  F: Finish making a problem\n"
                 "  C: Clear sudoku\n\n"
                 "  Enter: Solve this problem\n\n"
                 "  Mouse click: Enter a number\n"
                 "  Arrow keys: Move the cursor\n"
                 "  Tab: Move the cursor ->\n"
                 "  Del, BackSpace, Spacebar, 0:\n"
                 "  --Delete the entered number\n\n"
                 "  ESC: Exit";

    mvwaddstr(win, 2, 2, mes);
    box(win, ACS_VLINE, ACS_HLINE);
    mvwaddstr(win, 0, 12, "Usage");
    touchwin(win);
    wrefresh(win);
}

bool Sudoku::checkCoursor(int x, int y){

    return (x % 4 == 2 and y % 2 == 1);
}


void Sudoku::move_up() {
    int x, y;
    getyx(stdscr, y, x);
    if (checkCoursor(x, y) and y > 3 ) {
        if (create_mode) {
            if (create_solution) {
                int y1 = 2;
                while (create_mode_puzzle[x/4-1][(y-y1)/2-1] != 0) {
                    if (getBoard(x, y - y1 - 2) == WALL){
                        y1 = 0;
                        break;
                    }
                    y1 += 2;
                }
                wmove(stdscr, y - y1, x);
            } else
                wmove(stdscr, y - 2, x);
        } else {
            if (generated_puzzle[x/4-1][(y - 2)/2-1] != 0) {
                int y1 = 2;
                while (generated_puzzle[x/4-1][(y-y1)/2-1] != 0) {
                    if (getBoard(x, y - y1 - 2) == WALL){
                        y1 = 0;
                        break;
                    }
                    y1 += 2;
                    }
                    wmove(stdscr, y - y1, x);
            } else {
                wmove(stdscr, y - 2, x);
            }
        }
    }
    curs_set(1);
}

void Sudoku::move_down() {
    int x, y;
    getyx(stdscr, y, x);
    if (checkCoursor(x, y) and y < HEIGHT - 3) {
        if (create_mode) {
            if (create_solution) {
                int y1 = 2;
                while (create_mode_puzzle[x/4-1][(y+y1)/2-1] != 0) {
                    if (getBoard(x, y + y1 + 2) == WALL){
                        y1 = 0;
                        break;
                    }
                    y1 += 2;
                }
                wmove(stdscr, y + y1, x);
            } else
                wmove(stdscr, y + 2, x);
        } else {
            if (generated_puzzle[x/4-1][(y + 2)/2-1] != 0) {
                int y1 = 2;
                while (generated_puzzle[x/4-1][(y+y1)/2-1] != 0) {
                    if (getBoard(x, y + y1 + 2) == WALL){
                        y1 = 0;
                        break;
                    }
                    y1 += 2;
                    }
                    wmove(stdscr, y + y1, x);
            } else {
                wmove(stdscr, y + 2, x);
            }
        }
    }
    curs_set(1);
}

void Sudoku::move_left() {
    int x, y;
    getyx(stdscr, y, x);
    if (checkCoursor(x, y) and x > 6) {
        if (create_mode) {
            if (create_solution) {
                int x1 = 4;
                while (create_mode_puzzle[(x-x1)/4-1][y/2-1] != 0) {
                    if (getBoard(x - x1 - 4, y) == WALL){
                        x1 = 0;
                        break;
                    }
                    x1 += 4;
                }
                wmove(stdscr, y, x - x1);
            } else
                wmove(stdscr, y, x - 4);
        } else {
            if (generated_puzzle[(x-4)/4-1][y/2-1] != 0) {
                int x1 = 4;
                while (generated_puzzle[(x - x1)/4-1][(y)/2-1] != 0) {
                    if (getBoard(x - x1 - 4, y) == WALL){
                        x1 = 0;
                        break;
                    }
                    x1 += 4;
                    }
                    wmove(stdscr, y, x - x1);
            } else {
                wmove(stdscr, y, x - 4);
            }
        }
    }
    curs_set(1);
}

void Sudoku::move_right() {
    int x, y;
    getyx(stdscr, y, x);
    if (checkCoursor(x, y) and x < WIDTH - 5) {
        if (create_mode) {
            if (create_solution) {
                int x1 = 4;
                while (create_mode_puzzle[(x+x1)/4-1][y/2-1] != 0) {
                    if (getBoard(x + x1 + 4, y) == WALL){
                        x1 = 0;
                        break;
                    }
                    x1 += 4;
                }
                wmove(stdscr, y, x + x1);
            } else
                wmove(stdscr, y, x + 4);
        } else {
            if (generated_puzzle[(x+4)/4-1][y/2-1] != 0) {
                int x1 = 4;
                while (generated_puzzle[(x + x1)/4-1][(y)/2-1] != 0) {
                    if (getBoard(x + x1 + 4, y) == WALL){
                        x1 = 0;
                        break;
                    }
                    x1 += 4;
                    }
                    wmove(stdscr, y, x + x1);
            } else {
                wmove(stdscr, y, x + 4);
            }
        }
    }
    curs_set(1);
}

void Sudoku::fill_puzzle(vector<int8_t> row) {
    for (int i = 0; i < 9; i++) {
        row.push_back(row[0]);
        row.erase(row.begin());
        solution[i] = row;
    }
}


bool Sudoku::check_solution(vector<vector<int8_t>> sudoku)
{
    int is_row_sum = 1, is_col_sum = 1, is_diag1_sum = 1, is_diag2_sum = 1;

    for (int col = 0; col < 9; col++) {
        int row_sum = 0, col_sum = 0;
        for (int row = 0; row < 9; row++) {
            row_sum += sudoku[col][row];
            col_sum += sudoku[row][col];


        }
        if(row_sum != 45) {
            is_row_sum = 0;
        }
        if(col_sum != 45) {
            is_row_sum = 0;
        }
    }
    for (int col = 0; col < 9; col += 3) {
        for (int row = 0; row < 9; row += 3) {
            int s = 0;
            for (int counter_i = 0; counter_i < 3; counter_i ++){
                for (int counter_j = 0; counter_j < 3; counter_j ++){
                  s += sudoku[col + counter_i][row + counter_j];
                }
            }
            if (s != 45){

                return false;
            }
        }
    }
    if (is_row_sum and is_col_sum) {
            return true;
    }
    else {
        return false;
    }
}

void Sudoku::empty_puzzle(int level, vector<int8_t> index, default_random_engine rng) {

    shuffle(begin(index), end(index), rng);
    index.insert(index.begin(), 0);
    index.pop_back();
    while (true) {
        for (int i = 0; i < 9; i++) {
            shuffle(begin(index), end(index), rng);
            if (level == 0) {
                return;
            }
            if (generated_puzzle[i][index[1]] != 0) {
                generated_puzzle[i][index[1]] = 0;
                level--;
            }
        }
    }

}

void Sudoku::generate_sudoku() {
    vector<int8_t> row{1, 2, 3, 4, 5, 6, 7, 8, 9};

    random_device rd;
    auto rng = default_random_engine { rd() };
    shuffle(begin(row), end(row), rng);
    fill_puzzle(row);
    while (!check_solution(solution)) {
        shuffle(begin(solution), end(solution), rng);
    }


}

void Sudoku::show_puzzle_on_board(int level) {
    vector<int8_t> row{1, 2, 3, 4, 5, 6, 7, 8, 9};
    random_device rd;
    auto rng = default_random_engine { rd() };
    generated_puzzle = solution;
    empty_puzzle(level, row, rng);

    for (int i = 0, x = 6; x < WIDTH - 3; x += 4, i++)
    {
        for (int j = 0, y = 3; y < HEIGHT - 1; y += 2, j++)
        {

            if (generated_puzzle[i][j] == 0) {
                mvaddch(y, x, (' '));
            } else {

                mvaddch(y, x, (generated_puzzle[i][j] + '0') | COLOR_PAIR(5));
            }



        }
    }
}
void Sudoku::show_solution_on_board(vector<vector<int8_t>> sudoku) {
    for (int i = 0, x = 6; x < WIDTH - 3; x += 4, i++)
    {
        for (int j = 0, y = 3; y < HEIGHT - 1; y += 2, j++)
        {
                if (sudoku[i][j] == 0) {
                    mvaddch(y, x, (solution[i][j] + '0') | COLOR_PAIR(6));
                }

        }
    }
}

bool Sudoku::check_created_sudoku() {

    for (int i = 0; i < 9; i++) {

              for (int j = 1; j < 10; j++) {
                  if (count(create_mode_puzzle[i].begin(),
                            create_mode_puzzle[i].end(), j) > 1) {
                      return false;
                  }
              }
    }
        vector<int8_t> nums;
        for (int i = 0; i < 9; i++) {

            for (int j = 0; j < 9; j++) {
                if (create_mode_puzzle[j][i] != 0) {
                    nums.push_back(create_mode_puzzle[j][i]);

                }
            }
            for (int j = 0; j < 9; j++) {
                if (count(nums.begin(), nums.end(), j) > 1) {
                    return false;
                }
            }
            nums.clear();

        }
          for (int col = 0; col < 9; col += 3) {
              for (int row = 0; row < 9; row += 3) {
                  int s = 0;
                  for (int counter_i = 0; counter_i < 3; counter_i ++){
                      for (int counter_j = 0; counter_j < 3; counter_j ++){

                        if (create_mode_puzzle[col + counter_i][row + counter_j] != 0) {
                          nums.push_back(create_mode_puzzle[col + counter_i][row + counter_j]);

                        }
                      }
                  }
                  for (int j = 0; j < 9; j++) {
                      if (count(nums.begin(), nums.end(), j) > 1) {
                          return false;
                      }
                  }
                  nums.clear();
              }
          }
          return true;



}

void Sudoku::generate_created_sudoku(){
    while (true) {
        generate_sudoku();
        int counter = 0, counter2 = 0;
        for (int i = 0; i < 9; i ++) {
            for (int j =0; j < 9; j ++) {
                if (create_mode_puzzle[i][j] != 0 and
                        create_mode_puzzle[i][j] == solution[i][j])
                    counter++;

                if (create_mode_puzzle[i][j] != 0)
                    counter2++;

            }
        }
        if (counter == counter2) {
            break;
        }
    }
}

void Sudoku::print_num(int num) {
    int x, y;
    getyx(stdscr, y, x);
    if (x > 5 and x < WIDTH - 4 and y > 2 and y < HEIGHT - 2) {
        generated_solution[x/4-1][y/2-1] = num;
        mvaddch(y, x, num + '0'  | COLOR_PAIR(6));
        wmove(stdscr, y, x);
    }
    bool is_zero = false;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (generated_puzzle[i][j] == 0 && generated_solution[i][j] == 0)
                is_zero = true;
        }
    }
    if (!is_zero) {
        curs_set(0);
        WINDOW *w = newwin(3, 27, 10, 30);
        box(w, ACS_VLINE, ACS_HLINE);
        merge_matrix(generated_puzzle, generated_solution);
        if (check_solution(generated_puzzle))
           mvwaddstr(w, 1, 2, "You win!");
        else
           mvwaddstr(w, 1, 2, "You lost!");

        touchwin(w);
        wrefresh(w);
        sleep(4);
        touchwin(stdscr);
        wrefresh(stdscr);
        touchwin(win);
        wrefresh(win);
    }


}



void Sudoku::add_num_create_mode_puzzle(int num) {
    int x, y;
    getyx(stdscr, y, x);
    if (x > 5 and x < WIDTH - 4 and y > 2 and y < HEIGHT - 2) {
        create_mode_puzzle[x/4-1][y/2-1] = num;
        mvaddch(y, x, num + '0'  | COLOR_PAIR(5));
    }
    wmove(stdscr, y, x);
}

void Sudoku::add_num_create_mode_solution(int num) {
    int x, y;
    getyx(stdscr, y, x);
    if (x > 5 and x < WIDTH - 4 and y > 2 and y < HEIGHT - 2) {
        create_mode_solution[x/4-1][y/2-1] = num;
        mvaddch(y, x, num + '0'  | COLOR_PAIR(6));
    }
    wmove(stdscr, y, x);
    bool is_zero = false;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (create_mode_puzzle[i][j] == 0 && create_mode_solution[i][j] == 0)
                is_zero = true;
        }
    }
    if (!is_zero) {
        curs_set(0);
        WINDOW *w = newwin(3, 27, 10, 30);
        box(w, ACS_VLINE, ACS_HLINE);
        merge_matrix(create_mode_puzzle, create_mode_solution);
        if (check_solution(create_mode_puzzle))
           mvwaddstr(w, 1, 2, "You win!");
        else
           mvwaddstr(w, 1, 2, "You lost!");

        touchwin(w);
        wrefresh(w);
        sleep(4);
        touchwin(stdscr);
        wrefresh(stdscr);
        touchwin(win);
        wrefresh(win);
    }

}

void Sudoku::merge_matrix(vector<vector<int8_t>> puzzle, vector<vector<int8_t>> solution) {
    int x, y;
    getyx(stdscr, y, x);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (solution[i][j] != 0) {
                puzzle[i][j] = solution[i][j];
                mvaddch((j+1)*2+1, (i+1)*4 + 2, puzzle[i][j] + '0'  | COLOR_PAIR(5));

            }
        }
    }
    wmove(stdscr, y, x);
}

void Sudoku::moveCursor() {

    keypad(stdscr, TRUE);
    int ch;
    mousemask(ALL_MOUSE_EVENTS|REPORT_MOUSE_POSITION, NULL);

    ch = getch();
    int x, y;
    switch(ch) {
        case KEY_MOUSE:
            MEVENT event;
            if (getmouse(&event) == OK) {
                if (event.bstate & BUTTON1_CLICKED) {
                    x = event.x;
                    y = event.y;
                    if (event.x % 4 == 2 and event.y % 2 == 1 and
                            generated_puzzle[x/4-1][y/2-1] == 0) {
                        wmove(stdscr, event.y, event.x);
                        curs_set(1);
                    }
                    if (event.x > WIDTH - 4 || event.y > HEIGHT - 2 ||
                        event.x < 2 || event.y < 1) {
                        wmove(stdscr, event.y, event.x);
                        curs_set(0);
                    }

                }

            }
            break;
        case KEY_UP:
            move_up();
            y = y - 2;

            break;
        case KEY_DOWN:
            move_down();
            y = y + 2;
            break;
        case KEY_LEFT:
            move_left();
            x = x - 4;

            break;
        case KEY_RIGHT:
        case '\t':
            move_right();
            x = x + 4;
            break;
        case 27:
            exit = true;
            return;
            break;
        case 69:
        case 101:
            generate_mode = true;
            getyx(stdscr, y, x);
            generate_sudoku();
            show_puzzle_on_board(47);
            wmove(stdscr, y, x);
            create_mode = false;
            break;
        case 77:
        case 109:
            generate_mode = true;
            getyx(stdscr, y, x);
            generate_sudoku();
            show_puzzle_on_board(50);
            wmove(stdscr, y, x);
            create_mode = false;
            break;
        case 72:
        case 104:
            generate_mode = true;
            getyx(stdscr, y, x);
            generate_sudoku();
            show_puzzle_on_board(53);
            wmove(stdscr, y, x);
            create_mode = false;
            break;
        case 1 + '0':
            if (create_mode) {
                if (create_solution) {
                    add_num_create_mode_solution(1);
                } else {
                    merge_matrix(create_mode_puzzle, create_mode_solution);
                    add_num_create_mode_puzzle(1);
                }
            } else {
                print_num(1);
            }
            break;
        case 2 + '0':
            if (create_mode) {
                if (create_solution) {
                    add_num_create_mode_solution(2);
                } else {
                    merge_matrix(create_mode_puzzle, create_mode_solution);
                    add_num_create_mode_puzzle(2);
                }
            } else {
                print_num(2);
            }
            break;
        case 3 + '0':
            if (create_mode) {
                if (create_solution) {
                    add_num_create_mode_solution(3);
                } else {
                    merge_matrix(create_mode_puzzle, create_mode_solution);
                    add_num_create_mode_puzzle(3);
                }
            } else {
                print_num(3);
            }
            break;
        case 4 + '0':
            if (create_mode) {
                if (create_solution) {
                    add_num_create_mode_solution(4);
                } else {
                    merge_matrix(create_mode_puzzle, create_mode_solution);
                    add_num_create_mode_puzzle(4);
                }
            } else {
                print_num(4);
            }
            break;
        case 5 + '0':
            if (create_mode) {
                if (create_solution) {
                    add_num_create_mode_solution(5);
                } else {
                    merge_matrix(create_mode_puzzle, create_mode_solution);
                    add_num_create_mode_puzzle(5);
                }
            } else {
                print_num(5);
            }
            break;
        case 6 + '0':
            if (create_mode) {
                if (create_solution) {
                    add_num_create_mode_solution(6);
                } else {
                    merge_matrix(create_mode_puzzle, create_mode_solution);
                    add_num_create_mode_puzzle(6);
                }
            } else {
                print_num(6);
            }
            break;
        case 7 + '0':
            if (create_mode) {
                if (create_solution) {
                    add_num_create_mode_solution(7);
                } else {
                    merge_matrix(create_mode_puzzle, create_mode_solution);
                    add_num_create_mode_puzzle(7);
                }
            } else {
                print_num(7);
            }
            break;
        case 8 + '0':
            if (create_mode) {
                if (create_solution) {
                    add_num_create_mode_solution(8);
                } else {
                    merge_matrix(create_mode_puzzle, create_mode_solution);
                    add_num_create_mode_puzzle(8);
                }
            } else {
                print_num(8);
            }
            break;
        case 9 + '0':
            if (create_mode) {
                if (create_solution) {
                    add_num_create_mode_solution(9);
                } else {
                    merge_matrix(create_mode_puzzle, create_mode_solution);
                    add_num_create_mode_puzzle(9);
                }
            } else {
                print_num(9);
            }
            break;
        case '\n':
            getyx(stdscr, y, x);


            if (create_mode) {
                if(check_created_sudoku()) {
                    generate_created_sudoku();
                    show_solution_on_board(create_mode_puzzle);


                } else {
                    curs_set(0);
                    WINDOW *w = newwin(3, 27, 10, 30);
                    box(w, ACS_VLINE, ACS_HLINE);
                    mvwaddstr(w, 1, 2, "Wrong Sudoku Problem!");

                    touchwin(w);
                    wrefresh(w);
                    sleep(4);
                    touchwin(stdscr);
                    wrefresh(stdscr);
                    touchwin(win);
                    wrefresh(win);
                }
            } else {
                show_solution_on_board(generated_puzzle);

            }
             wmove(stdscr, y, x);
            break;
        case KEY_BACKSPACE:
        case KEY_DC:
        case ' ':
        case '0':
            getyx(stdscr, y, x);
            mvaddch(y, x, ' ');
            if (create_mode) {
                if (create_solution)
                    create_mode_solution[x/4-1][y/2-1] = 0;
                else
                    create_mode_puzzle[x/4-1][y/2-1] = 0;
            } else {
                generated_solution[x/4-1][y/2-1] = 0;
            }
            wmove(stdscr, y, x);
            break;
        case 67:
        case 99: //C key is pressed
            getyx(stdscr, y, x);
            createEmptyTable();
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    generated_solution[i][j] = 0;
                    generated_puzzle[i][j] = 0;
                    solution[i][j] = 0;
                    create_mode_puzzle[i][j] = 0;
                    create_mode_solution[i][j] = 0;
                }
            }
            create_mode = true;
            generate_mode = false;
            wmove(stdscr, y, x);
            break;
        case 73:
        case 105: //I key is pressed
            if (!generate_mode) {
                create_mode = true;
                if (count_create_mode > 0) {
                    create_solution = false;
                    count_create_mode = 0;
                }
            }
            break;
        case 70:
        case 102: //F key is pressed

            create_solution = true;
            count_create_mode ++;
            break;



    }

    refresh();
}

void Sudoku::start() {
    createEmptyTable();
    print_instruction();
    while(TRUE) {
        moveCursor();
        if (exit)
           break;
    }
}


