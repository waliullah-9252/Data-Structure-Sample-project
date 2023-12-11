#include <iostream>
#include <string>
using namespace std;

// Node structure for a question
struct Question {
    string questionText;
    string optionA;
    string optionB;
    string optionC;
    string optionD;
    char correctOption;
    Question* next;

    Question(string qText, string optA, string optB, string optC, string optD, char correctOpt)
        : questionText(qText), optionA(optA), optionB(optB), optionC(optC), optionD(optD), correctOption(correctOpt), next(nullptr) {}
};

// Linked list to store questions
class QuestionList {
private:
    Question* head;

public:
    QuestionList() : head(nullptr) {}

    // Add a new question to the list
    void addQuestion(string qText, string optA, string optB, string optC, string optD, char correctOpt) {
        Question* newQuestion = new Question(qText, optA, optB, optC, optD, correctOpt);
        newQuestion->next = head;
        head = newQuestion;
    }

    // Display all questions in the list
    void displayQuestions() {
        Question* current = head;
        while (current != nullptr) {
            cout << "Q: " << current->questionText << endl;
            cout << "A. " << current->optionA << endl;
            cout << "B. " << current->optionB << endl;
            cout << "C. " << current->optionC << endl;
            cout << "D. " << current->optionD << endl;
            cout << "Correct Option: " << current->correctOption << endl << endl;

            current = current->next;
        }
    }

    // Function to take an exam
    void takeExam() {
        Question* current = head;
        int score = 0;

        while (current != nullptr) {
            cout << "Q: " << current->questionText << endl;
            cout << "A. " << current->optionA << endl;
            cout << "B. " << current->optionB << endl;
            cout << "C. " << current->optionC << endl;
            cout << "D. " << current->optionD << endl;

            char userAnswer;
            cout << "Your answer (A/B/C/D): ";
            cin >> userAnswer;

            if (toupper(userAnswer) == current->correctOption) {
                cout << "Correct!" << endl;
                score++;
            } else {
                cout << "Incorrect. Correct answer: " << current->correctOption << endl;
            }

            cout << endl;
            current = current->next;
        }

        cout << "Your final score: " << score << " out of " << getCount() << endl;
    }

    // Function to get the count of questions
    int getCount() {
        int count = 0;
        Question* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    // Other functionalities can be added, such as removing a question, updating a question, etc.
};

int main() {
    // Create a question list
    QuestionList examQuestions;

    while (true) {
        cout << "1. Add a question" << endl;
        cout << "2. Display questions" << endl;
        cout << "3. Take the exam" << endl;
        cout << "4. Exit" << endl;

        char choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == '1') {
            string qText, optA, optB, optC, optD;
            char correctOpt;

            cout << "Enter the question: ";
            cin.ignore();
            getline(cin, qText);

            cout << "Enter option A: ";
            getline(cin, optA);
            cout << "Enter option B: ";
            getline(cin, optB);
            cout << "Enter option C: ";
            getline(cin, optC);
            cout << "Enter option D: ";
            getline(cin, optD);

            cout << "Enter the correct option (A/B/C/D): ";
            cin >> correctOpt;

            examQuestions.addQuestion(qText, optA, optB, optC, optD, correctOpt);

            cout << "Question added successfully!" << endl;
        } else if (choice == '2') {
            cout << "----- Exam Questions -----" << endl;
            examQuestions.displayQuestions();
        } else if (choice == '3') {
            examQuestions.takeExam();
        } else if (choice == '4') {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

