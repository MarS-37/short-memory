#include <windows.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>


const int COLOR_BLUE	= 1;
const int COLOR_GREEN	= 2;
const int COLOR_YELLOW	= 6;
const int COLOR_RESET	= 7;


void setConsoleColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void loadSettingsFromFile(int& length_line, float& coffnt, std::string& charset)
{
	std::ifstream settingsFile("settings.cfg");

	if (settingsFile.is_open()) {
		std::string line;
		try {
			std::getline(settingsFile, line);
			length_line = std::stoi(line);
			std::getline(settingsFile, line);
			coffnt = std::stof(line);
			std::getline(settingsFile, charset);
		}
		catch (const std::invalid_argument& e) {
			std::cerr << &e << "Invalid format in settings file. Using default settings." << std::endl;
			length_line = 1;
			coffnt = 1.1f;
			charset = "1234567890-_=+\\|/`~qwertyuiop[]QWERTYUIOP{}asdfghjkl;\'ASDFGHJKL:\"zxcvbnmZXCVBNM<>?,.";
		}

		settingsFile.close();
	}
	else {
		length_line = 1;
		coffnt = 1.1f;
		charset = "1234567890-_=+\\|/`~qwertyuiop[]QWERTYUIOP{}asdfghjkl;\'ASDFGHJKL:\"zxcvbnmZXCVBNM<>?,.";
	}
}


void saveSettingsToFile(int length_line, float coffnt, const std::string& charset) {
	std::ofstream settingsFile("settings.cfg");

	if (settingsFile.is_open()) {
		settingsFile << length_line << std::endl;
		settingsFile << coffnt << std::endl;
		settingsFile << charset << std::endl;
		settingsFile.close();
	}
	else {
		std::cerr << "Unable to open settings file for writing." << std::endl;
	}
}


std::string generateRandomString(int length, const std::string& charset) {
	std::string randomString;
	size_t charsetSize = charset.size();

	for (int i = 0; i < length; ++i) {
		char randomChar = charset[std::rand() % charsetSize];
		randomString += randomChar;
	}

	return randomString;
}


int getRandomColor() {
	int colors[] = { COLOR_BLUE, COLOR_GREEN, COLOR_YELLOW };

	return colors[std::rand() % 3];
}


static void clearConsole()
{
	system("cls");
}


int main()
{
	setlocale(LC_ALL, "");


	std::srand(std::time(nullptr));


	int length_line;
	float coffnt;
	std::string charset;


	loadSettingsFromFile(length_line, coffnt, charset);


	while (true) 
	{
		clearConsole();
		
				
		std::cout << "��� ������ ������� \"exit\"" << std::endl;
		std::cout << "<" << length_line << "> " << "��������� ��������� ������: ";

		std::string line = generateRandomString(length_line, charset);

		for (char ch : line) {
			if ((ch > 64 && ch < 91) || (ch > 96 && ch < 123)) {
				setConsoleColor(COLOR_YELLOW);
			}

			std::cout <<  ch;
			setConsoleColor(COLOR_RESET);
		}
		
		
		std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>((length_line * 1.5 + length_line) * 1000)));

		clearConsole();

		std::cout << "��� ������ ������� \"exit\"" << std::endl;
		std::cout << "<" << length_line << "> " << "������� ���������� ������ ";


		std::string userInput;
		std::cin >> userInput;

		if (userInput == "exit") {
			std::cout << "Exiting the program..." << std::endl;
			break;
		}


		if (userInput == line) {
			++length_line;
		}
		else if (length_line > 1) {
			--length_line;
		}


		saveSettingsToFile(length_line, coffnt, charset);		
	}
	

	return 0;
}