#include <iostream>
using namespace std;

//Node protoType Functions
template<class T,int Order>
struct Node
{
    //Node *Parent;
    int NumbersOfKeys;//number of the actual keys
    int order;
    int position=-1;//to allocate value in the appropriate place
    T* keys=new T[order];
    Node** childs=new Node*[order];

    Node (int order);
    int Insert (T value);
    Node* split (Node* node, T* value);
    void Print () ;
    void PrintUtil (int height,bool checkParent);
    int getHeight () ;
    ~Node ();
};
/////////////////////////////////////////////////////////////

//Node implementation
template <class T,int Order>
Node<T,Order>::Node (int order)
{
    this->order = order;
    this->NumbersOfKeys = 0;
}



template <class T,int Order>
int Node<T,Order>::Insert (T value)
{

    //if the node is leaf
    if (this->childs[0] == NULL)
    {
        this->keys[++this->position] = value;
        ++this->NumbersOfKeys;
        //arrange the keys array after put new value in node
        for(int i=this->position; i>0 ; i--)
        {
            if (this->keys[i] < this->keys[i-1]) std::swap(this->keys[i],this->keys[i-1]);
        }
    }
    //if the node is not leaf
    else
    {
        //count to get place of child to put the value in it
        int i=0;
        for(; i<this->NumbersOfKeys>0 && value > this->keys[i];)
        {
            i++;
        }
        //Check if the child is full to split it
        int check=this->childs[i]->Insert(value);
        //if node full
        if(check)
        {
            T mid;
            int TEMP = i;
            Node<T,Order> *newNode = split(this->childs[i], &mid); //Splitted Node to store the values and child that greater than the midValue
            //allocate midValue in correct place
            for(; i<this->NumbersOfKeys>0 && mid > this->keys[i];)
            {
                i++;
            }

            for (int j = this->NumbersOfKeys; j > i ; j--) this->keys[j] = this->keys[j - 1];
            this->keys[i] = mid;

            ++this->NumbersOfKeys;
            ++this->position;

            //allocate newNode Splitted in the correct place
            int k;
            for (k = this->NumbersOfKeys; k > TEMP + 1; k--)
                this->childs[k] = this->childs[k - 1];
            this->childs[k] = newNode;
        }

    }
    if(this->NumbersOfKeys == this->order) return 1;//to split it
    else return 0;
}

template <class T,int Order>
Node<T,Order>* Node<T,Order>::split (Node *node, T *med) //mid to store value of mid and use it in insert func
{
    int NumberOfKeys = node->NumbersOfKeys;
    Node<T,Order> *newNode = new Node<T,Order>(order);
    //Node<T,Order> *newParentNode = new Node<T,Order>(order);
    int midValue = NumberOfKeys / 2;
    *med = node->keys[midValue];
    int i;
    //take the values after mid value
    for (i = midValue + 1; i < NumberOfKeys; ++i)
    {
        newNode->keys[++newNode->position] = node->keys[i];
        newNode->childs[newNode->position] = node->childs[i];
        ++newNode->NumbersOfKeys;
        --node->position;
        --node->NumbersOfKeys;
        node->childs[i] = NULL;
    }
    newNode->childs[newNode->position+1] = node->childs[i];
    node->childs[i] = NULL;

    --node->NumbersOfKeys; //because we take mid value...
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
        for (int i = 0; i < this->NumbersOfKeys; i++){
             if(i==0) cout << "|";
             cout<< this->keys[i];
             if(i!=this->NumbersOfKeys-1) cout<<"|";
             if(i==this->NumbersOfKeys-1) cout << "|"<<" ";
        }

    }

    else
    {
        for (int i = 0; i <= this->NumbersOfKeys; i++){
            this->childs[i]->PrintUtil(height-1,false);
            //cout<<endl<<" ";
        }

    }

}

template <class T,int Order>
int Node<T,Order>::getHeight ()
{
    int COUNT=1;
    Node<T,Order>* Current=this;//current point to root
    while(true){
            //is leaf
        if(Current->childs[0] == NULL){
            return COUNT;
        }
        Current=Current->childs[0];
        COUNT++;
    }
}

//Deallocation
template <class T,int Order>
Node<T,Order>::~Node ()
{
    delete[]keys;
    for (int i = 0; i <= this->NumbersOfKeys; ++i)
        delete this->childs[i];
}
/////////////////////////////////////////////////////////////


//BTree protoType Function
template <class T,int Order>
class BTree
{
private:
    Node<T,Order> *Root;
    int order;
    int count=0;//to count number of elements

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
    this->Root  = NULL;
}

template <class T,int Order>
void BTree<T,Order>::Insert (T value)
{
    count++;
    //if Tree is empty
    if (this->Root == NULL)
    {
        this->Root = new Node<T,Order>(this->order);
        this->Root->keys[++this->Root->position]=value;
        this->Root->NumbersOfKeys=1;
    }
    //if tree not empty
    else
    {
        int check=Root->Insert(value);
        if(check){
            T mid;
            Node<T,Order> *splittedNode = this->Root->split(this->Root, &mid);
            Node<T,Order> *newNode = new Node<T,Order>(this->order);
            newNode->keys[++newNode->position]=mid;
            newNode->NumbersOfKeys=1;
            newNode->childs[0] = Root;
            newNode->childs[1] = splittedNode;
            this->Root = newNode;
        }
    }
}


template <class T,int Order>
void BTree<T,Order>::Print () const
{
    if (Root != NULL)
        Root->Print();
    else cout<<"The B-Tree is Empty"<<endl;
}


template <class T,int Order>
BTree<T,Order>::~BTree ()
{
    delete Root;
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
