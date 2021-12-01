#pragma once
#include <ncurses.h>
#include <stdint.h>
#include <vector>
#include <random>

#define WIDTH	(43)
#define HEIGHT	(22)
#define WALL	(-1)

using namespace std;
class Sudoku {
    WINDOW *win;
    int8_t	m_Board[WIDTH][HEIGHT];

    vector<vector<int8_t>> solution{9, vector<int8_t>(9)};
    vector<vector<int8_t>> generated_puzzle{9, vector<int8_t>(9)};
    vector<vector<int8_t>> generated_solution{9, vector<int8_t>(9)};
    vector<vector<int8_t>> create_mode_puzzle{9, vector<int8_t>(9)};
    vector<vector<int8_t>> create_mode_solution{9, vector<int8_t>(9)};



    bool create_mode = true;
    bool generate_mode = false;
    bool create_solution = false;
    bool finish_create = false;
    int count_create_mode = 0;
    bool exit = false;
    public:
        Sudoku();
        //~Sudoku();



        void start();

    protected:
        inline int8_t getBoard(int x, int y) {
            return m_Board[x][y];
        }
//        inline void setBoard(int x, int y, WINDOW* win) {
//            Board[x][y] = win;
//        }
        void initScreen();
        void createEmptyTable();
        void print_instruction();
        void moveCursor();
        bool checkCoursor(int x, int y);
        void move_up();
        void move_down();
        void move_left();
        void move_right();
        void generate_sudoku();
        void fill_puzzle(vector<int8_t> row);
        bool check_solution(vector<vector<int8_t>> sudoku);
        void empty_puzzle(int level, vector<int8_t> index, default_random_engine rng);
        void show_puzzle_on_board(int level);
        void show_solution_on_board(vector<vector<int8_t>> sudoku);
        bool check_created_sudoku();
        void generate_created_sudoku();
        void print_num(int num);
        void print_num_create_mode(int num);
        void add_num_create_mode_solution(int num);
        void add_num_create_mode_puzzle(int num);
        void merge_matrix(vector<vector<int8_t>> puzzle, vector<vector<int8_t>> solution);
};
