#include <array>
#include <random>
#include <vector>
#include <chrono>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>

template<int n> class A{
private:
	int left_adder(int&, int);
	int left_compressor(int&, int);
	int left_move_row(int);
	int left_move();
	int right_adder(int&, int);
	int right_compressor(int&, int);
	int right_move_row(int);
	int right_move();
	int up_adder(int&, int);
	int up_compressor(int&, int);
	int up_move_column(int);
	int up_move();
	int down_adder(int&, int);
	int down_compressor(int&, int);
	int down_move_column(int);
	int down_move();
	std::pair<int,int> random();
	void out() const;
	unsigned score = 0;
	bool deadlock = false;
	static std::mt19937 rand;
	std::array<std::array<int,n>,n> a;
public:
	A();
	std::vector<int> init();
	std::vector<int> move(int);
	unsigned get_score() const;
};


template<int n> int A<n>::left_adder(int& k, int l){
	int s = 0;
	for(;a[l][k] == a[l][k-1] && k && a[l][k]; k--){
		a[l][k-1]++;
		s += (1 << (a[l][k] + 1));
		a[l][k] = 0;
		deadlock = false;
	};
	return s;
};

template<int n> int A<n>::left_compressor(int& k, int l){
	int j = k;
	while(!a[l][j] && j < n)
		j++;
	if(j==n)
		k = n;
	else
		deadlock = false;
	std::swap(a[l][k], a[l][j]);
	return left_adder(k, l);
};

template<int n> int A<n>::left_move_row(int l){
	int s = 0;
	for(int i = 0; i < n; i++)
		if(a[l][i])
			s += left_adder(i, l);
		else
			s += left_compressor(i, l);
	return s;
};

template<int n> int A<n>::left_move(){
	int s = 0;
	for(int i = 0; i < n; i++)
		s += left_move_row(i);
	return s;
};

template<int n> int A<n>::up_adder(int& k, int l){
	int s = 0;
	for(;a[k][l] == a[k-1][l] && k && a[k][l]; k--){
		a[k-1][l]++;
		s += (1 << (a[k][l] + 1));
		a[k][l] = 0;
		deadlock = false;
	};
	return s;
};

template<int n> int A<n>::up_compressor(int& k, int l){
	int j = k;
	while(!a[j][l] && j < n)
		j++;
	if(j==n)
		k = n;
	else
		deadlock = false;
	std::swap(a[k][l], a[j][l]);
	return up_adder(k, l);
};

template<int n> int A<n>::up_move_column(int l){
	int s = 0;
	for(int i = 0; i < n; i++)
			if(a[i][l])
				s += up_adder(i, l);
			else
				s += up_compressor(i, l);
	return s;
};

template<int n> int A<n>::up_move(){
	int s = 0;
	for(int i = 0; i < n; i++)
		s += up_move_column(i);
	return s;
};

template<int n> int A<n>::right_adder(int& k, int l){
	int s = 0;
	for(;a[l][k] == a[l][k+1] && k < n - 1 && a[l][k]; k++){
		a[l][k+1]++;
		s += (1 << (a[l][k] + 1));
		a[l][k] = 0;
		deadlock = false;
	};
	return s;
};

template<int n> int A<n>::right_compressor(int& k, int l){
	int j = k;
	while(!a[l][j] && j)
		j--;
	if(j < 0)
		k = 0;
	else
		deadlock = false;
	std::swap(a[l][k], a[l][j]);
	return right_adder(k, l);
};

template<int n> int A<n>::right_move_row(int l){
	int s = 0;
	for(int i = n - 1; i >= 0 ; i--)
		if(a[l][i])
			s += right_adder(i, l);
		else
			s += right_compressor(i, l);
	return s;
};

template<int n> int A<n>::right_move(){
	int s = 0;
	for(int i = 0; i < n; i++)
		s += right_move_row(i);
	return s;
};

template<int n> int A<n>::down_adder(int& k, int l){
	int s = 0;
	for(;a[k][l] == a[k+1][l] && k < n - 1 && a[k][l]; k++){
		a[k+1][l]++;
		s += (1 << (a[k][l] + 1));
		a[k][l] = 0;
		deadlock = false;
	};
	return s;
};

template<int n> int A<n>::down_compressor(int& k, int l){
	int j = k;
	while(!a[j][l] && j)
		j--;
	if(j < 0)
		k = 0;
	else
		deadlock = false;
	std::swap(a[k][l], a[j][l]);
	return down_adder(k, l);
};

template<int n> int A<n>::down_move_column(int l){
	int s = 0;
	for(int i = n - 1; i >= 0 ; i--)
		if(a[i][l])
			s += down_adder(i, l);
		else
			s += down_compressor(i, l);
	return s;
};

template<int n> int A<n>::down_move(){
	int s = 0;
	for(int i = 0; i < n; i++)
		s += down_move_column(i);
	return s;
};

template<int n> void A<n>::out() const{
	for(auto i:a){
		for(auto j:i)
			std::clog<<int(j)<<' ';
		std::clog<<std::endl;
	};
	std::clog<<std::endl;
};

template<int n> A<n>::A(){
	for(auto& i:a)
		for(auto& j:i)
			j = 0;
};

template<int n> std::vector<int> A<n>::move(int side){
	deadlock = true;
	int t = A<n>::rand() % 10;
	std::pair<int,int> r;
	switch(side){
		case 0:
			out();
			t = score;
			deadlock = false;
			r = std::make_pair(0, 0);
			break;
		case 1:
			score += up_move();
			break;
		case 2:
			score += right_move();
			break;
		case 3:
			score += down_move();
			break;
		case 4:
			score += left_move();
			break;
	};
	if(deadlock)
		return std::vector<int>{n, n, 0};
	if(side){
		r = random();
		t = (t)?(1):(2);
		a[r.first][r.second] = t;
	};
	return std::vector<int>{r.first, r.second, t};
};

template<int n> std::vector<int> A<n>::init(){
	std::pair<int, int> r1 = random();
	a[r1.first][r1.second] = 1;
	std::pair<int, int> r2 = random();
	a[r2.first][r2.second] = 1;
	return std::vector<int> {r1.first, r1.second, r2.first, r2.second};
};

template<int n> unsigned A<n>::get_score() const{
	return score;
};

template<int n> std::pair<int,int> A<n>::random(){
	std::vector<std::pair<int,int>> v;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			if(!a[i][j])
				v.push_back(std::make_pair(i, j));
	return v[A<n>::rand() % v.size()];
};
