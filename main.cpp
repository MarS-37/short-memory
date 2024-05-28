#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>


void loadLengthFromFile(int& length_line)
{
	std::ifstream settingsFile("settings.txt");

	if (settingsFile.is_open()) {
		settingsFile >> length_line;
		settingsFile.close();
	}
	else {
		// default value if the file doesn't exist
		length_line = 1;
	}
}


std::string generateRandomString(int length) {
	std::string randomString;

	for (int i = 0; i < length; ++i) {
		char randomChar = 'a' + std::rand() % 26;
		randomString += randomChar;
	}

	return randomString;
}


int main()
{
	// srand initialization
	std::srand(std::time(nullptr));
	// random string length
	int length_line; 

	loadLengthFromFile(length_line);

	while (false) {
		std::string line = generateRandomString(length_line);
		std::cout << line << std::endl;


		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>((length_line * 1.5 + length_line) * 1000)));


		
	}


	return 0;
}