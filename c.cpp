#include<iostream>
#include <windows.h>
#include<string>
#include<vector>
#include<stdexcept>
#include<fstream>
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
    void savebook();
    void loadbook();
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
    if(searchbook.empty()){
        cout<<"没有这本个author书"<<endl;
    }
    for(const auto& x:searchbook){
        cout<<"Id:"<<x->id<<"   Title:"<<x->title<<"    Year:"<<x->year<<"  "<<x->borrowed<<endl;
    }
}
void Library::searchbook_title(){
    string title;
    cin>>title;
    vector<Book*> searchbook = searchtitle(title);
    if(searchbook.empty()){
        cout<<"没有这本个title书"<<endl;
    }
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

void Library::savebook(){
    ofstream fout("text.txt");
    if(fout.is_open() == false){
        cout<<"this file donot opened"<<endl;
        return;
    }
    for(int i = 0; i < size; ++i){         
        fout << books[i].title  << "\n"
             << books[i].author << "\n"
             << books[i].year   << "\n"
             << (books[i].borrowed ? 1 : 0) << "\n";
    }
    fout.close();
}

void Library::loadbook(){
    ifstream fin("text.txt");
    if(fin.is_open() == false){
        return;
    }
    string t, a;
    int y, flag;
    while(fin >> t >> a >> y >> flag){ 
        addbook(t, a, y);              
        books[size-1].borrowed = flag;  // ← 把你上次的判断填进来
    }
    fin.close();
}
int main(){
    SetConsoleOutputCP(CP_UTF8);
    Library lib;
    lib.loadbook();
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
            case 1:{
                cout<<"请输入title,author,year";
                string q,w;
                int year;
                cin>>q>>w>>year;
                lib.addbook(q,w,year);
                lib.savebook();
                cout<<"添加成功"<<endl;
                break;
            }
            case 2: {
                int id;
                cout<<"请输入要删除的图书id:"<<endl;
                cin>>id;
                lib.removebook(id);
                lib.savebook();
                cout<<"删除成功"<<endl;
                break; 
            }
            case 3: {
                cout<<"输入作者:"<<endl;
                lib.searchbook_author();
                cout<<"成功"<<endl;
                break;
            }
            case 4: {
                cout<<"输入标题:"<<endl;
                lib.searchbook_title();
                cout<<"成功"<<endl;
                break;
            }
            case 5: {
                int id;
                cout<<"请输入要检查的图书id:"<<endl;
                cin>>id;
                lib.checkbook(id);
                cout<<"成功"<<endl;
                break;
            }
            case 6: {
                int id;
                cout<<"请输入要检查的图书id:"<<endl;
                cin>>id;
                lib.introducebook(id);
                cout<<"成功"<<endl;
                break;
            }
            case 7: {
                cout<<"再见"<<endl;
                break;
            }
        }
    }while(choice!=7);
    return 0;
}