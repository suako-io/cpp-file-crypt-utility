#include <iostream>
#include <string>

std::int8_t startup()
{
	std::string _user_input{};
	std::int8_t _converted_input{};

	std::cout << "1: Encrypt a file" << std::endl;
	std::cout << "2: Decrypt a file" << std::endl;
	std::cout << "Please select option: ";

	std::getline(std::cin, _user_input);

	if (_user_input == "1")
	{
		std::cout << "You entered: " + _user_input << std::endl;
		_converted_input = std::stoi(_user_input);
		return _converted_input;
	}
	else if (_user_input == "2")
	{
		std::cout << "You entered: " + _user_input << std::endl;
		_converted_input = std::stoi(_user_input);
		return _converted_input;
	}
	else
	{
		std::cout << "Invalid input, please enter correct input." << std::endl;
		startup();
	}
}

int main()
{
	std::int8_t _selected_option{ startup() };


	return 0;
}