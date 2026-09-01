#include<iostream>
#include<string.h>
using namespace std;
struct Book{
    int id;
    string title;
    string author;
    int year;
    bool borrowed;
    Book(): id(0), title(""), author(""), year(0), borrowed(false) {}
    Book(int id,string t,string a,int y,bool b):id(id),title(t),author(a),year(y),borrowed(b){}
};

class Library{
private:
    Book* books;
    int size;
    int capacity;
    void resize();
public:
    Library(int max):books(new Book[max]),size(max),capacity(max+5){}
    void addbook();
    Book* getbook();
    void removebook();
    void searchbook();
    bool borrowbook();
    void introducebook();
};

void Library::resize(){
    if(size == capacity){
        Book* newbooks = new Book[capacity*2];
        delete[]books;
        books = newbooks;
        capacity*=2;
    }
}

void Library::addbook(){
    resize();
    books[size]
}
int main(){

}