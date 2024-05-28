#include <iostream>
#include <fstream>
#include <chrono>
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


int main()
{
	// srand initialization
	std::srand(std::time(nullptr));
	// random string length
	int length_line; 

	loadLengthFromFile(length_line);

	while (false) {

	}


	return 0;
}