#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>
using namespace std;
struct Book{
    int id;
    string title;
    string author;
    int year;
    bool borrowed;
    Book(): id(0), title(""), author(""), year(0), borrowed(false) {}
    Book(string t,string a,int y,bool b):id(0),title(t),author(a),year(y),borrowed(b){}
    Book& operator=(const Book& p){
        if (this == &p) {
        return *this;
        }
        id = p.id;
        title = p.title;
        author = p.author;
        year = p.year;
        borrowed = p.borrowed;
        return *this;
    }
};

class Library{
private:
    Book* books;
    int size;
    int capacity;
    void resize();
    vector<Book*> searchauthor(string& author);
    vector<Book*> searchtitle(string& title);
    Book* getbookid(int id);
public:
    Library():books(new Book[5]),size(0),capacity(5){}
    Library(int max):books(new Book[max]),size(0),capacity(max){}
    void addbook(string& title,string& author,int year);
    void getbook();
    void removebook();
    void searchbook();
    bool borrowbook();
    void introducebook();
};

void Library::resize(){
    if(size == capacity){
        Book* newbooks = new Book[capacity*2];
        for(int i = 0;i<size;++i){
            newbooks[i] =  books[i];
        }
        delete[]books;
        books = newbooks;
        capacity*=2;
    }
}

void Library::addbook(string& title,string& author,int year){
    resize();
    books[size].id = size;
    books[size].title = title;
    books[size].author = author;
    books[size].year = year;
    books[size].borrowed = 0;
    size++;
}

Book* Library::getbookid(int id){
    if(id>= size||id<0) throw::std::out_of_range("下组越界");
    return &books[id];
}

vector<Book*> Library::searchauthor(string& author){
    vector<Book*> newbook;
    for(int i = 0;i<size;++i){
        if(books[i].author == author) newbook.push_back(&books[i]);
    }
    return newbook;
}
vector<Book*> Library::searchtitle(string& title){
    vector<Book*> newbook;
    for(int i = 0;i<size;++i){
        if(books[i].title == title) newbook.push_back(&books[i]);
    }
    return newbook;
}


int main(){

}