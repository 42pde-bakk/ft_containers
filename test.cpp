#include <vector>
#include <iostream>

int main() {
	std::vector<int> peer;
	for (int i = 0; i < 10; i++)
		peer.push_back(i);
	std::vector<int>::iterator it = peer.begin();
	for (int i = 0; i < 4; i++)
		it++;
	std::cout << it[4] << std::endl;
	std::cout << it[-89] << std::endl;
	std::cout << "cap = " << peer.capacity() << ", other = " << peer.size() << std::endl;
}
