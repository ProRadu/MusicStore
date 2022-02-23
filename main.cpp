#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>

using namespace std;

class Product{
protected:
double price;
string name;
public:
    Product() : Product(0,""){}
    Product(double price, const string &name) : price(price), name(name) {}

    const string &getName() const {
        return name;
    }

    friend ostream &operator<<(ostream &os, const Product &product) {
        product.afisare(os);
        return os;
    }
    virtual ostream & afisare(ostream& os) const{
        os << "price: " << price << " name: " << name;
        return os;
    }

    friend istream &operator>>(istream &is, Product &product){
        product.citire(is);
        return is;
    }
    virtual istream & citire(istream &is){
        cout<<"price:\n";
        is>>price;
        cout<<"name:\n";
        is.get();
        getline(is, name);
        return is;
    }
    virtual void split(const string& s, char separator, vector<string> &v){
        size_t i = 0;
        size_t j = s.find(separator);
        while(j != s.length()){
            v.push_back(s.substr(i, j-i));
            i=j+1;
            j=s.find(separator,j);
            if(j==s.length()-1)
                v.push_back(s.substr(i,s.length()));
        }
    }

    virtual bool isCompatibleWith(Product *other){
        vector<string> n;
        split(name,' ',n);
        return false;
    }
};

class MusicPlayer : public Product{
protected:
    string title, singer;
public:
    MusicPlayer() : MusicPlayer(0,"","",""){}
    MusicPlayer(double price, const string &name, const string &title, const string &singer) : Product(price, name),
                                                                                               title(title),
                                                                                               singer(singer) {}

    const string &getTitle() const {
        return title;
    }

    const string &getSinger() const {
        return singer;
    }

    istream &citire(istream &is) override {
        Product::citire(is);
        cout<<"title:\n";
        is.get();
        getline(is, title);
        cout<<"singer:\n";
        is.get();
        getline(is, singer);
        return is;
    }

    ostream &afisare(ostream &os) const override {
        Product::afisare(os);
        cout<< " title: "<<title<<" singer: "<<singer;
        return os;
    }

    bool isCompatibleWith(Product *other) override {
        Product::isCompatibleWith(other);
        vector<string > t, s;
        split(title,' ',t);
        split(singer,' ',s);
        return false;
    }

    void split(const string &s, char separator, vector<string> &n) override {
        Product::split(s, separator, n);
    }
};

class Song : public Product{
protected:
    vector<string> author;
    string title;
    int seconds;
public:
    Song() : Song(0,"",{""},"",0) {}
    Song(double price, const string &name, const vector<string> &author,const string &title, int seconds) : Product(price, name),
                                                                                        author(author),
                                                                                        title(title),
                                                                                        seconds(seconds) {}

    const vector<string> &getAuthor() const {
        return author;
    }

    const string &getTitle() const {
        return title;
    }

    istream &citire(istream &is) override {
        Product::citire(is);
        string autor;
        int i;
        cout<<"title:\n";
        is>>title;
        cout<<"number of authors:\n";
        is>>i;
        for(int j=0;j<i;j++)
        {
            cout<<"autor "<<j+1<<":\n";
            is.get();
            getline(is,autor);
            author.push_back(autor);
        }
        cout<<"seconds: ";
        is>>seconds;
        return is;
    }

    ostream &afisare(ostream &os) const override {
        Product::afisare(os);
        cout<<" title: "<<title;
        cout<<" author(s): ";
        for(auto i: author)
            cout<<i<<" ";
        cout<<"seconds: "<<seconds;
        return os;
    }

    bool isCompatibleWith(Product *other) override {
        Product::isCompatibleWith(other);
        vector<string > t;
        split(title,' ',t);
        for(auto i: author)
        {
            vector<string > a;
            split(i,' ', a);
        }
        return false;
    }

    void split(const string &s, char separator, vector<string> &v) override {
        Product::split(s, separator, v);
    }
};

class Sticker : public Product{
string printedText;
public:
    Sticker() : Sticker(0,"",""){}
    Sticker(double price, const string &name, const string &printedText) : Product(price, name),
                                                                           printedText(printedText) {}

    const string &getPrintedText() const {
        return printedText;
    }

    istream &citire(istream &is) override {
        Product::citire(is);
        cout<<"printedText:\n";
        is.get();
        getline(is,printedText);
        return is;
    }

    ostream &afisare(ostream &os) const override {
        Product::afisare(os);
        cout<<" printedText"<<printedText;
        return os;
    }

    void split(const string &s, char separator, vector<string> &v) override {
        Product::split(s, separator, v);
    }

    bool isCompatibleWith(Product *other) override {
        Product::isCompatibleWith(other);
        vector<string > p;
        split(printedText,' ',p);
        return false;
    }
};

class Vinyl : public virtual Song{

public:
    Vinyl() : Vinyl(0,"",{""},"",0){}
    Vinyl(double price, const string &name, const vector<string> &author, const string &title, int seconds) : Song(price, name, author,title,
                                                                                              seconds) {}

    istream &citire(istream &is) override {
        Song::citire(is);
        return is;

    }

    ostream &afisare(ostream &os) const override {
        Song::afisare(os);
        return os;
    }

    bool isCompatibleWith(Product *other) override {
        Song::isCompatibleWith(other);
    }

    void split(const string &s, char separator, vector<string> &v) override {
        Song::split(s, separator, v);
    }
};

class CD : public virtual Song{

public:
    CD() : CD(0,"",{""},"",0) {}
    CD(double price, const string &name, const vector<string> &author, const string &title, int seconds) : Song(price, name, author, title,
                                                                                           seconds) {}

    istream &citire(istream &is) override {
        Song::citire(is);
        return is;
    }

    ostream &afisare(ostream &os) const override {
        Song::afisare(os);
        return os;
    }

    bool isCompatibleWith(Product *other) override {
        Song::isCompatibleWith(other);
    }

    void split(const string &s, char separator, vector<string> &v) override {
        Song::split(s, separator, v);
    }
};

class VinylPlayer : public virtual MusicPlayer{

public:
    VinylPlayer() : VinylPlayer(0,"","","") {}
    VinylPlayer(double price, const string &name, const string &title, const string &singer) : MusicPlayer(price, name,
                                                                                                           title,
                                                                                                           singer) {}

    istream &citire(istream &is) override {
        MusicPlayer::citire(is);
        return is;
    }

    ostream &afisare(ostream &os) const override {
        MusicPlayer::afisare(os);
        return os;
    }

    bool isCompatibleWith(Product *other) override {
        return MusicPlayer::isCompatibleWith(other);
    }

    void split(const string &s, char separator, vector<string> &n) override {
        MusicPlayer::split(s, separator, n);
    }
};

class CdPlayer : public virtual MusicPlayer{

public:
    CdPlayer() : CdPlayer(0,"","","") {}
    CdPlayer(double price, const string &name, const string &title, const string &singer) : MusicPlayer(price, name,
                                                                                                        title,
                                                                                                        singer) {}

    istream &citire(istream &is) override {
        MusicPlayer::citire(is);
        return is;
    }

    ostream &afisare(ostream &os) const override {
        MusicPlayer::afisare(os);
        return os;
    }

    bool isCompatibleWith(Product *other) override {
        return MusicPlayer::isCompatibleWith(other);
    }

    void split(const string &s, char separator, vector<string> &n) override {
        MusicPlayer::split(s, separator, n);
    }
};

///Incercasem sa fac alocare ca in exemplul cu profesori, dar ajunge sa nu fie nevoie separat de functie pentru ca este rezolvata alocarea de addProduct
//Product *alocaDinamic(Product *product){
//    Product *asProduct=dynamic_cast<Product*>(product);
//    MusicPlayer *asMusicPlayer=dynamic_cast<MusicPlayer*>(product);
//    Song *asSong=dynamic_cast<Song*>(product);
//    Sticker *asSticker=dynamic_cast<Sticker*>(product);
//    Vinyl *asVinyl=dynamic_cast<Vinyl*>(product);
//    CD *asCD=dynamic_cast<CD*>(product);
//    VinylPlayer *asVinylPlayer=dynamic_cast<VinylPlayer*>(product);
//    CdPlayer *asCdPlayer=dynamic_cast<CdPlayer*>(product);
//    Product *newProduct = nullptr;
//    if(asProduct != nullptr)
//        newProduct= new Product(*asProduct);
//    else if(asMusicPlayer != nullptr)
//        newProduct= new MusicPlayer(*asMusicPlayer);
//    else if(asSong != nullptr)
//        newProduct= new Song(*asSong);
//    else if(asSticker != nullptr)
//        newProduct= new Sticker(*asSticker);
//    else if(asVinyl != nullptr)
//        newProduct= new Vinyl(*asVinyl);
//    else if(asCD != nullptr)
//        newProduct= new CD(*asCD);
//    else if(asVinylPlayer != nullptr)
//        newProduct= new VinylPlayer(*asVinylPlayer);
//    else if(asCdPlayer != nullptr)
//        newProduct= new CdPlayer(*asCdPlayer);
//    return newProduct;
//}

Product *createProduct(){
    int tip;
    cout<<"Tip produs(0=MusicPlayer, 1=Song, 2=Sticker, 3=Vinyl, 4=CD, 5=VinylPlayer, 6=CdPlayer): ";
    cin>>tip;

    Product *product= nullptr;
    if(tip==0)
        product= new MusicPlayer;
    else if(tip==1)
        product= new Song;
    else if(tip==2)
        product= new Sticker;
    else if(tip==3)
        product= new Vinyl;
    else if(tip==4)
        product= new CD;
    else if(tip==5)
        product= new VinylPlayer;
    else if(tip==6)
        product= new CdPlayer;

    if(product != nullptr)
        cin>> *product;
    return product;
}

class MusicStore{
vector<Product*> products;
public:
    MusicStore() {}

    MusicStore(const vector<Product *> &products) : products(products) {}

    virtual ~MusicStore(){
        for(auto *product: products)
            delete product;
    }

    friend ostream &operator<<(ostream &os, const MusicStore &store) {
        store.afisare(os);
        return os;
    }
    virtual ostream & afisare(ostream &os) const{
        os << "products: "<<endl;
        for(auto i: products)
            os<< *i<<endl;
        return os;
    }

    void citesteNProduse(){
        int n, i;
        cout<<"n= ";
        cin>>n;
        for(i=0;i<n;i++) {
            cout << "Citeste produs " << i + 1 << endl;
            products.push_back(createProduct());
        }
    }

    void addProduct(){
        products.push_back(createProduct());
    }

    void addProduct(const Product& product){
        Product* newProduct= nullptr;
        try {
            auto asMusicPlayer=dynamic_cast<const MusicPlayer&>(product);
            newProduct=new MusicPlayer(asMusicPlayer);
        }catch (bad_cast&){}
        try {
            auto asSong=dynamic_cast<const Song&>(product);
            newProduct=new Song(asSong);
        }catch (bad_cast&){}
        try {
            auto asSticker=dynamic_cast<const Sticker&>(product);
            newProduct=new Sticker(asSticker);
        }catch (bad_cast&){}
        try {
            auto asVinyl=dynamic_cast<const Vinyl&>(product);
            newProduct=new Vinyl(asVinyl);
        }catch (bad_cast&){}
        try {
            auto asCD=dynamic_cast<const CD&>(product);
            newProduct=new CD(asCD);
        }catch (bad_cast&){}
        try {
            auto asVinylPlayer=dynamic_cast<const VinylPlayer&>(product);
            newProduct=new VinylPlayer(asVinylPlayer);
        }catch (bad_cast&){}
        try {
            auto asCdPlayer=dynamic_cast<const CdPlayer&>(product);
            newProduct=new CdPlayer(asCdPlayer);
        }catch (bad_cast&){}
        products.push_back(newProduct);
    }

    void produseCompatibile(){
        cout<<"Deocamdata sunt implementate doar partial metodele de isCompatibleWith in fiecare clasa"<<endl;
    }

    void menu(){
        cout<<"1. Citeste n produse"<<endl;
        cout<<"2. Adauga produs nou"<<endl;
        cout<<"3. Afiseaza produse compatibile"<<endl;
        cout<<"4. Afiseaza toate produsele"<<endl;
        cout<<"5. Exit"<<endl;
    }

    void run(){
        int option;
        while (true){
            menu();
            cout<<"Optiune: ";
            cin>> option;
            if(option==1)
                citesteNProduse();
            else if(option==2)
                addProduct();
            else if(option==3)
                produseCompatibile();
            else if(option==4)
                cout<< * this;
            else break;
        }
    }

};
int main() {
    vector<Product *> v = {
            new Vinyl(100,"Negativ Film 1",{"Klaus Badelt"},"The Black Pearl", 136),
            new Sticker(15,"Corabie", "You are a pirate!"),
            new CD(25,"Negativ Film 2",{"Klaus Badelt"},"He is a pirate", 90),
            new CdPlayer(200,"CD Player", "Pirate", "Jack Sparrow"),
            new VinylPlayer(500,"Classical Music", "Violin", "Sergei Rachmaninoff")
    };
    MusicStore musicStore(v);
    musicStore.run();
}
