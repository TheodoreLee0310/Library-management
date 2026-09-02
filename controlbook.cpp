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
public:
    Library(int max):books(new Book[max]),size(0),capacity(max){}
    void addbook(string& title,string& author,int year,bool borrowed);
    Book* getbookid(int id);
    vector<Book*> getbookauthor(string& author);
    void removebook(int id);
    void remove(string& author);
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

void Library::addbook(string& title,string& author,int year,bool borrowed){
    resize();
    books[size].id = size;
    books[size].title = title;
    books[size].author = author;
    books[size].year = year;
    books[size].borrowed = 0;
    size++;
}

Book* Library::getbookid(int id){
    if(id>= size||id<0) std::overflow_error("下组越界");
    return &books[id];
}

vector<Book*> Library::getbookauthor(string& author){
    
    vector<Book*>
}
    void Library::removebook(int id){

    }
    void Library::remove(string& author){

    }
    void Library::searchbook(){

    }
    bool Library::borrowbook(){

    }
    void Library::introducebook()
int main(){

}