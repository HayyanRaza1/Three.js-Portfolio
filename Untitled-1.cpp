#include <iostream>
#include <string>
using namespace std;

class Item
{
protected:
    string itemName;
    int itemNumber;
    double price;

public:
    Item() {}

    Item(string name, int number, double price)
        : itemName(name), itemNumber(number), price(price) {}

    virtual void displayItem() const
    {
        cout << "Name: " << itemName << endl;
        cout << "Number: " << itemNumber << endl;
        cout << "Price: " << price << endl;
    }
};

class PhysicalItem : public Item
{
protected:
    string location;
    int quantity;

public:
    PhysicalItem() {}

    PhysicalItem(string name, int number, double price, string loc, int qty)
        : Item(name, number, price), location(loc), quantity(qty) {}

    void displayItem() const override
    {
        Item::displayItem();
        cout << "Location: " << location << endl;
        cout << "Quantity: " << quantity << endl;
    }
};

class DigitalItem : public Item
{
protected:
    string format;

public:
    DigitalItem() {}

    DigitalItem(string name, int number, double price, string fmt)
        : Item(name, number, price), format(fmt) {}

    void displayItem() const override
    {
        Item::displayItem();
        cout << "Format: " << format << endl;
    }
};

class Book : public PhysicalItem
{
protected:
    string author;
    int pages;

public:
    Book() {}

    Book(string name, int number, double price, string loc, int qty, string auth, int pgs)
        : PhysicalItem(name, number, price, loc, qty), author(auth), pages(pgs) {}

    void displayItem() const override
    {
        PhysicalItem::displayItem();
        cout << "Author: " << author << endl;
        cout << "Pages: " << pages << endl;
    }
};

class eBook : public DigitalItem
{
protected:
    string author;
    int pages;

public:
    eBook() {}

    eBook(string name, int number, double price, string fmt, string auth, int pgs)
        : DigitalItem(name, number, price, fmt), author(auth), pages(pgs) {}

    void displayItem() const override
    {
        DigitalItem::displayItem();
        cout << "Author: " << author << endl;
        cout << "Pages: " << pages << endl;
    }
};

class AudioBook : public Book, public eBook
{
private:
    string narrator;
    int duration;

public:
    AudioBook() {}

    AudioBook(string name, int number, double price, string loc, int qty,
              string fmt, string auth, int pgs, string narr, int dur)
        : Book(name, number, price, loc, qty, auth, pgs),
          eBook(name, number, price, fmt, auth, pgs),
          narrator(narr), duration(dur) {}

    void displayItem() const override
    {
        cout << "AudioBook Details:" << endl;
        Book::displayItem(); // Calls Book's displayItem
        cout << "Narrator: " << narrator << endl;
        cout << "Duration: " << duration << " mins" << endl;
    }
};

int main()
{
    Book myBook("Introduction to Programming", 201, 45.5, "Shelf 2", 3, "Hayyan Raza", 320);
    eBook myEBook("Learning C++", 202, 25.99, "EPUB", "Hayyan Raza", 280);
    AudioBook myAudioBook("Mastery in C++", 203, 30.0, "Shelf 1", 5, "MP3", "Hayyan Raza", 200, "Robot Voice", 180);

    cout << "Book Information:" << endl;
    myBook.displayItem();
    cout << endl;

    cout << "eBook Information:" << endl;
    myEBook.displayItem();
    cout << endl;

    cout << "AudioBook Information:" << endl;
    myAudioBook.displayItem();

    return 0;
}
