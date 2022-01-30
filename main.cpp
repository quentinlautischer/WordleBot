#include <vector>
#include <memory>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "wordle_solver.h"
#include "tests/tests.h"

int main()
{
	std::cout << std::endl << "Wordle Solver" << std::endl << std::endl;

	#if _DEBUG
		tests::run_tests();
	#endif

	wordle_solver_ns::wordle_solver solver("wordle_words.txt");

	while(true)
	{
		std::cout << "Query>";
	
		std::string input;
		std::string args;
		
		std::cin >> input;

		if (input == "quit" || input == "q")
			return 0;
		else
		if (input == "h" || input == "help")
			std::cout << "Query format #OR##|WDS left is pattern and right is confirmed letters" << std::endl << std::endl;
		else
		if (input == "reset")
			solver.reset();
		else
		if (input == "guess")
		{
			auto best_word = solver.guess();
			std::cout << "Best next guess: " << best_word << std::endl;
			solver.add_attempt(best_word);
		}
		else
		if (input == "attempt")
		{
			std::cin >> args;
			std::transform(args.begin(), args.end(), args.begin(), [](char c){ return std::tolower(c); });
			
			solver.add_attempt(args);
		}		
		else
		if (input == "attempts")
			solver.print_attempts();
		else
		if (input == "pool")
		{
			solver.print_pool();
		}
		else
		if (input.find('|') != std::string::npos)
		{
			size_t idx = input.find('|');
			// Break apart and sanitize
			std::string green_pattern = input.substr(0, idx);
			std::string yellow_pattern = input.substr(idx+1, std::string::npos);
			std::transform(green_pattern.begin(), green_pattern.end(), green_pattern.begin(), [](char c){ return std::tolower(c); });
			std::transform(yellow_pattern.begin(), yellow_pattern.end(), yellow_pattern.begin(), [](char c){ return std::tolower(c); });

			if (green_pattern.size() == 0)
				green_pattern = "#####";
			else
			if (green_pattern.size() != 5)
			{
				std::cout << "Invalid green pattern" << std::endl;
				continue;
			}

			if (yellow_pattern.size() == 0)
				yellow_pattern = "#####";
			else
			if (yellow_pattern.size() != 5)
			{
				std::cout << "Invalid yellow pattern" << std::endl;
				continue;
			}


			// Crunch
			solver.solve(green_pattern, yellow_pattern);
			auto best_word = solver.guess();
			std::cout << "Best next guess: " << best_word << std::endl;
			solver.add_attempt(best_word);
		}
		else
			std::cout << "Invalid query" << std::endl;
	}

	return 0;
}
