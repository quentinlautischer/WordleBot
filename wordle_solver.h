#pragma once

namespace wordle_solver_ns 
{
	namespace
	{
		template<typename CollectionType>
		void print_list(const std::string& list_name, CollectionType collection)
		{
			std::cout << list_name << ": [";
			for (auto& item : collection)
				std::cout << item << ((&item != &collection.back()) ? ", " : "");
			std::cout << "]" << std::endl;
		}

		template<typename CollectionType, typename Pred>
		void copy_if(const CollectionType& source, CollectionType& target, Pred pred)
		{
			std::copy_if(source.begin(), source.end(), std::back_inserter(target), [&pred](auto& i) { return pred(i);});
		}
	}

	template<typename CollectionType>
    CollectionType filter_by_pattern(CollectionType& words, const std::string& pattern)
    {
        CollectionType words_matching_pattern;

		copy_if(words, words_matching_pattern,
		[&pattern](auto& word)
		{
			for(int i = 0; i < 5; ++i)
            {
                char c = pattern.at(i);

                if (c == '#')
                    continue;

                if (c != word.at(i))
					return false;
            }
			return true;
		});

        return words_matching_pattern;
    }

	template<typename CollectionType>
    CollectionType filter_by_confirmed(CollectionType& words, const std::string& confirmed)
    {
        CollectionType words_containing_confirmed;

		copy_if(words, words_containing_confirmed,
		[&confirmed](auto& word)
        {
            for(char c : confirmed)
                if (word.find(c) == std::string::npos)
					return false;
			return true;
        });
        
        return words_containing_confirmed;
    }

	template<typename CollectionType>
    CollectionType filter_by_rejected_letters(CollectionType& words, const std::string& pattern, std::string confirmed_letters, CollectionType& attempted)
    {
        CollectionType filtered;

		copy_if(pattern, confirmed_letters, [](const char c){ return c != '#'; });

        std::string rejected_letters;
        for(auto& word : attempted)
            copy_if(word, rejected_letters, [&confirmed_letters](const char c){ return confirmed_letters.find(c) == std::string::npos; });

		copy_if(words, filtered, 
		[&rejected_letters](auto& word)
		{
			return !std::any_of(rejected_letters.begin(), rejected_letters.end(), [&word](const char c){ return word.find(c) != std::string::npos; });
		});

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
				letter_probability[e.first] = ((float)e.second)/total_letters;

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
