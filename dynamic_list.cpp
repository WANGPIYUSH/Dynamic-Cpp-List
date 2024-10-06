#include<iostream>
#include<vector>
using namespace std;

class Object{
    public:
    Object(){}
    friend ostream &operator<<(ostream &os, const Object &obj)
    {
        return obj.output(os);
    }
    virtual ostream &output(ostream &os) const
    {
        throw runtime_error("Unkown object type");
    }
    virtual Object* get(int index)
    {
        throw runtime_error("Not a list");
    }
};

class Int : public Object{
    private:
    int value;
    public:
    Int(int v) : value(v) {}
    int get() {return value;}
    friend ostream& operator<<(ostream& os, const Int& obj){
        os << obj.value;
        return os;
    }
    ostream &output(ostream &os) const override
    {
        os << value;
        return os;
    }
};

class Char : public Object{
    private:
    char value;
    public:
    Char(char v) : value(v) {}
    char get() {return value;}
    friend ostream& operator<<(ostream& os, const Char& obj)
    {
        os << obj.value;
        return os;
    }
};

class String : public Object{
    private:
    std::string value;
    public:
    String(const std::string& value) : value(value){}
    std::string get(){return value;}
    friend ostream& operator<<(ostream& os, const String& obj)
    {
        os << obj.value;
        return os;
    }
    ostream &output(ostream &os) const override
    {
        os << value;
        return os;
    }
};

class List : public Object{
private:
    struct Node
    {
        Object* data;
        Node* next;
    };
    Node* head;

public:
    List() : head(nullptr) {}
    ~List()
    {
        while (head)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void append(Object* data){
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = nullptr;
        if(!head){
            head = newNode;
        }else{
            Node* last = head;
            while(last->next){
                last = last->next;
            }
            last->next = newNode;
        }
    }
    void append(int value){
        Int* data = new Int(value);
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = nullptr;
        if(!head){
            head = newNode;
        }else{
            Node* last = head;
            while(last->next){
                last = last->next;
            }
            last->next = newNode;
        }
    }
    Object* get(int index){
        Node* current = head;
        int count = 0;
        while(current){
            if(count == index){
                return current->data;
            }
            count++;
            current = current->next;
        }
        throw out_of_range("Index out of range");
    }
    ostream& output(ostream& os) const override {
        os<<'[';
        Node* current = head;
        while(current){
            current->data->output(os);
            current = current->next;
            if (current){
                os << ', ';
            }
        }
        os << ']';
        return os;
    }
    };

int main(){
    Int myInt(44);
    String myString("Hello");
    cout<<myInt<<myString<<endl;
    List l1;
    l1.append(&myInt);
    l1.append(&myString);

    return 0;
}