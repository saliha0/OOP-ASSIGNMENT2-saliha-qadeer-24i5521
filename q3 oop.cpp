#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int BookID;
    string Title;
    string Author;
    Node* next;
    Node* prev;
};

class DoublyLinkedList {
public:
    Node* head;

    DoublyLinkedList() {
        head = NULL;
    }

    void AddAtBeginning(int id, string title, string author) {
        Node* n = new Node;
        n->BookID = id;
        n->Title = title;
        n->Author = author;
        n->prev = NULL;
        n->next = head;
        if (head != NULL)
            head->prev = n;
        head = n;
    }

    void AddAtEnd(int id, string title, string author) {
        Node* n = new Node;
        n->BookID = id;
        n->Title = title;
        n->Author = author;
        n->next = NULL;
        if (head == NULL) {
            n->prev = NULL;
            head = n;
            return;
        }
        Node* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = n;
        n->prev = temp;
    }

    void AddAtPosition(int pos, int id, string title, string author) {
        if (pos <= 1) {
            AddAtBeginning(id, title, author);
            return;
        }
        Node* temp = head;
        for (int i = 1; i < pos - 1 && temp != NULL; i++)
            temp = temp->next;
        if (temp == NULL || temp->next == NULL) {
            AddAtEnd(id, title, author);
            return;
        }
        Node* n = new Node;
        n->BookID = id;
        n->Title = title;
        n->Author = author;
        n->next = temp->next;
        n->prev = temp;
        temp->next->prev = n;
        temp->next = n;
    }

    void DeleteBook(int id) {
        Node* temp = head;
        while (temp != NULL && temp->BookID != id)
            temp = temp->next;
        if (temp == NULL) {
            cout << "Book not found!\n";
            return;
        }
        if (temp->prev != NULL)
            temp->prev->next = temp->next;
        else
            head = temp->next;
        if (temp->next != NULL)
            temp->next->prev = temp->prev;
        delete temp;
        cout << "Book deleted!\n";
    }

    void DisplayForward() {
        Node* temp = head;
        cout << "\nBooks (Forward):\n";
        while (temp != NULL) {
            cout << temp->BookID << " - " << temp->Title << " - " << temp->Author << endl;
            temp = temp->next;
        }
    }

    void DisplayBackward() {
        Node* temp = head;
        if (temp == NULL) return;
        while (temp->next != NULL)
            temp = temp->next;
        cout << "\nBooks (Backward):\n";
        while (temp != NULL) {
            cout << temp->BookID << " - " << temp->Title << " - " << temp->Author << endl;
            temp = temp->prev;
        }
    }
};

int main() {
    DoublyLinkedList list;
    list.AddAtEnd(1, "Python", "Robert");
    list.AddAtEnd(2, "Buisness Maths", "Brigham");
    list.AddAtBeginning(0, "Intro to Programming", "John");
    list.AddAtPosition(2, 5, "Microeconomics", "N. Gregory Mankiw");
    list.DisplayForward();
    list.DisplayBackward();
    list.DeleteBook(2);
    list.DisplayForward();
}

