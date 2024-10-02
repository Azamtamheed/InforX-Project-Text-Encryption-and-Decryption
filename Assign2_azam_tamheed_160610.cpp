#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

struct Node {
    char data;
    Node* next;
    Node(char data) {
        this->data = data; 
        this->next = NULL; 
    }
};

class Stack {
private:
    Node* top;

public:
    Stack() {
        top = NULL;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(char element) {
        Node* newNode = new Node(element);
        newNode->next = top;
        top = newNode;
    }

    char pop() {
        if (!isEmpty()) {
            Node* temp = top;
            char data = top->data;
            top = top->next;
            delete temp;
            return data;
        }
        return 0; // Stack is empty
    }

    bool isEmpty() {
        return top == NULL;
    }
};

class Queue {
private:
    Node *front, *back;

public:
    Queue() {
        front = NULL;
        back = NULL;
    }

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(char element) {
        Node* newNode = new Node(element);
        if (isEmpty()) {
            front = back = newNode;
        } else {
            back->next = newNode;
            back = newNode;
        }
    }

    char dequeue() {
        if (!isEmpty()) {
            Node* temp = front;
            char data = front->data;
            front = front->next;
            if (front == NULL) {
                back = NULL;
            }
            delete temp;
            return data;
        }
        return 0; // Queue is empty
    }

    bool isEmpty() {
        return front == NULL;
    }
};

class EncryptorDecryptor {
public:
    string encryptText(const string& text) {
        Stack stack;
        string encryptedText, finalText;
        for (int i = 0; i < text.length(); ++i) {
            char ch = text[i];
            if (ch == ' ' || ch == '\n') {
                while (!stack.isEmpty()) {
                    encryptedText += replaceVowel(stack.pop());
                }
                finalText = encryptedText + " " + finalText;
                encryptedText.clear();
            } else {
                stack.push(ch);
            }
        }
        while (!stack.isEmpty()) {
            encryptedText += replaceVowel(stack.pop());
        }
        finalText = encryptedText + " " + finalText;
        if (!finalText.empty() && finalText[finalText.length() - 1] == ' ') {
            finalText.erase(finalText.length() - 1);  // Remove the extra space at the end
        }
        return finalText;
    }

    string decryptText(const string& text) {
        Stack stack;
        string decryptedText, finalWord;
        for (int i = text.length() - 1; i >= -1; --i) {
            char ch = (i >= 0) ? text[i] : ' '; // Add a space at the beginning to trigger the final word processing
            if (ch == ' ' || ch == '\n') {
                while (!stack.isEmpty()) {
                    finalWord += revertVowel(stack.pop());
                }
                finalWord = reverseString(finalWord); // Use custom reverse function
                if (!decryptedText.empty() && !finalWord.empty()) {
                    decryptedText += " ";
                }
                decryptedText += finalWord;
                finalWord.clear();
            } else {
                stack.push(ch);
            }
        }
        return decryptedText;
    }

private:
    static char replaceVowel(char ch) {
        switch (ch) {
            case 'a': case 'A': return '*';
            case 'e': case 'E': return '@';
            case 'i': case 'I': return '#';
            case 'o': case 'O': return '$';
            case 'u': case 'U': return '&';
            default: return ch;
        }
    }

    static char revertVowel(char ch) {
        switch (ch) {
            case '*': return 'a'; // or 'A' depending on your decryption policy
            case '@': return 'e'; // or 'E'
            case '#': return 'i'; // or 'I'
            case '$': return 'o'; // or 'O'
            case '&': return 'u'; // or 'U'
            default: return ch;
        }
    }

    static string reverseString(const string& str) {
        string reversed;
        for (int i = str.length() - 1; i >= 0; i--) {
            reversed += str[i];
        }
        return reversed;
    }
};

void encryptFromFile() {
    string inputFile;
    cout << "Enter the name of the input file for encryption: ";
    cin >> inputFile;

    ifstream inFile(inputFile);
    assert(inFile.is_open());

    EncryptorDecryptor encryptorDecryptor;
    string line, encryptedText;
    while (getline(inFile, line)) {
        encryptedText += encryptorDecryptor.encryptText(line) + "\n";
    }

    inFile.close();
    cout << "Encrypted Text:\n" << encryptedText << endl;
}

void decryptFromFile() {
    string inputFile;
    cout << "Enter the name of the input file for decryption: ";
    cin >> inputFile;

    ifstream inFile(inputFile);
    assert(inFile.is_open());

    EncryptorDecryptor encryptorDecryptor;
    string line, decryptedText;
    while (getline(inFile, line)) {
        decryptedText += encryptorDecryptor.decryptText(line) + "\n";
    }

    inFile.close();
    cout << "Decrypted Text:\n" << decryptedText << endl;
}

int main() {
    while (true) {
        cout << " ............................Main Menu........................" << endl;
        cout << "1. Encrypt Text from File" << endl;
        cout << "2. Decrypt Text from File" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice (1-3): ";
        
        char choice;
        cin >> choice;

        switch (choice) {
            case '1':
                encryptFromFile();
                break;
            case '2':
                decryptFromFile();
                break;
            case '3':
                cout << "\nThank You for using our Application. \nExiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

