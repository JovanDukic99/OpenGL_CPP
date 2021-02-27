#include <iostream>
#include <vector>

typedef unsigned char byte;

std::string createString(byte* buff, int size) {
	std::string result;

	for (int i = 0; i < size; i++) {
		result = result + (char) buff[i];
	}

	return result;
}

int size(byte* buff) {
	int t = 0;
	
	while (buff[t++] != 0) {
	
	}

	return t;
}

void test1() {
	byte* buff = new byte[1080];

	memset(buff, 0, 1080);

	std::cin.getline((char*)buff, 1080);

	std::string result = createString(buff, size(buff));

	std::cout << result << std::endl;
}

void test2() {
	int number = 20555;

	byte* buff = new byte[4];

	buff[0] = number;
	buff[1] = number >> 8;
	buff[2] = number >> 16;
	buff[3] = number >> 24;

	int result = buff[0] | (buff[1] << 8) | (buff[2] << 16) | (buff[3] << 24);

	std::cout << result << std::endl;
}

void test3()
{
	byte* bytes = new byte[1080];
	bytes[0] = 97;
	bytes[1] = 98;
	bytes[2] = 99;
	bytes = bytes + 2;
	std::cout << *bytes << std::endl;
}

void test4()
{
	throw 5;
}

void foo()
{
	test4();
}

//void test5() {
//	try {
//		Socket* socket = new Socket(100, "helloWOrld!");
//	}
//	catch (SocketException e) {
//		std::cout << e.message() << std::endl;
//	}
//}

void test6() {
	int mat[2][2] = {1, 2,
					3, 4};

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			std::cout << mat[i][j] << ", ";
		}
		std::cout << std::endl;
	}

	std::cout << *mat[1] << std::endl;
}

void test7() {
	std::vector<int> numbers;

	numbers.push_back(1);
	numbers.push_back(2);
	numbers.push_back(5);
	numbers.push_back(6);

	std::vector<int>::iterator it;


	for (it = numbers.begin(); it < numbers.end(); it++) {
		if (4 < *it) {
			numbers.insert(it, 4);
			break;
		}
	}

	for (size_t i = 0; i < numbers.size(); i++) {
		std::cout << numbers[i] << std::endl;
	}
}

int main() {
	
	test7();

	return 0;
}