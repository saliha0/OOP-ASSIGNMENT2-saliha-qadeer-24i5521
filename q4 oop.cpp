#include <iostream>
#include <string>
using namespace std;

struct Customer {
    int id;
    string name;
    int tickets;
};

class TicketQueue {
private:
    Customer queue[10];
    int front;
    int rear;
    int count;
    bool priorityMode;

public:
    TicketQueue(bool isPriority = false) {
        front = 0;
        rear = -1;
        count = 0;
        priorityMode = isPriority;
    }

    ~TicketQueue() {
        cout << "\nDestructor called. Queue memory cleared.\n";
    }

    bool isEmpty() {
        return (count == 0);
    }

    bool isFull() {
        return (count == 10);
    }

    void Enqueue(int id, string name, int tickets) {
        if (isFull()) {
            cout << "Queue full!\n";
            return;
        }
        rear = (rear + 1) % 10;
        queue[rear].id = id;
        queue[rear].name = name;
        queue[rear].tickets = tickets;
        count++;
        cout << "Added " << name << " (" << tickets << " tickets)\n";
        if (priorityMode) {
            for (int i = 0; i < count - 1; i++) {
                for (int j = i + 1; j < count; j++) {
                    int idx1 = (front + i) % 10;
                    int idx2 = (front + j) % 10;
                    if (queue[idx2].tickets > queue[idx1].tickets) {
                        swap(queue[idx1], queue[idx2]);
                    }
                }
            }
        }
    }

    void Dequeue() {
        if (isEmpty()) {
            cout << "Queue empty!\n";
            return;
        }
        cout << "\nNow Serving: " << queue[front].name
             << " (ID: " << queue[front].id
             << ", Tickets: " << queue[front].tickets << ")\n";
        cout << "Tickets issued successfully!\n";
        front = (front + 1) % 10;
        count--;
    }

    void Display() {
        if (isEmpty()) {
            cout << "No customers.\n";
            return;
        }
        cout << "\nCurrent Queue:\n";
        for (int i = 0; i < count; i++) {
            int idx = (front + i) % 10;
            cout << "ID: " << queue[idx].id
                 << " | Name: " << queue[idx].name
                 << " | Tickets: " << queue[idx].tickets << endl;
        }
    }
};

int main() {
    cout << "??? WELCOME TO CINEMA BOOKING SYSTEM ???\n";
    TicketQueue tq(false);
    tq.Enqueue(1, "Dua", 2);
    tq.Enqueue(2, "Sara", 5);
    tq.Enqueue(3, "Saliha", 3);
    tq.Enqueue(4, "Hadia", 4);
    cout << "\nInitial Queue:";
    tq.Display();
    tq.Dequeue();
    cout << "\nQueue after serving one customer:";
    tq.Display();
    tq.Enqueue(5, "Hassan", 6);
    cout << "\nQueue after adding new customer:";
    tq.Display();
    while (!tq.isEmpty()) {
        tq.Dequeue();
    }
    cout << "\nAll customers served. Queue is now empty.\n";
    return 0;
}

