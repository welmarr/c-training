#include <array>
#include <iostream>
#include <vector>
#include <map> 
#include <utility>
#include <algorithm>
#include <boost/algorithm/string.hpp>

class PhoneBook {
    private:
    std::map<std::string, std::string> memory;
    std::map<int, std::vector<std::string>> memory_alpha_index;

public:
    PhoneBook(const std::vector<std::string>& numbers) {
        for(long unsigned int i = 0; i < (numbers.size()- 1); i+=2){
            AddEntry(boost::to_lower_copy(numbers.at(i)), numbers.at(i + 1));
        }
    }

    bool AddEntry(const std::string& name, const std::string& num) {
        try{
            std::string key = boost::to_lower_copy(name);
            
            memory[key] = num;

            int key_first_caracter = int(key[0]);

            auto it = memory_alpha_index.find(key_first_caracter);

            if(it != memory_alpha_index.end()){
                // std::cout << " -- " << char(key_first_caracter) << "  -  " << key << "\n";
                std::vector<std::string> current_caracter_dic= it->second;

                if(find(current_caracter_dic.begin(), current_caracter_dic.end(), key) == current_caracter_dic.end()){
                    current_caracter_dic.push_back(key);
                }

                std::sort(current_caracter_dic.begin(), current_caracter_dic.end());
                memory_alpha_index[key_first_caracter] = current_caracter_dic;
            }else{

                // std::cout << " ++ " << char(key_first_caracter) << "  -  " << key << "\n";
                memory_alpha_index[key_first_caracter] = std::vector<std::string> { key };
            }
            
            return true;
        }catch(const std::runtime_error& re)
        {
            std::cerr << "Runtime error: " << re.what() << std::endl;
            return false;
        }
        catch(const std::exception& ex)
        {
            std::cerr << "Error occurred: " << ex.what() << std::endl;
            return false;
        }

    }

    std::string GetNumber(const std::string& name) {
        auto it = memory.find(boost::to_lower_copy(name));
        if(it != memory.end()){
            return it->second;
        }
        return "";
    }

    int Count(){
        return memory.size();
    }

    void Display(){
        for(auto character : memory_alpha_index){
            std::cout << char(character.first) << '\n';
            for(auto line : character.second){
                std::cout << line << " : " << memory.find(line)->second << '\n';
            }
        }
    }

    // some other ideas for the API?
    // optionally: check name in a case insensitive way -> "John" and "joHN" should point to the same entry.
};

int main() {
    const std::vector<std::string> numbers {
        "John", "123 456 789",
        "Kate", "777 456 789",
        "Blake", "456 111 789",
        "Megan", "321 986 545",
        "Mark", "783 432 222",
        "Bob", "875 462 111",
        "Hugo", "873 753 751"
    };

    //std::cout << "count of numbers: " << numbers.size()/2 << '\n';

    PhoneBook book { numbers }; // the book initializes with the array entries
    book.AddEntry("John", "123 123 123");
    book.AddEntry("Barbara", "789 331 781");
    book.AddEntry("Aymar", "7969 331 781");
    book.AddEntry("Zimmar", "896 331 856");
    // basic API
    std::cout << "looking for John: " << book.GetNumber("John") << '\n';
    std::cout << "Number of line in book: " << book.Count() << '\n';

    book.Display();
}