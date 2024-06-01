#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm> // for std::find
#include <sstream>   // for std::stringstream

using namespace std;

void encrypt(const map<char, int>& charToNumber) {
    string enc;  // This will store the encrypted message
    string s;    // This will store the user input (plaintext)

    cout << "Enter the message which you want to encrypt: \n";
    
    cin >> ws;  // Use ws manipulator to ignore leading whitespace
    getline(cin, s);  // Use getline to handle multi-word input including spaces

    try {
        for (char c : s) {
            // Check if the character is an alphabetic letter
            if (isalpha(c)) {
                // Convert the character to lowercase to handle both uppercase and lowercase letters uniformly
                c = tolower(c);

                if (charToNumber.find(c) == charToNumber.end()) {
                    throw invalid_argument("Character not found in alphabet map.");
                }

                // Append the corresponding number to the encrypted message
                enc += to_string(charToNumber.at(c)) + " ";
            } else {
                throw invalid_argument("Input contains non-alphabetic character.");
            }
        }

        // Output the encrypted message
        cout << "Encrypted message: " << enc << endl;

    } catch (const invalid_argument& e) {
        cout << "Error during encryption: " << e.what() << endl;
    }
}

void decrypt(const map<int, char>& numberToChar) {
    string dec;  // This will store the decrypted message
    string s;    // This will store the user input (ciphertext)
    int num;     // Declare num to store the converted integer value

    cout << "Enter the numbers for decryption (input one number at a time, separated by spaces, type 'end' to finish): \n";
    
    while (true) {
        try {
            cin >> s;  // Read the input from the user into the string `s`
            
            if (s == "end") break;  // If the input is "end", break out of the loop

            num = stoi(s);  // Convert the input string to an integer and store it in `num`

            if (numberToChar.find(num) == numberToChar.end()) {
                // If the number is not found in the map, throw an invalid_argument exception
                throw invalid_argument("Invalid number entered.");
            }

            // Append the character corresponding to the number to the decrypted message
            dec += numberToChar.at(num);
        } catch (const invalid_argument& e) {
            // If an invalid_argument exception is caught, print an error message
            cout << "Invalid input. Please enter valid numbers only.\n";

            // Clear the input stream error state
            cin.clear();

            // Ignore the rest of the line to remove any invalid input from the stream
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Output the decrypted message
    cout << "Decrypted message: " << dec << endl;
}

int getChoice() {
    int choice;
    try {
        cout << "1. Encrypt a message\n";
        cout << "2. Decrypt a message\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 3) {
            throw invalid_argument("Invalid choice entered.");
        }
    } catch (const invalid_argument& e) {
        // If an invalid_argument exception is caught, print an error message
        cout << "Error: " << e.what() << ". Please try again.\n";
        cin.clear();  // Clear the input stream error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the rest of the line
        choice = getChoice();  // Recursively call getChoice() until valid input is provided
    }
    return choice;
}

int main() {
    // Using vector to store alphabet
    string alpha = "abcdefghijklmnopqrstuvwxyz";

    // Create a map for encryption
    map<char, int> charToNumber;
    for (int i = 0; i < alpha.size(); ++i) {
        charToNumber[alpha[i]] = i + 1;  // Map character to 1-based index
    }

    // Create a map for decryption
    map<int, char> numberToChar;
    for (int i = 0; i < alpha.size(); ++i) {
        numberToChar[i + 1] = alpha[i];  // Map 1-based index to character
    }

    int userChoice;
    do {
        userChoice = getChoice();  // Get user choice once per loop iteration

        switch (userChoice) {
            case 1:
                encrypt(charToNumber);
                break;

            case 2:
                decrypt(numberToChar);
                break;

            case 3:
                cout << "Program ran successful. End of program." << endl;
                break;

            default:
                cout << "Bad choice! Please try again later.\n";
        }
    } while (userChoice != 3);  // Use the stored userChoice variable

    return 0;
}
