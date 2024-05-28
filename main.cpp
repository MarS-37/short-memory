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


void saveLengthToFile(int length_line) {
	std::ofstream settingsFile("settings.txt");

	if (settingsFile.is_open()) {
		settingsFile << length_line;
		settingsFile.close();
	}
}


std::string generateRandomString(int length, const std::string& charset) {
	std::string randomString;
	int charsetSize = charset.size();

	for (int i = 0; i < length; ++i) {
		char randomChar = charset[std::rand() % charsetSize];
		randomString += randomChar;
	}

	return randomString;
}


static void clearConsole()
{
	std::cout << "\033[2J\033[1;1H";
}


int main()
{
	// srand initialization
	std::srand(std::time(nullptr));
	// random string length
	int length_line; 
	std::string charset = "AdNbGtRe%369:?\";";

	loadLengthFromFile(length_line);

	while (true) {
		std::string line = generateRandomString(length_line, charset);
		std::cout << line << std::endl;
		

		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>((length_line * 1.5 + length_line) * 1000)));


		clearConsole();


		std::cout << "Enter the displayed string: ";


		std::string userInput;
		std::cin >> userInput;

		if (userInput == "exit") {
			std::cout << "Exiting the program..." << std::endl;
			break;
		}


		if (userInput == line) {
			++length_line;
		}
		else if(length_line > 1) {
			--length_line;
		}


		saveLengthToFile(length_line);
	}


	return 0;
}