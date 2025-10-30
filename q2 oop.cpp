#include <iostream>
#include <string>
using namespace std;

class Feature {
public:
    string Name;
    Feature(string n) { 
	Name = n;
	 }
    virtual void analyze() = 0;
    virtual Feature* copy() = 0;
    virtual ~Feature() {}
};

class LandFeature : public Feature {
public:
    LandFeature(string n) : Feature(n) {}
    void analyze() {
	 cout << "Land Feature Detected: " << Name << endl;
	  }
    Feature* copy() { 
	return new LandFeature(Name);
	 }
};

class WaterFeature : public Feature {
public:
    WaterFeature(string n) : Feature(n) {}
    void analyze() { 
	cout << "Water Feature Detected: " << Name << endl;
	 }
    Feature* copy() { 
	return new WaterFeature(Name);
	 }
};

class Node {
public:
    int FeatureID;
    Feature* f;
    Node* next;
    Node(int id, Feature* feat) {
        FeatureID = id;
        f = feat;
        next = NULL;
    }
};

class SinglyLinkedList {
public:
    Node* head;
    SinglyLinkedList() { head = NULL; }

    void insertAtEnd(int id, Feature* f) {
        Node* newNode = new Node(id, f);
        if (head == NULL) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
    }

    void deleteByID(int id) {
        if (head == NULL) return;
        if (head->FeatureID == id) {
            Node* del = head;
            head = head->next;
            delete del->f;
            delete del;
            return;
        }
        Node* temp = head;
        while (temp->next != NULL && temp->next->FeatureID != id)
            temp = temp->next;
        if (temp->next != NULL) {
            Node* del = temp->next;
            temp->next = temp->next->next;
            delete del->f;
            delete del;
        }
    }

    void displayAll() {
        Node* temp = head;
        while (temp != NULL) {
            cout << "Feature ID " << temp->FeatureID << ": ";
            temp->f->analyze();
            temp = temp->next;
        }
    }

    void reverseList() {
        Node* prev = NULL;
        Node* current = head;
        Node* next = NULL;
        while (current != NULL) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    SinglyLinkedList(const SinglyLinkedList& other) {
        head = NULL;
        Node* temp = other.head;
        while (temp != NULL) {
            insertAtEnd(temp->FeatureID, temp->f->copy());
            temp = temp->next;
        }
    }

    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this == &other) return *this;
        clear();
        Node* temp = other.head;
        while (temp != NULL) {
            insertAtEnd(temp->FeatureID, temp->f->copy());
            temp = temp->next;
        }
        return *this;
    }

    SinglyLinkedList operator+(const SinglyLinkedList& other) {
        SinglyLinkedList result;
        Node* temp = head;
        while (temp != NULL) {
            result.insertAtEnd(temp->FeatureID, temp->f->copy());
            temp = temp->next;
        }
        temp = other.head;
        while (temp != NULL) {
            result.insertAtEnd(temp->FeatureID, temp->f->copy());
            temp = temp->next;
        }
        return result;
    }

    void clear() {
        Node* temp = head;
        while (temp != NULL) {
            Node* del = temp;
            temp = temp->next;
            delete del->f;
            delete del;
        }
        head = NULL;
    }

    ~SinglyLinkedList() { clear(); }
};

int main() {
    SinglyLinkedList list1;
    list1.insertAtEnd(1, new LandFeature("Forest"));
    list1.insertAtEnd(2, new WaterFeature("River"));
    list1.insertAtEnd(3, new LandFeature("Desert"));
    list1.insertAtEnd(4, new WaterFeature("Lake"));

    cout << "Original List:\n";
    list1.displayAll();

    cout << "\nAfter deleting ID 2:\n";
    list1.deleteByID(2);
    list1.displayAll();

    cout << "\nAfter reversing list:\n";
    list1.reverseList();
    list1.displayAll();

    SinglyLinkedList list2;
    list2.insertAtEnd(5, new LandFeature("Mountain"));
    list2.insertAtEnd(6, new WaterFeature("Ocean"));

    cout << "\nList 2:\n";
    list2.displayAll();

    SinglyLinkedList merged = list1 + list2;
    cout << "\nAfter concatenating lists (+ operator):\n";
    merged.displayAll();

    SinglyLinkedList copied;
    copied = merged;
    cout << "\nDeep copied list (= operator):\n";
    copied.displayAll();

    return 0;
}



