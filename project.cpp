#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::remove_if;
using std::sort;

int main() {
    
    vector<string> words;
    string line = "";
    int off_count = 0;
    int non_sim = 0;
    
    // Reads in a user input password
    string password;
    cout << "Give me a password:" << endl;
    cin >> password;
    cout << "You provided a password of " << password << endl;
    
    int pass_size = password.length();
    int least = pass_size;
    
    // Uses a stream to open the .txt file
    ifstream myfile;
    myfile.open("common_passwords.txt");
    
    // If the file has been opened it reads in lines from the .txt
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            
            int line_size = line.size();
            
            // Initializes if the line or password is larger
            int smallest_size = std::min(line_size, pass_size);
            int largest_size = std::max(line_size, pass_size);
            
            // This for loop iterates through the characters to
            // check for differences in the two passwords
            for (int i = 0; i < smallest_size; ++i) {
                if (line[i] != password[i]) {
                    ++non_sim;
                }
            }
            
            // Adds the difference in password lengths
            non_sim += largest_size - smallest_size;
            
            // Checks the number of differences and then either
            // adds to the vector or clears the vector and starts
            // over.
            if (non_sim < least) {
                words = {};
                words.push_back(line);
                least = non_sim;
                off_count = non_sim;
            } else if (non_sim == least) {
                words.push_back(line);
                off_count = non_sim;
            }
            
            non_sim = 0;
            
        }
        
        // Closes the .txt file that was opened
        myfile.close();
        
    }
    
    cout << "The most similar passwords to " << password << " are:" << endl;
    
    sort(words.begin(), words.end());
    
    // Iterates through vector and outputs each element
    for (auto & element: words) {
        cout << element << ", ";
    }
    cout << endl << "All of which are " << off_count << " character(s) different." << endl;
    
}