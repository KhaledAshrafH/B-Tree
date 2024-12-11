#include <iostream>
using namespace std;

//Node protoType Functions
template<class T,int Order>
struct Node
{
    //Node *Parent;
    int number_of_keys;//number of the actual keys
    int order;
    int position=-1;//to allocate value in the appropriate place
    T* keys;
    Node** children;

    explicit Node (int order);
    int Insert (T value);
    Node* split (Node* node, T* med);
    void Print () ;
    void PrintUtil (int height,bool checkRoot);
    int getHeight () ;
    ~Node ();
};
/////////////////////////////////////////////////////////////

//Node implementation
template <class T,int Order>
Node<T,Order>::Node (int order)
{
    this->order = order;
    this->number_of_keys = 0;
    // Allocate memory AFTER setting order
    this->keys = new T[this->order];
    this->children = new Node*[this->order + 1];

    // Initialize children to NULL
    for (int i = 0; i <= this->order; ++i)
        this->children[i] = nullptr;
}


template <class T,int Order>
int Node<T,Order>::Insert (T value)
{

    //if the node is leafed
    if (this->children[0] == nullptr)
    {
        this->keys[++this->position] = value;
        ++this->number_of_keys;
        //arrange the key array after put new value in node
        for(int i=this->position; i>0 ; i--)
            if (this->keys[i] < this->keys[i-1])
                std::swap(this->keys[i],this->keys[i-1]);
    }
    //if the node is not leaf
    else
    {
        //count to get place of child to put the value in it
        int i=0;
        for(; i<this->number_of_keys && value > this->keys[i];)
            i++;

        //Check if the child is full to split it
        int check=this->children[i]->Insert(value);
        //if node full
        if(check)
        {
            T mid;
            int TEMP = i;
            Node<T,Order> *newNode = split(this->children[i], &mid); //Split Node
            // to store the values and child that greater than the midValue
            //allocate midValue the correct place
            for(; i<this->number_of_keys && mid > this->keys[i];)
                i++;

            for (int j = this->number_of_keys; j > i ; j--)
                this->keys[j] = this->keys[j - 1];
            this->keys[i] = mid;
            ++this->number_of_keys;
            ++this->position;

            //allocate newNode Split in the correct place
            int k;
            for (k = this->number_of_keys; k > TEMP + 1; k--)
                this->children[k] = this->children[k - 1];
            this->children[k] = newNode;
        }

    }
    if(this->number_of_keys == this->order)
        return 1;//to split it
    else return 0;
}

template <class T,int Order>
Node<T,Order>* Node<T,Order>::split (Node *node, T *med) //mid to store value of mid and use it in insert func
{
    int NumberOfKeys = node->number_of_keys;
    auto *newNode = new Node<T,Order>(order);
    //Node<T,Order> *newParentNode = new Node<T,Order>(order);
    int midValue = NumberOfKeys / 2;
    *med = node->keys[midValue];
    int i;
    //take the values after mid-value
    for (i = midValue + 1; i < NumberOfKeys; ++i)
    {
        newNode->keys[++newNode->position] = node->keys[i];
        newNode->children[newNode->position] = node->children[i];
        ++newNode->number_of_keys;
        --node->position;
        --node->number_of_keys;
        node->children[i] = nullptr;
    }
    newNode->children[newNode->position + 1] = node->children[i];
    node->children[i] = nullptr;

    --node->number_of_keys; //because we take mid-value...
    --node->position;
    return newNode;
}


template <class T,int Order>
void Node<T,Order>::Print ()
{
    int height = this->getHeight(); //number of levels  -> log (n)
    for (int i = 1; i <= height; ++i) //50 levels maximum
    {
        //O(n)
        if(i==1)PrintUtil(i,true);
        else PrintUtil(i,false);
        cout<<endl;
    }
    cout<<endl;
}

template <class T,int Order>
void Node<T,Order>::PrintUtil (int height,bool checkRoot)
{
    //to print all values in the level
    if (height==1 || checkRoot)
    {
        for (int i = 0; i < this->number_of_keys; i++){
             if(i==0) cout << "|";
             cout<< this->keys[i];
             if(i!=this->number_of_keys-1) cout<<"|";
             if(i==this->number_of_keys-1) cout << "|"<<" ";
        }

    }

    else
    {
        for (int i = 0; i <= this->number_of_keys; i++)
            this->children[i]->PrintUtil(height - 1, false);
            //cout<<endl<<" ";
    }

}

template <class T,int Order>
int Node<T,Order>::getHeight ()
{
    int COUNT=1;
    Node<T,Order>* Current=this;//current point to root
    while(true){
            //is leafed
        if(Current->children[0] == nullptr)
            return COUNT;
        Current=Current->children[0];
        COUNT++;
    }
}

// De-allocation
template <class T,int Order>
Node<T,Order>::~Node ()
{
    delete[]keys;
    // Only delete non-NULL child pointers
    for (int i = 0; i <= this->number_of_keys; ++i)
        delete children[i];
    delete[] children;
}
/////////////////////////////////////////////////////////////


//BTree protoType Function
template <class T,int Order>
class BTree
{
private:
    Node<T,Order> *root;
    int order;
    int count=0; //to count the number of elements

public:
    BTree ();
    void Insert (T value);
    void Print () const;
    ~BTree ();
};
/////////////////////////////////////////////////////////////


//BTree implementation
template <class T,int Order>
BTree<T,Order>::BTree()
{
    this->order = Order;
    this->root  = nullptr;
    this->count=0;
}

template <class T,int Order>
void BTree<T,Order>::Insert (T value)
{
    count++;
    //if the Tree is empty
    if (this->root == nullptr)
    {
        this->root = new Node<T,Order>(this->order);
        this->root->keys[++this->root->position]=value;
        this->root->number_of_keys=1;
    }
    //if a tree doesn't empty
    else
    {
        int check=root->Insert(value);
        if(check){
            T mid;
            Node<T,Order> *splitNode = this->root->split(this->root, &mid);
            auto *newNode = new Node<T,Order>(this->order);
            newNode->keys[++newNode->position]=mid;
            newNode->number_of_keys=1;
            newNode->children[0] = root;
            newNode->children[1] = splitNode;
            this->root = newNode;
        }
    }
}


template <class T,int Order>
void BTree<T,Order>::Print () const
{
    if (root != nullptr)
        root->Print();
    else cout<<"The B-Tree is Empty"<<endl;
}


template <class T,int Order>
BTree<T,Order>::~BTree ()
{
    delete root;
}


////////////////////////////////////////////////////////////
int main ()
{
    // Construct a BTree of order 3, which stores int data
    BTree<int,3> t1;
    t1.Insert(1);
    t1.Insert(5);
    t1.Insert(0);
    t1.Insert(4);
    t1.Insert(3);
    t1.Insert(2);
    t1.Print(); // Should output the following on the screen:
    /*
    1,4
      0
      2,3
      5
    */
    // Construct a BTree of order 5, which stores char data
    BTree<char,5> t;
    // Look at the example in our lecture:
    t.Insert('G');
    t.Insert('I');
    t.Insert('B');
    t.Insert('J');
    t.Insert('C');
    t.Insert('A');
    t.Insert('K');
    t.Insert('E');
    t.Insert('D');
    t.Insert('S');
    t.Insert('T');
    t.Insert('R');
    t.Insert('L');
    t.Insert('F');
    t.Insert('H');
    t.Insert('M');
    t.Insert('N');
    t.Insert('P');
    t.Insert('Q');
    t.Print(); // Should output the following on the screen:
    //t.traverse();
    /*
    K
      C,G
        A,B
        D,E,F
        H,I,J
      N,R
        L,M
        P,Q
        S,T
    */
    return 0;
}
