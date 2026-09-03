#include<iostream>
#include <windows.h>
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
    vector<Book*> searchauthor(const string& author);
    vector<Book*> searchtitle(const string& title);
    Book* getbookid(int id);//
public:
    Library():books(new Book[5]),size(0),capacity(5){}
    Library(int max):books(new Book[max]),size(0),capacity(max){}
    ~Library(){delete[]books;}
    void addbook(const string& title,const string& author,int year);//增加图书
    void getbook(int id);//获取图书信息
    void removebook(int id);//删除图书
    void searchbook_author();//按作者查询图书
    void searchbook_title();//按标题查询图书
    void checkbook(int id);//是否已借出
    void introducebook(int id);//介绍图书信息
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

void Library::addbook(const string& title,const string& author,int year){
    resize();
    books[size].id = size;
    books[size].title = title;
    books[size].author = author;
    books[size].year = year;
    books[size].borrowed = false;
    size++;
}

void Library::removebook(int id){
    if(id>= size||id<0) throw std::out_of_range("下组越界");
    for(int i =id;i<size-1;++i){
        books[i] = books[i+1];
        books[i].id = i;
    }
    size--;
}

Book* Library::getbookid(int id){
    if(id>= size||id<0) throw std::out_of_range("下组越界");
    return &books[id];
}

vector<Book*> Library::searchauthor(const string& author){
    vector<Book*> newbook;
    for(int i = 0;i<size;++i){
        if(books[i].author == author) newbook.push_back(&books[i]);
    }
    return newbook;
}
vector<Book*> Library::searchtitle(const string& title){
    vector<Book*> newbook;
    for(int i = 0;i<size;++i){
        if(books[i].title == title) newbook.push_back(&books[i]);
    }
    return newbook;
}

void Library::getbook(int id){
    Book* book = getbookid(id);
    cout << "Id:" << book->id << " Title:" << book->title
         << " Author:" << book->author << " Year:" << book->year
         << " 借阅状态:" << (book->borrowed ? "已借出" : "在馆") << endl;
    
}

void Library::searchbook_author(){
    string author;
    cin>>author;
    vector<Book*> searchbook = searchauthor(author);
    for(const auto& x:searchbook){
        cout<<"Id:"<<x->id<<"   Title:"<<x->title<<"    Year:"<<x->year<<"  "<<x->borrowed<<endl;
    }
}
void Library::searchbook_title(){
    string title;
    cin>>title;
    vector<Book*> searchbook = searchtitle(title);
    for(const auto& x:searchbook){
        cout<<"Id:"<<x->id<<"   Title:"<<x->title<<"    Year:"<<x->year<<"  "<<x->borrowed<<endl;
    }
}

void Library::checkbook(int id){
    Book* book = getbookid(id);
    if(book->borrowed) cout<<"已借出"<<endl;
    else cout<<"没有借出"<<endl;
}

void Library::introducebook(int id){
    Book* book = getbookid(id);
    cout<<"Id:"<<book->id<<"   Title:"<<book->title<<"    Author:"<<book->author<<"    Year:";
    cout<<book->year<<"    Borrowed:"<<book->borrowed<<endl;
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    Library lib;
    int choice;
    cout<<"请输入您的选择："<<endl;
    cout<<"1.增加图书"<<endl;
    cout<<"2.删除图书"<<endl;
    cout<<"3.按作者查询图书"<<endl;
    cout<<"4.按标题查询图书"<<endl;
    cout<<"5.检查图书借阅状态"<<endl;
    cout<<"6.介绍图书信息"<<endl;
    cout<<"7.退出"<<endl;
    do{
        cin>>choice;
        switch(choice){
            case 1:
                lib.addbook("C++","张三",2023);
                break;
            case 2: {
                int id;
                cout<<"请输入要删除的图书id:"<<endl;
                cin>>id;
                lib.removebook(id);
                break; 
            }
            case 3: {
                cout<<"输入作者:"<<endl;
                lib.searchbook_author();
                break;
            }
            case 4: {
                cout<<"输入标题:"<<endl;
                lib.searchbook_title();
                break;
            }
            case 5: {
                int id;
                cout<<"请输入要检查的图书id:"<<endl;
                cin>>id;
                lib.checkbook(id);
                break;
            }
            case 6: {
                int id;
                cin>>id;
                lib.introducebook(id);
                break;
            }
            case 7: {
                break;
            }
        }
    }while(choice!=7);
    lib.addbook("C++","张三",2023);
    lib.addbook("C","李四",2022);
    lib.addbook("Java","王五",2021);
    lib.addbook("Java","赵六",2020);
    lib.removebook(2);
    lib.getbook(0);
    lib.checkbook(0);
    lib.introducebook(0);
    lib.searchbook_author();//按作者查询图书
    lib.searchbook_title();
    return 0;
}