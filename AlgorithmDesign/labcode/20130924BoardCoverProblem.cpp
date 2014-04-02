#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <cstdlib>

template <typename T> 
struct matrix
{
	matrix(const std::size_t row, const std::size_t col) :
		row_(row),
		col_(col),
		data_(new T[row * col])
	{}

	~matrix() { delete[] this->data_; }

	T & operator()(const std::size_t row, const std::size_t col)
	{ return this->data_[ row * this->col_ + col ]; }

	const T & operator()(const std::size_t row, const std::size_t col) const 
	{ return this->data_[ row * this->col_ + col ]; }

	std::size_t row_;
	std::size_t col_;
	T * data_;
};//struct matrix

std::size_t g_num;
std::size_t g_srow;
std::size_t g_scol;
matrix<int> * g_board;

std::size_t g_tile_num1 = 1;
std::size_t g_tile_num2 = 2;
std::size_t g_tile_num3 = 3;
std::size_t g_tile_num4 = 4;

void input() {
	std::cin >> g_num;
	if(std::sqrt(g_num) - std::floor(std::sqrt(g_num)) > 0) {
		std::cout << "num must be a squared number." << std::endl;
		std::exit(1);
	}//if
	std::cin >> g_srow;
	std::cin >> g_scol;

	g_board = new matrix<int>(g_num, g_num);
}//input()

void output() {
	for(std::size_t i = 0; i < g_num; ++i) {
		for(std::size_t j = 0; j < g_num; ++j) {
			std::cout << std::setw(4) << (*g_board)(i, j);
		}//for
		std::cout << std::endl;
	}//for
}//output()

void chess_board(int row, int col, int srow, int scol, int size) {
	if(size == 1)
		return;

	int s = size/2;
	std::size_t tile;

	// decide which tile to use:
	if(srow < row + s && scol < col + s) {
		tile = g_tile_num4;
		g_tile_num4 += 4;
	} else if(srow < row + s && scol >= col + s) {
		tile = g_tile_num3;
		g_tile_num3 += 4;
	} else if(srow >= row + s && scol < col + s) {
		tile = g_tile_num2;
		g_tile_num2 += 4;
	} else if(srow >= row + s && scol >= col + s) {
		tile = g_tile_num1;
		g_tile_num1 += 4;
	}//if-else

	// left upper
	if(srow < row + s && scol < col + s) {
		chess_board(row, col, srow, scol, s);
	} else {
		(*g_board)(row + s - 1, col + s - 1) = tile;
		chess_board(row, col, row + s - 1, col + s - 1, s);
	}//if-else

	// right upper
	if(srow < row + s && scol >= col + s) {
		chess_board(row, col + s, srow, scol, s);
	} else {
		(*g_board)(row + s - 1, col + s) = tile;
		chess_board(row, col + s, row + s - 1, col + s, s);
	}//if-else

	// left lower
	if(srow >= row + s && scol < col + s) {
		chess_board(row + s, col, srow, scol, s);
	} else {
		(*g_board)(row + s, col + s - 1) = tile;
		chess_board(row + s, col, row + s, col + s - 1, s);
	}//if-else

	// right lower
	if(srow >= row + s && scol >= col + s) {
		chess_board(row + s, col + s, srow, scol, s);
	} else {
		(*g_board)(row + s, col + s) = tile;
		chess_board(row + s, col + s, row + s, col + s, s);
	}//if-else
}//chess_board(row, col, srow, scol, size)

int main(int argc, char * argv[]) {
	input();

	chess_board(0, 0, g_srow, g_scol, g_num);

	output();

	return 0;
}//main

