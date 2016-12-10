#include "board.hpp"

using namespace std::chrono;
const int n = 4;
A<n> a;
std::random_device r;
template<int n> std::mt19937 A<n>::rand(r());

int main(){
	int b = 0, k = 0;
	std::vector<int> c;
	auto st = system_clock::now().time_since_epoch();
	c = a.init();
	while( c != std::vector<int> {n, n, 0} ){
		for(auto i:c)
			std::cout << i << ' ';
		std::cout << std::endl;
		std::cin >> b;
		c = a.move(b);
		k++;
	};
	auto et = system_clock::now().time_since_epoch();
	std::clog << k << ' ' << a.get_score() << ' ' << duration_cast<milliseconds>(et - st).count() << std::endl;
	return 0;
}
