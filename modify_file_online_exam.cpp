#include <iostream>
#include <fstream>
using namespace std;

class Question
{
public:
    string questionText;
    string optionA;
    string optionB;
    string optionC;
    string optionD;
    char correctOption;
    Question *next;


    // constructor 
    Question(string questionText, string optionA, string optionB, string optionC, string optionD, char correctOption)
    {
        this->questionText = questionText;
        this->optionA = optionA;
        this->optionB = optionB;
        this->optionC = optionC;
        this->optionD = optionD;
        this->correctOption = correctOption;
        this->next = NULL;
    }
};

// add or create questions functions
void addQuestion(Question *&head, string qText, string optA, string optB, string optC, string optD, char correctOpt)
{
    Question *newQuestion = new Question(qText, optA, optB, optC, optD, correctOpt);
    newQuestion->next = head;
    head = newQuestion;
}

// show the question function 
void displayQuestions(Question *head)
{
    if (head == NULL)
    {
        cout << endl
             << "Question list is empty." << endl;
        return;
    }
    Question *current = head;
    while (current != NULL)
    {
        cout << "Q: " << current->questionText << endl;
        cout << "A. " << current->optionA << endl;
        cout << "B. " << current->optionB << endl;
        cout << "C. " << current->optionC << endl;
        cout << "D. " << current->optionD << endl;
        cout << "Correct Option: " << current->correctOption << endl
             << endl;

        current = current->next;
    }
}

// count the the questions 
int getCount(Question *head)
{
    int count = 0;
    Question *current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}


// paticipate exam create questions 
void takeExam(Question *&head)
{
    if (head == NULL)
    {
        cout << endl
             << "The question list is empty. Cannot take the exam." << endl
             << endl;
        return;
    }

    int totalMark = getCount(head);

    int position;
    cout << "Enter the position of the question you want to answer (starting from 0): ";
    cin >> position;

    Question *current = head;
    int currentPos = 0;
    while (current != NULL && currentPos < position)
    {
        current = current->next;
        currentPos++;
    }

    if (current == NULL)
    {
        cout << endl
             << "Invalid position. No question found at the specified position." << endl
             << endl;
        return;
    }

    cout << "Q: " << current->questionText << endl;
    cout << "A. " << current->optionA << endl;
    cout << "B. " << current->optionB << endl;
    cout << "C. " << current->optionC << endl;
    cout << "D. " << current->optionD << endl;

    char userAnswer;
    cout << "Your answer (A/B/C/D): ";
    cin >> userAnswer;

    int score = 0;

    if (userAnswer == current->correctOption)
    {
        cout << "Correct!" << endl;
        score = 1; // Mark for a correct answer
    }
    else
    {
        cout << "Incorrect. Correct answer is: " << current->correctOption << endl;
    }

    cout << endl;
    cout << "Your score is: " << score << " out of 1. Total Mark: " << totalMark << endl
         << endl;
}


// delete the created questions 
void deleteQuestion(Question *&head, int pos)
{
    if (head == NULL)
    {
        cout << endl
             << "The question list is empty." << endl
             << endl;
        return;
    }

    if (pos == 0)
    {
        Question *deleteQuestion = head;
        head = head->next;
        delete deleteQuestion;
        cout << endl
             << "Deleted from position " << pos << endl
             << endl;
        return;
    }

    Question *temp = head;
    for (int i = 0; i < pos - 1; i++)
    {
        temp = temp->next;
        if (temp == NULL || temp->next == NULL)
        {
            cout << endl
                 << "Invalid index." << endl
                 << endl;
            return;
        }
    }

    Question *deleteQuestion = temp->next;
    temp->next = temp->next->next;
    delete deleteQuestion;
    cout << endl
         << "Deleted from position " << pos << endl
         << endl;
}


// calculate the mark this question
int calculateTotalMark(Question *head)
{
    int totalMark = 0;
    Question *current = head;
    while (current != NULL)
    {
        totalMark++;
        current = current->next;
    }
    return totalMark;
}


// file save functions 
void saveQuestionsToFile(Question *head, const string &filename)
{
    ofstream outFile(filename);
    if (outFile.is_open())
    {
        Question *current = head;
        while (current != NULL)
        {
            outFile << current->questionText << "\n";
            outFile << current->optionA << "\n";
            outFile << current->optionB << "\n";
            outFile << current->optionC << "\n";
            outFile << current->optionD << "\n";
            outFile << current->correctOption << "\n";

            current = current->next;
        }
        outFile.close();
        cout << "Questions saved to file: " << filename << endl;
    }
    else
    {
        cout << "Error opening file for writing." << endl;
    }
}


// load the file which created the functions 
void loadQuestionsFromFile(Question *&head, const string &filename)
{
    ifstream inFile(filename);
    if (inFile.is_open())
    {
        string qText, optA, optB, optC, optD;
        char correctOpt;

        while (getline(inFile, qText) &&
               getline(inFile, optA) &&
               getline(inFile, optB) &&
               getline(inFile, optC) &&
               getline(inFile, optD) &&
               inFile >> correctOpt)
        {
            addQuestion(head, qText, optA, optB, optC, optD, correctOpt);
            inFile.ignore(); // Consume the newline character after correctOpt
        }

        inFile.close();
        cout << "Questions loaded from file: " << filename << endl;
    }
    else
    {
        cout << "Error opening file for reading." << endl;
    }
}


// main function start here 
int main()
{
    Question *head = NULL;

    while (true)
    {
        cout << "<----Menu---->" << endl;
        cout << "1. Add a question" << endl;
        cout << "2. Display questions" << endl;
        cout << "3. Take the exam" << endl;
        cout << "4. Delete Question" << endl;
        cout << "5. Calculate Total Mark" << endl;
        cout << "6. Save Questions to File" << endl;
        cout << "7. Load Questions from File" << endl;
        cout << "8. Exit" << endl;

        char choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == '1')
        {
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

            addQuestion(head, qText, optA, optB, optC, optD, correctOpt);

            cout << endl
                 << "Question added successfully!" << endl
                 << endl;
        }
        else if (choice == '2')
        {
            cout << endl
                 << "----- Exam All Questions -----" << endl;
            displayQuestions(head);
            cout << endl
                 << "----------------------------------------" << endl;
        }
        else if (choice == '3')
        {
            cout << endl
                 << "----- Now Answer Your Exam Questions -----" << endl;
            takeExam(head);
        }
        else if (choice == '4')
        {
            int pos;
            cout << "Enter the position of the question you want to delete: ";
            cin >> pos;
            deleteQuestion(head, pos);
        }
        else if (choice == '5')
        {
            int totalMark = calculateTotalMark(head);
            cout << endl
                 << "Total Mark: " << totalMark << endl
                 << endl;
        }
        else if (choice == '6')
        {
            string filename;
            cout << "Enter the filename to save questions: ";
            cin >> filename;
            saveQuestionsToFile(head, filename);
        }
        else if (choice == '7')
        {
            string filename;
            cout << "Enter the filename to load questions from: ";
            cin >> filename;
            loadQuestionsFromFile(head, filename);
        }
        else if (choice == '8')
        {
            cout << endl
                 << "Exiting the program. Goodbye!" << endl;
            break;
        }
        else
        {
            cout << endl
                 << "Invalid choice. Please try again." << endl;
        }
    }

    // Free memory
    Question *current = head;
    while (current != NULL)
    {
        Question *next = current->next;
        delete current;
        current = next;
    }

    return 0;
}
