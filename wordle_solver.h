#pragma once

namespace wordle_solver_ns 
{
	template<typename T>
	void print_list(const std::string& name, std::vector<T> collection)
	{
		std::cout << name << ": [";
		auto it = collection.begin();
		while(it != collection.end())
		{
			std::cout <<  *it;
			if (it+1 != collection.end()) 
				std::cout << ", ";
			it++;
		}
		std::cout << "]" << std::endl;
	}

    std::vector<std::string> filter_by_pattern(std::vector<std::string>& words, const std::string& pattern)
    {
        std::vector<std::string> words_matching_pattern;

        for(auto& word : words)
        {
            bool is_valid = true;
            for(int i = 0; i < 5; ++i)
            {
                char c = pattern.at(i);

                if (c == '#')
                    continue;

                if (c != word.at(i))
                {
                    is_valid = false;
                    break;
                }
            }

            if (is_valid)
                words_matching_pattern.emplace_back(word);
        }

        return words_matching_pattern;
    }

    std::vector<std::string> filter_by_confirmed(std::vector<std::string>& words, const std::string& confirmed)
    {
        std::vector<std::string> words_containing_confirmed;

        for (auto& word : words)
        {
            bool is_valid = true;
            for(char c : confirmed)
            {
                if (word.find(c) == std::string::npos)
                {
                    is_valid = false;
                    break;
                }
            }
            if (is_valid)
                words_containing_confirmed.emplace_back(word);
        }
        
        return words_containing_confirmed;
    }

    std::vector<std::string> filter_by_rejected_letters(std::vector<std::string>& words, const std::string& pattern, const std::string& confirmed_letters, std::vector<std::string>& attempted)
    {
        std::vector<std::string> filtered;

        std::string confirmed = confirmed_letters;
        for (char c : pattern)
        {
            if (c != '#')
                confirmed.push_back(c);
        }
        std::string rejected;
        for(auto& word : attempted)
        {
            for (char c : word)
            {
                if (confirmed.find(c) == std::string::npos)
                {
                    rejected.push_back(c);
                }
            }
        }

        for (auto& word : words)
        {
            bool is_valid = true;
            for (char c : rejected)
            {
                if (word.find(c) != std::string::npos)
                {
                    is_valid = false;
                    break;
                }		
            }

            if (is_valid)
                filtered.push_back(word);
        }

        return filtered;
    }

	class wordle_solver
	{
	public:
		wordle_solver(const std::string& filepath)
		:words_(load_words(filepath)), filepath_(filepath)
		{
		}

		wordle_solver(std::vector<std::string>&& words)
		:words_(words)
		{
		}

		void reset()
		{
			words_ = load_words(filepath_);
			attempts_.clear();
			confirmed_ = "";
		}

		void add_attempt(const std::string word)
		{
			attempts_.push_back(word);
		}

		void print_attempts()
		{
			print_list("Attempts", attempts_);
		}

		void print_pool()
		{
			print_list("Remaining words", words_);
		}

		std::vector<std::string> pool()
		{
			return words_;
		}

		std::string guess()
		{
			if (words_.empty())
				return "No words. No stats. No guess.";

			size_t total_letters = 0;
			std::map<char, size_t> letter_occurences;
			for(auto& word : words_)
			{
				for (char c : word)
				{
					total_letters++;

					if (letter_occurences.find(c) != letter_occurences.end())
						letter_occurences[c]++;
					else
						letter_occurences[c] = 1;
				}
			}

			std::map<char, float> letter_probability;
			for (auto e : letter_occurences)
			{
				letter_probability[e.first] = ((float)e.second)/total_letters;
			}

			//Score
			std::string best_word = words_[0];
			float best_score = 0.0f;

			for (auto& word : words_)
			{
				float score = 0.0f;
				std::string letters_used;
				for (char c : word)
				{
					if (letters_used.find(c) == std::string::npos)
						score += letter_probability[c];

					letters_used.push_back(c);
				}
				
				if (score > best_score)
				{
					if (std::find(attempts_.begin(), attempts_.end(), word) != attempts_.end())
						continue;

					best_score = score;
					best_word = word;
				}
			}

			return best_word;
		}

		void solve(const std::string& pattern, const std::string& confirmed_letters)
		{
			auto a = filter_by_pattern(words_, pattern);
			auto b = filter_by_confirmed(a, confirmed_letters);
			words_ = filter_by_rejected_letters(b, pattern, confirmed_letters, attempts_);	
		}

	private:

		std::vector<std::string> load_words(const std::string& filepath)
		{
			std::vector<std::string> words;

			std::fstream fs(filepath, std::fstream::in);
			std::string word;
			while(std::getline(fs, word))
				words.push_back(word);

			return words;
		}

	private:
		std::string filepath_;

		std::vector<std::string> words_;
		std::vector<std::string> attempts_;
		std::string 			 confirmed_;
	};
}
