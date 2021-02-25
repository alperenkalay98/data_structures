#include <iostream>
#include <fstream>

using namespace std;

class HashNode{                 //Linkedlist nodes. Holds pointer to next node and holds ID number
private:
    long long int value;
    HashNode* next;
public:
    HashNode(const long long int &hashvalue,HashNode* ptrnext); //constructor
    HashNode* GetNext(void);                                    //returns pointer next node
    void SetNext(HashNode* nextptr);                            //Set next node
    long long int GetValue(void);                               //returns ID number
};

HashNode* CreateHashNode(const long long int &item,HashNode* nextptr=NULL){ //It is for creating new node
    HashNode* newhashnode=new HashNode(item,nextptr);                       //Dynamically allocated memory,
    return newhashnode;                                                     //i will delete later.
}

class HashTable{        //Hash table class,private member is pointer to pointer to hash node.
private:
    HashNode** table;
public:
    HashTable(const int n); //constructor
    void AddID(int function_number,long long int TC_number,int table_size); //Add ID to hash table
    void DeleteID(int function_number,long long int TC_number,int table_size); //Delete ID from hash table
    int SearchID(int function_number,long long int TC_number,int table_size);   //Search for ID in hash table
    HashNode** GetTable(void);                                                  //returns table
};

int HashFunctions(int function_number,long long int TC_number,int table_size){ //hash function implementation
    switch(function_number){
        int t,temp1,temp2,temp3,temp4;
    case 1:                                     //folding
        temp1=TC_number/100000000;
        temp2=(TC_number/100000)%1000;
        temp3=(TC_number/100)%1000;
        temp4=TC_number%100;
        t=temp1+temp2+temp3+temp4;
        return t%table_size;
    case 2 :                                    //middle squaring
        t=(TC_number/10000)%1000;
        t=t*t;
        return t%table_size;
    case 3:                                     //truncation
        t=TC_number%100;
        return t%table_size;
    default:
        return -1;
    }
}

int menu(void){         //Menu interface,returns the input from user
    int operation;
    cout<<endl;
    cout<<"What operation do you want to do?"<<endl;
    cout<<endl;
    cout<<"1. Initialize Hash Table"<<endl;
    cout<<"2. Load T.C. ID Numbers from file"<<endl;
    cout<<"3. Add new T.C. ID Number"<<endl;
    cout<<"4. Delete a T.C. ID Number"<<endl;
    cout<<"5. Search for a T.C. ID Number"<<endl;
    cout<<"6. Print out Hash Table"<<endl;
    cout<<"7. Finish and Clear program"<<endl;  //I added this operation to clear dynamically allocated memory
    cin>>operation;
    cout<<endl;
    if(operation>7 ||operation<1){
        cout<<"There is no such operation"<<endl;
        return -1;
    }
    return operation;
}


int main()
{       //I used if else structure below,i considered to use switch, but variables cant be created in case blocks.
    int op=menu();
    if(op!=1){                                         //table should be initialized first
        cout<<"Initialization must be done first!"<<endl;
    }
    else{                                           //operation 1
        int table_size,hash_function;
        cout<<"What is table size?"<<endl;
        cin>>table_size;
        cout<<"What is hash function"<<endl;
        cout<<"1 for folding"<<endl;
        cout<<"2 for middle squaring"<<endl;
        cout<<"3 for truncation"<<endl;
        cin>>hash_function;
        if(hash_function<1||hash_function>3){
            cout<<"There is no such hash function"<<endl;
            exit(0);
        }
        HashTable ID(table_size);
        while(1){                           //operations other than 1,in infinite while loop
            int operation=menu();
            if (operation==1){
                cout<<"Hash table is already initialized!"<<endl;
            }
            else if(operation==2){              //read form text file
                long long int IDnumbers[200];
                ifstream myfile("hash_table_init200.txt");
                int c=0;
                long long int x;
                while(c<200&&myfile>>x)
                    IDnumbers[c++]=x;

                for(int i=0;i<200;i++){
                    ID.AddID(hash_function,IDnumbers[i],table_size);    //adds ID numbers in text to hash table
                }
                cout<<"Loaded from file"<<endl;
            }
            else if(operation==3){                              //add selected ID to hash table
                long long int willadd;
                cout<<endl;
                cout<<"TC number to be inserted?"<<endl;
                cin>>willadd;
                ID.AddID(hash_function,willadd,table_size);
            }
            else if(operation==4){                              //delete selected ID from hash table
                long long int willdel;
                cout<<endl;
                cout<<"TC number to be deleted?"<<endl;
                cin>>willdel;
                ID.DeleteID(hash_function,willdel,table_size);
            }
            else if(operation==5){                              //search for selected ID in hash table
                long long int willsearch;
                cout<<endl;
                cout<<"TC number to be searched?"<<endl;
                cin>>willsearch;
                if(ID.SearchID(hash_function,willsearch,table_size)==1)
                    cout<<willsearch<<" is in the table"<<endl;
                else
                    cout<<willsearch<<" is not in the table"<<endl;
            }
            else if(operation==6){                          //Prints hash table
                for(int i=0;i<table_size;i++){
                    if(ID.GetTable()[i]==NULL)
                        cout<<'E'<<endl;
                    else
                        cout<<ID.GetTable()[i]->GetValue()<<endl;
                }
            }
            else if(operation==7){                      //Clears dynamically allocated memory
                for(int i=0;i<table_size;i++){
                    if(ID.GetTable()[i]!=NULL){
                        HashNode* prevptr=NULL;
                        HashNode* ptr=ID.GetTable()[i];
                        while(ptr!=NULL){
                            prevptr=ptr;
                            ptr=ptr->GetNext();
                            delete prevptr;
                        }
                    }
                }
                delete[] ID.GetTable();
                break;
            }

        }
    }

    return 0;
}


HashNode::HashNode(const long long int &hashvalue,HashNode* ptrnext){
    value=hashvalue;
    next=ptrnext;
}

HashNode* HashNode::GetNext(void){
    return next;
}

void HashNode::SetNext(HashNode* nextptr){
    next=nextptr;
}

long long int HashNode::GetValue(void){
    return value;
}


HashTable::HashTable(const int n){    //creates n buckets for hash table,each bucket points to a hash node
    table=new HashNode* [n];
    for(int i=0;i<n;i++){
        table[i]=NULL;
    }
}


int HashTable::SearchID(int function_number,long long int TC_number,int table_size){

//returns 1 if ID is found,returns 0 if not
    int hashvalue=HashFunctions(function_number,TC_number,table_size);

    if(table[hashvalue]!=NULL){
        HashNode* ptr=table[hashvalue];
        while(ptr!=NULL){
            if(ptr->GetValue()==TC_number){
                return 1;
            }
            ptr=ptr->GetNext();
        }
    }
    return 0;
}

void HashTable::DeleteID(int function_number,long long int TC_number,int table_size){

//After finding related bucket according to hash function
//Basically i am setting next pointer of previous node to next of current node.Then deleting current node.
    int hashvalue=HashFunctions(function_number,TC_number,table_size);

    if(table[hashvalue]!=NULL){
        HashNode* ptr=table[hashvalue];
            if(ptr->GetValue()==TC_number){
                table[hashvalue]=ptr->GetNext();
                delete ptr;
                return;
            }
            else{
                while(ptr->GetNext()!=NULL){
                    if(ptr->GetNext()->GetValue()==TC_number){
                        HashNode* temp=ptr->GetNext();
                        ptr->SetNext(temp->GetNext());
                        delete temp;
                        return;
                    }
                    ptr=ptr->GetNext();
                }
            }
    }
    return;
}

void HashTable::AddID(int function_number,long long int TC_number,int table_size){

//After finding related bucket according to hash function
//I go until i reach a node which has next pointer to null,then add a node to end.
    if(SearchID(function_number,TC_number,table_size)==1){
        cout<<"Already Added"<<endl;
        return;
    }

    int hashvalue=HashFunctions(function_number,TC_number,table_size);

    if(table[hashvalue]==NULL)
        table[hashvalue]=CreateHashNode(TC_number);
    else{
        HashNode* ptr=table[hashvalue];
        while(ptr->GetNext()!=NULL)
            ptr=ptr->GetNext();

        ptr->SetNext(CreateHashNode(TC_number));
    }
}

HashNode** HashTable::GetTable(void){
    return table;
}
