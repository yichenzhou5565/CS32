//#include <iostream>
//#include <string>
//#include <vector>
//
//using namespace std;
//
//class Domain
//{
//public:
//    Domain(string lbl) : m_label(lbl) {}
//    string label() const { return m_label; }
//    const vector<Domain*>& subdomains() const { return m_subdomains; }
//    void add(Domain* d) { m_subdomains.push_back(d); }
//    ~Domain();
//private:
//    string m_label;
//    vector<Domain*> m_subdomains;
//};
//
//Domain::~Domain()
//{
//    for (size_t k = 0; k < m_subdomains.size(); k++)
//        delete m_subdomains[k];
//}

void listAll(const Domain* d, string path) // two-parameter overload
{
    if (d==nullptr)
        return;
    vector<Domain*> sub = d->subdomains();
    
    
    
    for (int i=0; i<sub.size(); i++) //trace every child
    {
        if (sub[i]->subdomains().size()==0) //if leaf
        {
            std::cout<<sub[i]->label() ; //output the label at this point
            if (path.empty()==false)
                std::cout<<"."+path;
            std::cout<<std::endl;
            continue;
        }
        
        
        path.empty()==true?listAll(sub[i],sub[i]->label())
        :listAll(sub[i],sub[i]->label()
                 +"."+path
                 );
        if (i==sub.size()-1)
            return;
    }
    
    if (sub.size()==0)
    {
        std::cout<<path<<std::endl;
    }
    
}

//void listAll(const Domain* d)  // one-parameter overload
//{
//    if (d != nullptr)
//        listAll(d, d->label());
//}
//
//int main()
//{
//    Domain* d1 = new Domain("ucla");
//    d1->add(new Domain("cs"));
//    d1->add(new Domain("ee"));
//    d1->add(new Domain("math"));
//    Domain* d2 = new Domain("caltech");
//    d2->add(new Domain("math"));
//    d2->add(new Domain("cs"));
//    Domain* d3 = new Domain("edu");
//    d3->add(d1);
//    d3->add(d2);
//    Domain* d4 = new Domain("com");
//    d4->add(new Domain("microsoft"));
//    d4->add(new Domain("apple"));
//    Domain* d5 = new Domain("biz");
//    Domain* root = new Domain("");
//    root->add(d3);
//    root->add(d4);
//    root->add(d5);
//    listAll(root);
//    cout << "====" << endl;
//    listAll(d2);
//    cout << "====" << endl;
//    listAll(d5);
//    delete root;
//}

/*
 cs.ucla.edu
 ee.ucla.edu
 math.ucla.edu
 math.caltech.edu
 cs.caltech.edu
 microsoft.com
 apple.com
 biz
 ====
 math.caltech
 cs.caltech
 ====
 biz
 */

