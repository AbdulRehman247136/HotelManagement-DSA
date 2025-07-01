#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cctype>
using namespace std;

class Hotel {
private:
    struct Node {
        int id;
        string name;
        string room_type;
        string date;
        Node* next;
    };

public:
    Node* head = NULL;

    void insertRoom();
    void updateRoom();
    void searchRoom();
    void deleteRoom();
    void sortRoom();
    void showRoom();
    void saveToFile();
    void loadFromFile();
    void menu();
};

void Hotel::menu() {
    loadFromFile();
    string input;
    int choice;

    do {
        cout << "\nWelcome to the Hotel Management System" << endl;
        cout << "1. Allocate Room" << endl;
        cout << "2. Search Room" << endl;
        cout << "3. Update Room" << endl;
        cout << "4. Delete Room" << endl;
        cout << "5. Show Room Records" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter Your Choice: ";
        getline(cin, input);

        if (input.length() == 1 && isdigit(input[0])) {
            choice = stoi(input);
        } else {
            cout << "Invalid input. Please enter a number between 1 and 6." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                insertRoom();
                break;
            case 2:
                searchRoom();
                break;
            case 3:
                updateRoom();
                break;
            case 4:
                deleteRoom();
                break;
            case 5:
                sortRoom();
                showRoom();
                break;
            case 6:
                saveToFile();
                cout << "Exiting program. Goodbye!" << endl;
                return;
            default:
                cout << "Invalid command. Please try again." << endl;
        }
    } while (true);
}

void Hotel::insertRoom() {
    Node* newNode = new Node;
    cout << "Enter Room ID: ";
    cin >> newNode->id;
    cin.ignore();
    cout << "Enter Customer Name: ";
    getline(cin, newNode->name);
    cout << "Enter Room Type (Single/Double/Twin): ";
    getline(cin, newNode->room_type);
    time_t now = time(0);
    tm* ltm = localtime(&now);
    newNode->date = to_string(1900 + ltm->tm_year) + "-" +
                    to_string(1 + ltm->tm_mon) + "-" +
                    to_string(ltm->tm_mday);
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        Node* ptr = head;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = newNode;
    }

    cout << "Room Allocated Successfully on Date: " << newNode->date << endl;
}

void Hotel::searchRoom() {
    int id;
    if (head == NULL) {
        cout << "No Rooms Found!" << endl;
        return;
    }

    cout << "Enter Room ID: ";
    cin >> id;

    Node* ptr = head;
    while (ptr != NULL) {
        if (id == ptr->id) {
            cout << "Room ID: " << ptr->id << endl;
            cout << "Customer Name: " << ptr->name << endl;
            cout << "Room Allocated Date: " << ptr->date << endl;
            cout << "Room Type: " << ptr->room_type << endl;
            return;
        }
        ptr = ptr->next;
    }

    cout << "Room not found!" << endl;
}

void Hotel::updateRoom() {
    int id;
    if (head == NULL) {
        cout << "No Rooms Found!" << endl;
        return;
    }

    cout << "Enter Room ID to Update: ";
    cin >> id;
    cin.ignore();

    Node* ptr = head;
    while (ptr != NULL) {
        if (id == ptr->id) {
            cout << "Enter New Room ID: ";
            cin >> ptr->id;
            cin.ignore();
            cout << "Enter New Customer Name: ";
            getline(cin, ptr->name);
            cout << "Enter New Room Type: ";
            getline(cin, ptr->room_type);
            time_t now = time(0);
            tm* ltm = localtime(&now);
            ptr->date = to_string(1900 + ltm->tm_year) + "-" +
                        to_string(1 + ltm->tm_mon) + "-" +
                        to_string(ltm->tm_mday);
            cout << "Room Updated Successfully!" << endl;
            return;
        }
        ptr = ptr->next;
    }

    cout << "Room ID not found!" << endl;
}

void Hotel::deleteRoom() {
    int id;
    if (head == NULL) {
        cout << "No Rooms Found!" << endl;
        return;
    }

    cout << "Enter Room ID to Delete: ";
    cin >> id;

    if (id == head->id) {
        Node* ptr = head;
        head = head->next;
        delete ptr;
        cout << "Room Deleted Successfully!" << endl;
        return;
    }

    Node* pre = head;
    Node* ptr = head->next;

    while (ptr != NULL) {
        if (id == ptr->id) {
            pre->next = ptr->next;
            delete ptr;
            cout << "Room Deleted Successfully!" << endl;
            return;
        }
        pre = ptr;
        ptr = ptr->next;
    }

    cout << "Room ID not found!" << endl;
}

void Hotel::sortRoom() {
    if (head == NULL) {
        cout << "No Rooms Found!" << endl;
        return;
    }

    Node* i = head;
    while (i != NULL) {
        Node* j = i->next;
        while (j != NULL) {
            if (i->id > j->id) {
                swap(i->id, j->id);
                swap(i->name, j->name);
                swap(i->date, j->date);
                swap(i->room_type, j->room_type);
            }
            j = j->next;
        }
        i = i->next;
    }
}

void Hotel::showRoom() {
    if (head == NULL) {
        cout << "No Rooms Found!" << endl;
        return;
    }

    Node* ptr = head;
    while (ptr != NULL) {
        cout << "\nRoom ID: " << ptr->id;
        cout << "\nCustomer Name: " << ptr->name;
        cout << "\nAllocated Date: " << ptr->date;
        cout << "\nRoom Type: " << ptr->room_type << endl;
        ptr = ptr->next;
    }
}

void Hotel::saveToFile() {
    ofstream file("newrooms.txt", ios::trunc);
    if (!file) {
        cout << "Error opening file for saving!" << endl;
        return;
    }

    Node* ptr = head;
    while (ptr != NULL) {
        file << ptr->id << endl;
        file << ptr->name << endl;
        file << ptr->room_type << endl;
        file << ptr->date << endl;
        ptr = ptr->next;
    }

    file.close();
    cout << "Data saved to file successfully!" << endl;
}

void Hotel::loadFromFile() {
    ifstream file("newrooms.txt");
    if (!file) {
        cout << "No previous records found." << endl;
        return;
    }

    while (true) {
        Node* newNode = new Node;
        if (!(file >> newNode->id)) {
            delete newNode;
            break;
        }

        file.ignore();
        getline(file, newNode->name);
        getline(file, newNode->room_type);
        getline(file, newNode->date);
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        } else {
            Node* ptr = head;
            while (ptr->next != NULL) {
                ptr = ptr->next;
            }
            ptr->next = newNode;
        }
    }

    file.close();
    cout << "Data loaded from file successfully!" << endl;
}

int main() {
    Hotel h;
    h.menu();
    return 0;
}
