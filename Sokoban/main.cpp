#include <iostream>
#include <fstream>
using namespace std;



/*
            DATA STRUCTURES METHODS

METHOD 1 : Storing Sokoban type values in DoublyLinkedList
METHOD 2 : Storing Sokoban type values in StackQueue

*/

//change number of method below (1 or 2) according to wanted DATA STRUCTURES
#define METHOD 1







const int Max_member=200;



template <class T>                      //I declared a node class which has 3 public members
class Node{                              // next* points to next node;
public:                                 //prev* point previous node
    Node<T> *next;                      //data is actual element of node, it will be sokoban type in main func.
    Node<T> *prev;                      //I declared 2 constructors.First one for default
    T data;                             //I will use the other one to assign sokoban type value to data.
    Node(void);
    Node(const T& item);
    ~Node(void);
};

template <class T>                      //GetNode is a special function for nodes.I will create nodes with this func.
Node<T>* GetNode(const T& item){        //return of this function is to be a pointer which points created node
    Node<T> *newnode;
    newnode=new Node<T>(item);
    return newnode;
}

template <class T>                      //I declared doublylinked list class.I will arrange and connect the nodes with
class DoublyLinkedList{                 //using public methods of this class, which have access to reach Node class.
private:                                //One private member will be head of this linked list.
    Node<T>* head;                      //It will point the first created node.
    public:
    DoublyLinkedList();                     //Two cons,one of them for default.I will use other one and i will create a node
    DoublyLinkedList(const T& item);        //using const T& item and GetNode func. Then i will assign the pointer of this
    void dinsert(const T& item);            //created node to head.
    T ddelete(void);                        //Insert and delete functions are simply add and delete nodes. I used temporary
    T headup(void);                         //pointer to Node class to reach at the end of linked list.Depending on the func
    T showlast(void)const;                  //i changed the pointers of the last node.
    int LinkedListLength(void)const;
    ~DoublyLinkedList(void);                                        //In head up,i moved forward the head.In Sokoban puzzle ,pressing r replays
};                                          //all moves.I will use headup function to return every stored data starting from
                                            //actual head.
                                            //Showlast is similar to peek method in stackqueue class.I will not delete the node
                                            //and return the data of it.
                                            //Linkedlistlength is for 'r' key again,it defines how many times iteration will
                                            //work.


template <class T>                              //In stackqueue class i implemented an array which will hold sokoban type values
class StackQueue{                               //i assigned front,rear and count to zero in constructor.
private:                                        //In push front and pop front i changed the front and count accordingly.
    T StackQueue_list[Max_member];              //In pop rear method i increased the r number and decreased c.
    int f;                                      //peek front simply shows the content of front element without deleting.
    int r;                                      //empty and full methods for checking stackqueue array.
    int c;                                      //since these are simply and well known methods i did not explained in detail.
public:
    StackQueue(void);
    int StackQueue_length(void)const;
    void push_front(const T& item);
    T pop_front(void);
    T pop_rear(void);
    T peek_front(void)const;
    int stack_queue_empty(void)const;
    int stack_queue_full(void)const;
};

class Sokoban{                                      //In sokoban class i used 3 private members.
private:                                            //i used a 2d array for game map,it is given as 6x8.
    char gamemap[6][8];                             //in x_of_player i hold the x-axis position of '@'
    int x_of_player;                                //in y_of_player i hold the y-axis position of '@'
    int y_of_player;                                //later i will explain how i modified this members.
public:                                             //since there are so many public methods i explained them in method
    Sokoban(void);                                  //declaration section.
    Sokoban(const Sokoban& obj);                    //I used many public methods to implement a well and good structured
    Sokoban& operator=(const Sokoban& rhs);         //class.If i did not use them here, i would have to write too long
                                                    //codes for each method.
    void player_location(void);

    char position_control(void)const;
    char up_control(void)const;
    char down_control(void)const;
    char left_control(void)const;
    char right_control(void)const;
    char double_up_control(void)const;
    char double_down_control(void)const;
    char double_left_control(void)const;
    char double_right_control(void)const;

    void set_position(const char& item);
    void set_up(const char& item);
    void set_down(const char& item);
    void set_left(const char& item);
    void set_right(const char& item);
    void set_double_up(const char& item);
    void set_double_down(const char& item);
    void set_double_left(const char& item);
    void set_double_right(const char& item);

    void leaving_position(void);

    bool move_up(void);
    bool move_down(void);
    bool move_left(void);
    bool move_right(void);

    bool is_solved(void)const;
    void print_puzzle(void)const;

};


int main()
{
    Sokoban gamedemo;                                       //I created an instance for sokoban class.
    char operation;                                         //I used switch/case statement for 'w','a','s','d','z','r' commands
                                                            //I used operation char as switch
    #if METHOD==1                                           //I defined global if else for method.it can be changed from top.
    DoublyLinkedList<Sokoban> sokoban_dll(gamedemo);
    gamedemo.print_puzzle();
                                                            //While loop will work always,it will wait for user input always
    while(true){                                            //checks for puzzle is solved
                                                            //if not,reads the operation
        if(gamedemo.is_solved()){                           //if it is either 'w','a','s','d' it will first move than store it
                cout<<"Congratulations!"<<endl;             //in stackqueue or doubly-linkedlist.Then it prints the current
        }                                                   //state and break.
        cin>>operation;                                     //if it is 'z', it deletes the last node/stackqueue element and
                                                            //reads the element before it.(without deleting)Then assigns this
        switch(operation){                                  //value to gamedemo instance of Sokoban class. Lastly,it prints
                                                            //the red value.
    case 'w':                                               //if it is 'r', i started to pop from rear/move head up(headup method)
        if(gamedemo.move_up()){                             //and prints these values up to list/stackqueue is empty.
            sokoban_dll.dinsert(gamedemo);                  //The main algorithm is same for both doubly linked list & stackqueueu
            gamedemo.print_puzzle();                        //Same methods with different names apper in method 2 ,too.
        }
        break;

    case 'a':
        if(gamedemo.move_left()){
            sokoban_dll.dinsert(gamedemo);
            gamedemo.print_puzzle();
        }
        break;

    case 's':
        if(gamedemo.move_down()){
            sokoban_dll.dinsert(gamedemo);
            gamedemo.print_puzzle();
        }
        break;

    case 'd':
        if(gamedemo.move_right()){
            sokoban_dll.dinsert(gamedemo);
            gamedemo.print_puzzle();
        }
        break;

    case 'z':
        sokoban_dll.ddelete();
        gamedemo=sokoban_dll.showlast();
        gamedemo.print_puzzle();
        break;

    case 'r':
            while(sokoban_dll.LinkedListLength()!=0){
                gamedemo=sokoban_dll.headup();
                gamedemo.print_puzzle();
            }
        break;

    default:
        cout<<"undefined operation"<<endl;
        }
    }
    #endif // METHOD



    #if METHOD==2
    StackQueue<Sokoban> sokoban_sq;
    sokoban_sq.push_front(gamedemo);
    gamedemo.print_puzzle();

    while(true){

        if(gamedemo.is_solved()){
                cout<<"Congratulations!"<<endl;
        }
        cin>>operation;

        switch(operation){

    case 'w':
        if(gamedemo.move_up()){
            sokoban_sq.push_front(gamedemo);
            gamedemo.print_puzzle();
        }
        break;

    case 'a':
        if(gamedemo.move_left()){
            sokoban_sq.push_front(gamedemo);
            gamedemo.print_puzzle();
        }
        break;

    case 's':
        if(gamedemo.move_down()){
            sokoban_sq.push_front(gamedemo);
            gamedemo.print_puzzle();
        }
        break;

    case 'd':
        if(gamedemo.move_right()){
            sokoban_sq.push_front(gamedemo);
            gamedemo.print_puzzle();
        }
        break;

    case 'z':
        sokoban_sq.pop_front();
        gamedemo=sokoban_sq.peek_front();
        gamedemo.print_puzzle();
        break;

    case 'r':
            while(sokoban_sq.StackQueue_length()!=0){
                gamedemo=sokoban_sq.pop_rear();
                gamedemo.print_puzzle();
            }
        break;

    default:
        cout<<"undefined operation"<<endl;
        }
    }
    #endif // METHOD


    return 0;
}



Sokoban::Sokoban(void){                                                   //this method reads text file and assigns each value
    string path = "sample_puzzle.txt";                                     //to gamemap.
    char dummy;
    ifstream file;
    file.open(path);
    for(int i=0; i<6; ++i){
        for(int j=0; j<8; ++j){
        file >> noskipws >> gamemap[i][j];
    }
    file >> noskipws >> dummy;
}
file.close();

    x_of_player=1;                                              //firstly, '@' is at this location.
    y_of_player=2;

}

Sokoban::Sokoban(const Sokoban& obj){                       //copy constructor :it asssigns obj.gamemap values to gamemap.
    for(int i=0;i<6;i++){
        for(int j=0;j<8;j++){
            gamemap[i][j]=obj.gamemap[i][j];
        }
    }
    x_of_player=obj.x_of_player;
    y_of_player=obj.y_of_player;
}

Sokoban& Sokoban::operator=(const Sokoban& rhs){           //since = is not a well defined operation for sokoban,
    for(int i=0;i<6;i++){                                  //i modified assignment operator.From now on,
        for(int j=0;j<8;j++){                              // = means assigning corresponding gamemap value of right hand side
            gamemap[i][j]=rhs.gamemap[i][j];               //to gamemap value of left hand side.
        }
    }
    x_of_player=rhs.x_of_player;                            //same for x_&y_ private members.
    y_of_player=rhs.y_of_player;
    return *this;
}


void Sokoban::player_location(void){                        //It searches for either '+' or '@' and assigns x and y the
    for(int i=0;i<6;i++){                                   //related values. Basically, finds player location.
        for(int j=0;j<8;j++){
            if(gamemap[i][j]==('@'|'+')){
                x_of_player=j;
                y_of_player=i;
                break;
            }
        }
    }
}

char Sokoban::position_control(void)const{                  //returns what there is at player location ('@' generally)
    return gamemap[y_of_player][x_of_player];
}

char Sokoban::up_control(void)const{                        //returns what there is at 1 step up of the player.
    return gamemap[y_of_player-1][x_of_player];             //the decrement of y is due to array decleration.
}                                                           //[0][0] is upmost leftside of gamemap.

char Sokoban::down_control(void)const{                      //returns what there is at 1 step down of the player.
    return gamemap[y_of_player+1][x_of_player];
}

char Sokoban::left_control(void)const{                      //returns what there is at 1 step left of the player.
    return gamemap[y_of_player][x_of_player-1];
}

char Sokoban::right_control(void)const{                     //returns what there is at 1 step right of the player.
    return gamemap[y_of_player][x_of_player+1];
}

char Sokoban::double_up_control(void)const{                 //returns what there is at 2 step up of the player.
    return gamemap[y_of_player-2][x_of_player];
}

char Sokoban::double_down_control(void)const{               //returns what there is at 2 step down of the player.
    return gamemap[y_of_player+2][x_of_player];
}

char Sokoban::double_left_control(void)const{               //returns what there is at 2 step left of the player.
    return gamemap[y_of_player][x_of_player-2];
}

char Sokoban::double_right_control(void)const{              //returns what there is at 2 step right of the player.
    return gamemap[y_of_player][x_of_player+2];
}






void Sokoban::set_position(const char& item){               //changes the 1 step up of player location.
    gamemap[y_of_player][x_of_player]=item;                 //same algorithm for below ones.
}

void Sokoban::set_up(const char& item){
    gamemap[y_of_player-1][x_of_player]=item;
}

void Sokoban::set_down(const char& item){
    gamemap[y_of_player+1][x_of_player]=item;
}

void Sokoban::set_left(const char& item){
    gamemap[y_of_player][x_of_player-1]=item;
}

void Sokoban::set_right(const char& item){
    gamemap[y_of_player][x_of_player+1]=item;
}

void Sokoban::set_double_up(const char& item){
    gamemap[y_of_player-2][x_of_player]=item;
}

void Sokoban::set_double_down(const char& item){
    gamemap[y_of_player+2][x_of_player]=item;
}

void Sokoban::set_double_left(const char& item){
    gamemap[y_of_player][x_of_player-2]=item;
}

void Sokoban::set_double_right(const char& item){
    gamemap[y_of_player][x_of_player+2]=item;
}

void Sokoban::leaving_position(void){                       //I used this function in other methods so many times,
    switch(position_control()){                             //i declared is as seperate function and used it in other methods
            case '@':                                       //it basically occurs when player change its position
                set_position(' ');                          //depending on the situation it will either be '@' or '+'
                break;
            case '+':
                set_position('.');
                break;
            }
}






bool Sokoban::move_up(void){
    bool b1,b2,b3,b4,b5,b6;                                      //boolean check for up side is available for movement.
    b1=up_control()=='#';
    b2=up_control()=='$';
    b3=up_control()=='*';
    b4=double_up_control()=='#';
    b5=double_up_control()=='$';
    b6=double_up_control()=='*';

    if(b1|(b2&(b4|b5|b6))|(b3&(b4|b5|b6)))
        return false;

    else{                                                       //if it is available, firstly it controls the 1 step up

        switch(up_control()){

    case ' ':
        set_up('@');                                            //i used switch case for checkng and doing operations.
            leaving_position();
        break;

                                                                //some movements does not concern 2 step up.
    case '$':
        set_up('@');
            switch(double_up_control()){                        //if they concerns like pushing box,
            case ' ':                                           //i used another switch case for 2 step up control
                set_double_up('$');
                    leaving_position();
                break;

            case '.':
                set_double_up('*');
                    leaving_position();
                break;
            }
        break;


    case '.':
        set_up('+');
            leaving_position();
        break;

    case '*':
        set_up('+');
            switch(double_up_control()){
            case ' ':
                set_double_up('$');
                    leaving_position();
                break;

            case '.':
                set_double_up('*');
                    leaving_position();
                break;
            }
        break;
    }

        y_of_player--;                                   //lastly i moved up(y-- is due to array decleration as i explained)
        is_solved();                                     //and check if it is solved then return true due to boolean method
        return true;
   }
}

bool Sokoban::move_down(void){                          //same algorithm with move up
    bool b1,b2,b3,b4,b5,b6;
    b1=down_control()=='#';
    b2=down_control()=='$';
    b3=down_control()=='*';
    b4=double_down_control()=='#';
    b5=double_down_control()=='$';
    b6=double_down_control()=='*';

    if(b1|(b2&(b4|b5|b6))|(b3&(b4|b5|b6)))
        return false;

    else{

        switch(down_control()){

    case ' ':
        set_down('@');
            leaving_position();
        break;


    case '$':
        set_down('@');
            switch(double_down_control()){
            case ' ':
                set_double_down('$');
                    leaving_position();
                break;

            case '.':
                set_double_down('*');
                    leaving_position();

                break;
            }
        break;


    case '.':
        set_down('+');
            leaving_position();
        break;

    case '*':
        set_down('+');
            switch(double_down_control()){
            case ' ':
                set_double_down('$');
                    leaving_position();
                break;

            case '.':
                set_double_down('*');
                    leaving_position();

                break;
            }
        break;
    }

        y_of_player++;
        is_solved();
        return true;
   }
}

bool Sokoban::move_left(void){                          //same algorithm with move up
    bool b1,b2,b3,b4,b5,b6;
    b1=left_control()=='#';
    b2=left_control()=='$';
    b3=left_control()=='*';
    b4=double_left_control()=='#';
    b5=double_left_control()=='$';
    b6=double_left_control()=='*';

    if(b1|(b2&(b4|b5|b6))|(b3&(b4|b5|b6)))
        return false;

    else{

        switch(left_control()){

    case ' ':
        set_left('@');
            leaving_position();
        break;


    case '$':
        set_left('@');
            switch(double_left_control()){
            case ' ':
                set_double_left('$');
                    leaving_position();
                break;

            case '.':
                set_double_left('*');
                    leaving_position();

                break;
            }
        break;


    case '.':
        set_left('+');
            leaving_position();
        break;

    case '*':
        set_left('+');
            switch(double_left_control()){
            case ' ':
                set_double_left('$');
                    leaving_position();
                break;

            case '.':
                set_double_left('*');
                    leaving_position();

                break;
            }
        break;
    }

        x_of_player--;
        is_solved();
        return true;
   }
}

bool Sokoban::move_right(void){                                 //same algorithm with move up
    bool b1,b2,b3,b4,b5,b6;
    b1=right_control()=='#';
    b2=right_control()=='$';
    b3=right_control()=='*';
    b4=double_right_control()=='#';
    b5=double_right_control()=='$';
    b6=double_right_control()=='*';

    if(b1|(b2&(b4|b5|b6))|(b3&(b4|b5|b6)))
        return false;

    else{

        switch(right_control()){

    case ' ':
        set_right('@');
            leaving_position();
        break;


    case '$':
        set_right('@');
            switch(double_right_control()){
            case ' ':
                set_double_right('$');
                    leaving_position();
                break;

            case '.':
                set_double_right('*');
                    leaving_position();

                break;
            }
        break;


    case '.':
        set_right('+');
            leaving_position();
        break;

    case '*':
        set_right('+');
            switch(double_right_control()){
            case ' ':
                set_double_right('$');
                    leaving_position();
                break;

            case '.':
                set_double_right('*');
                    leaving_position();

                break;
            }
        break;
    }

        x_of_player++;
        return true;
   }
}



bool Sokoban::is_solved(void)const{                 //If there is a moveable box (not in target location)
                                                    //that means puzzle is not solved.if not,then puzzle is solved.
    for(int i=0;i<6;i++){
        for(int j=0;j<8;j++){
            if(gamemap[i][j]=='$')
                return false;
        }
    }
    return true;
}



void Sokoban::print_puzzle(void)const{                //prints the chars of gamemap 2d array.
    for(int i=0;i<6;i++){
        for(int j=0;j<8;j++){
            cout<<gamemap[i][j];
        }
        cout<<endl;
    }
}









template <class T>
StackQueue<T>::StackQueue(void): f(0),r(0),c(0) {}              //constructor

template <class T>
int StackQueue<T>::StackQueue_length(void)const{                //c is for count
    return c;
}

template <class T>
void StackQueue<T>::push_front(const T& item){                  //if stackqueue is not full then i increased c,
    if(stack_queue_full()){                                     //assigned item to front,
        cerr<<"StackQueue list is full!"<<endl;                 //increased front
        exit(1);                                                //(f+1)% is for circular stackqueue
    }
    c++;
    StackQueue_list[f]=item;
    f=(f+1)%Max_member;
}

template <class T>
T StackQueue<T>::pop_front(void){                           //simply popped last element in list
    if(stack_queue_empty()){
        cerr<<"StackQueue list is empty!"<<endl;
        exit(1);
    }
    c--;
    f=(f-1)%Max_member;
    return StackQueue_list[f];
}

template <class T>
T StackQueue<T>::pop_rear(void){                            //popped from rear,i used temporary variable to return
    if(stack_queue_empty()){                                // beacuse i need to increment it also before returning.
        cerr<<"StackQueue list is empty!"<<endl;
        exit(1);
    }
    c--;
    T temp;
    temp=StackQueue_list[r];
    r=(r+1)%Max_member;
    return temp;
}

template <class T>
T StackQueue<T>::peek_front(void)const{                 //shows what there is at front without deleting it
    if(stack_queue_empty()){
        cerr<<"StackQueue list is empty!"<<endl;
        exit(1);
    }
    int temp;
    temp=f-1;
    return StackQueue_list[temp];
}

template <class T>
int StackQueue<T>::stack_queue_full(void)const{         //checks number of c if it is max array size
    return c==Max_member;
}

template <class T>
int StackQueue<T>::stack_queue_empty(void)const{        //checks number of c if it is 0
    return c==0;
}






template <class T>                                     //constructor
Node<T>::Node(void){                                   //i assigned null values to members as default
    data=NULL;
    next=NULL;
    prev=NULL;
}

template <class T>                                     //another constructor
Node<T>::Node(const T& item){                          //i generally used this in methods to assign some value to data in node.
    data=item;
    next=NULL;
    prev=NULL;
}







template <class T>
DoublyLinkedList<T>::DoublyLinkedList(void){        //linked list constructor,head is null as default
    head=NULL;
}

template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const T& item){       //other cons. i used this generally.Firstly i created a node with
    head=GetNode(item);
    delete GetNode(item);                              //GetNode. return type of this method is a pointer. I assigned this
}                                                           //pointer to head. So,head points the created node element.

template <class T>
void DoublyLinkedList<T>::dinsert(const T& item){           //insertion method for doub.link.list
                                                            //firstly i created a temporary pointer then assigned it to head.
    Node<T>* newptr=GetNode(item);                          //if head is null that means it will be our first node.
                                                            //if not, i reached the end of this doub.link.list using temp ptr
    if(head==NULL)                                          //i simply nexted to reach null char.
        head=newptr;                                        // then i added newnode which holds 'item' data in it.
    else{
        Node<T>* tempptr=head;
        while(tempptr->next!=NULL){
            tempptr=tempptr->next;
        }
        tempptr->next=newptr;
        newptr->prev=tempptr;
    }
}
template <class T>
T DoublyLinkedList<T>::ddelete(void){                       //same with inseriton up to reaching last node.
    Node<T>* tempptr;                                       //after i reached the last node.
    tempptr=head;                                           //i modified the connections(pointers)
    while(tempptr->next!=NULL){                             //so that this node will be seperated from list.
        tempptr=tempptr->next;                              //similar to pop_front.
    }
    tempptr->prev->next=NULL;
    return tempptr->data;
}

template <class T>
T DoublyLinkedList<T>::headup(void){                    //similar to pop rear.i modified head value.it points the next node now
    T element=head->data;                               //and im returning the old head's pointed data value.
    head=head->next;
    return element;
}

template <class T>                                      //similar to frontpeek.It returns the data of last node without
T DoublyLinkedList<T>::showlast(void)const{             //deleting it.i reached at the end of node with using temporary pointer
    Node<T>* tempptr;                                   //when i reached,i red the data from there.
    tempptr=head;
    while(tempptr->next!=NULL){
        tempptr=tempptr->next;
    }
    return tempptr->data;
}

template <class T>
int DoublyLinkedList<T>::LinkedListLength(void)const{           //similar to stackqueue legth.
    Node<T>* tempptr;                                           //i incremented an integer value every time i went to next node
    tempptr=head;                                               //i stopped when i reached null character
    int i;                                                      //i returned that integer value.
    for(i=0;tempptr!=NULL;tempptr=tempptr->next,i++){}
    return i;
}

template <class T>
Node<T>::~Node(void){
    delete this->next;
}

template <class T>

DoublyLinkedList<T>::~DoublyLinkedList(void){
    delete  head;
}
