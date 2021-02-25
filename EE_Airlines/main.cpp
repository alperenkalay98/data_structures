
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <fstream>
                                                //I added cstdlib and time for rand and srand functions
using namespace std;

class Graph{                                    //Graph class
private:
    int adj_matrix[20][20];                     //I used adjacency matrix. Matrix values are route fares.
public:
    string city[20];                            //I read city names in citylist.txt file into this array
    string available_cities[20];                //If a city(node) is connected, i stored it in this string
    Graph(void);                                //Constructor
    ~Graph(void);                               //Destructor

    void addgcity(string c);                    //add corresponding city to available cities array
    void removegcity(string c);                 //remove corresponding city from available cities array
    int searchgcity(string c);                  //search for a string and returns its city code if available
    void addgroute(int c1,int c2);              //set a value in related place in adjacency matrix -> adj[c1][c2]
    void removegroute(int c1,int c2);           //set 0 adj[c1][c2]
    int searchgroute(int c1,int c2);            //search in adjacency matrix and returns fare of that route
    void listgroutes(void);                     //prints routes
    void routediscount(int c1,int c2);          //fare value is decremented
};                                              //I will explain this methods in more detailed way below

class Flight{                                   //Binary Search Tree
private:
    int occupancyrate;                          //occupancy rate,flightnumber and unpopularity are my variables,
public:                                         //occupancy rate is private others are public which i can reach directly
    Flight* left;
    Flight* right;
    int flightnumber;
    int unpopularity;
    Flight(const int& c1,const int& c2,Flight* lptr=NULL,Flight* rptr=NULL);        //Constructor
    void setoccupancyrate(void);                //Set and get methods to reach and change occupancy rate
    int getoccupancyrate(void)const;
    ~Flight(void);                              //Destructor
};



void initroutemap(Graph& obj){                  //Global function to initialize graph
    obj.addgcity("Logicheim");                  //add cities to available cities array
    obj.addgcity("Probia");
    obj.addgcity("Gulf of Archi");
    obj.addgcity("Signale");
    obj.addgcity("Las Datas");
    obj.addgroute(obj.searchgcity("Logicheim"),obj.searchgcity("Probia"));          //I searched city for its city code and
    obj.addgroute(obj.searchgcity("Probia"),obj.searchgcity("Gulf of Archi"));      //used it to create route,basically
    obj.addgroute(obj.searchgcity("Probia"),obj.searchgcity("Logicheim"));          //setting a value at that location in
    obj.addgroute(obj.searchgcity("Gulf of Archi"),obj.searchgcity("Logicheim"));   //adj matrix.
    obj.addgroute(obj.searchgcity("Signale"),obj.searchgcity("Probia"));
    obj.addgroute(obj.searchgcity("Probia"),obj.searchgcity("Las Datas"));
}



Flight* create(int c1,int c2,Flight* lptr=NULL,Flight* rptr=NULL){         //Global function to create node for BST
    Flight* temp;
    temp=new Flight(c1,c2,lptr,rptr);                    //Memory allocated for new node
    if(temp==NULL){
        cout<<"mem. all. fail"<<endl;
        exit(1);
    }
    return temp;                                          //returns a pointer which points to this new node
}

void addtflight(Flight* &root,int c1,int c2){           //Global function to add flight,basically adds newly created node
    if(root==NULL){                                     //to BST
        root=create(c1,c2);                             //after recursively searching and going correct place,newly created
        return;                                         //node is connected to BST
    }
    else if(root->flightnumber > (c1*100+c2))           //Recursively search tree,flightnumber of leftmost node of bst is
        addtflight(root->left,c1,c2);                   //lowest, similarly flightnumber of rightmost node of tree is highest
    else if(root->flightnumber < (c1*100+c2))
        addtflight(root->right,c1,c2);
}

Flight* searchtflight(Flight* root,int c1,int c2){      //Global function to search flight,recursively searches BST and
    if(root==NULL)                                      //returns a pointer if flightnumber of that pointer
        return NULL;                                    //matches with c1*100+c2
    else{
        if(root->flightnumber==(c1*100+c2)){
            return root;
        }
        else{
            if(root->flightnumber>(c1*100+c2)){
                searchtflight(root->left,c1,c2);
            }
            else{
                searchtflight(root->right,c1,c2);
            }
        }
    }
}

Flight* minimumfno(Flight* curr){               //Search for minimum number for flight number,basically leftmost node.
    while (curr->left != NULL) {                //I will use this function when i remove a flight, i will change that node
        curr = curr->left;                      //with leftmost node of its right side.
    }
    return curr;
}

void setparent(Flight*& item, int fno, Flight*& parent){       //This funciton is also for removing a flight
    while (item!= NULL && item->flightnumber!=fno)             //I will use it to define parent node of a node which
    {                                                          //will be removed.
        parent=item;
        if (fno<item->flightnumber)
            item=item->left;
        else
            item= item->right;
    }
}

void removetflight(Flight*& root, int c1,int c2){          //Global func to remove a flight
    Flight* parent = NULL;
    Flight* curr = root;

    setparent(curr,(c1*100+c2),parent);                 //set parent node for node which will be removed

    if (curr==NULL)
        return;

    if (curr->left==NULL && curr->right==NULL)         //if there is no child node
    {
        if (curr!=root)
        {
            if (parent->left==curr)
                parent->left = NULL;
            else
                parent->right = NULL;
        }
        else
            root = NULL;

        free(curr);
    }


    else if (curr->left && curr->right)                 //if there is two child of that node
    {
        Flight* successor=minimumfno(curr->right);
        int val=successor->flightnumber;
        removetflight(root,(successor->flightnumber/100),(successor->flightnumber%100));
        curr->flightnumber=val;
    }

    else                                                //if there is one child of that node
    {
        Flight* child = (curr->left)? curr->left: curr->right;
        if (curr!=root)
        {
            if (curr==parent->left)
                parent->left=child;
            else
                parent->right=child;
        }

        else
            root=child;
        free(curr);
    }
}



string flightnumber_to_flightname(int fno){             //I used this function to print in desired way from flight number.
    int w,x,y,z;                                        // 304 to EE0304
    w=fno/1000;
    x=(fno/100)%10;
    y=(fno%100)/10;
    z=fno%10;
    char flightname[6];
    flightname[0]=flightname[1]='E';
    flightname[2]=w+'0';
    flightname[3]=x+'0';
    flightname[4]=y+'0';
    flightname[5]=z+'0';
    return flightname;
}

void printInorder(Flight* node){                       //Prints flights numbers in Inorder way
    if (node == NULL)
        return;
    printInorder(node->left);
    cout <<flightnumber_to_flightname(node->flightnumber)<<endl;
    printInorder(node->right);
}

void printflights(Flight* node){                    //Prints all flights in one block,works with printinorder function
    cout<<"Flights:"<<endl;
    printInorder(node);
    cout<<endl;
}

void initflightplan(Graph& obj1,Flight* &obj2){        //Similar to initroute map,initialize flights
    initroutemap(obj1);
    obj2=NULL;
    addtflight(obj2,obj1.searchgcity("Logicheim")+1,obj1.searchgcity("Probia")+1);      //+1 s are for flight numbers
    addtflight(obj2,obj1.searchgcity("Probia")+1,obj1.searchgcity("Gulf of Archi")+1);  //For example, probia is city[0]
    addtflight(obj2,obj1.searchgcity("Probia")+1,obj1.searchgcity("Logicheim")+1);      //but it is 01 in flights.
    addtflight(obj2,obj1.searchgcity("Gulf of Archi")+1,obj1.searchgcity("Logicheim")+1);
    addtflight(obj2,obj1.searchgcity("Signale")+1,obj1.searchgcity("Probia")+1);
    addtflight(obj2,obj1.searchgcity("Probia")+1,obj1.searchgcity("Las Datas")+1);
}



int* addmonthlynewroutes(Graph& obj,int n){        //Global function to add new routes
    srand(time(0));                                //srand for producing different combinations
    int* newly= new int[n];                         //memory is allocated to hold newly added routes
    int j,k;
    cout<<"Newly Added Routes:"<<endl;
    for(int i=0;i<n;){
        j=rand()%20;                                //Since we have 20 cities j,k are randomly selected from this 20.
        k=rand()%20;
        if(j!=k&&obj.searchgroute(j,k)==0){         //checks if j is different from k and route from j to k does not exist
            obj.addgroute(j,k);                     //then creates route
            *(newly+i)=(j+1)*100+(k+1);             //+1 is because of same reason i mentioned before.Related flight code is
                                                    // 1 more than city code.
            cout<<obj.city[j]<<" --> "<<obj.city[k]<<" ,fare:"<<obj.searchgroute(j,k)<<"\n";
            i++;                                       //I print route and related value in that cell(fare) and increment i.
            if(obj.available_cities[j]!=obj.city[j])        //I added cities to available cities array if they
            obj.addgcity(obj.city[j]);                      //are introduced new.
            if(obj.available_cities[k]!=obj.city[k])
            obj.addgcity(obj.city[k]);
        }
    }
    cout<<endl;
    return newly;       //returns array of newly added routes
}

void addmonthlynewflights(Flight* root,int* nrt,int n){     //works with addmonthlynewroutes function
    int j,k;
    cout<<"Newly Added Flights:"<<endl;
    for(int i=0;i<n;i++){                   //Prints all flights in newly added routes array
        j=(*(nrt+i))/100;
        k=(*(nrt+i))%100;
        addtflight(root,j,k);
        cout<<"Flight "<<flightnumber_to_flightname(j*100+k)<<" Added"<<endl;
    }
    delete[] nrt;
    cout<<endl;
}



void collectfeedbackfrompassengers(Flight*& item,const int OT){ //I used this function to define unpopularity of that flight
    if(item==NULL)
        return;
    else{
        collectfeedbackfrompassengers(item->left,OT);          //recursively searching all flights and assigns a value
        collectfeedbackfrompassengers(item->right,OT);          //to unpopularity of that flight.If that flight's occupancy rate
        item->setoccupancyrate();                               //is below than treshold value,i am incrementing unpopularity of
        if(item->getoccupancyrate()>OT){                        //that flight.
            item->unpopularity=0;
        }
        else{
            item->unpopularity++;
        }
    }
}

void seeunpop(Flight*& item){           //This function is not necessary, i just used it too see unpopularities of flights
    if(item!=NULL){
        seeunpop(item->left);
        seeunpop(item->right);
        cout<<item->flightnumber<<endl;
        cout<<item->unpopularity<<endl;
    }
}

int* cancelunpopularflights(Flight*& item,const int OT){
    int  k=0;
    int  s=0;
    for(int i=1;i<21;i++){                                  //Firstly i searched to detect how many flights will be cancelled
        for(int j=1;j<21;j++){                              //or discounted
            if(searchtflight(item,i,j)!=NULL){
                if(searchtflight(item,i,j)->unpopularity!=0){
                    k++;                                        //k is the number for cancelled or discounted flights
                }
                if(searchtflight(item,i,j)->unpopularity==2){   //I will seperately store flights which will be deleted,i will
                    s++;                                        //explain why i did this
                }
            }
        }
    }
    if(k==0)
        return NULL;

    int* unpops=new int[k+1];   //memory is allocated to hold unpopular flights,+1 is for putting null value
                                //later i will read this array up to this null
    int* willbedeleted=new int[s];      //memory is allocated to hold flights which will be deleted

    int t=0;
    int m=0;
    cout<<"Cancelled Flights:"<<endl;
    for(int i=1;i<21;i++){
        for(int j=1;j<21;j++){
            if(searchtflight(item,i,j)!=NULL){
                if(searchtflight(item,i,j)->unpopularity!=0){       //if its unpopularity 1 or 2 (there can't be more)
                    *(unpops+t)=searchtflight(item,i,j)->flightnumber; //add that flight to unpops array
                    t++;
                    if(searchtflight(item,i,j)->unpopularity==2){   //if unpopularity is 2,delete that flight also.
                        cout<<"Flight "<<flightnumber_to_flightname(i*100+j)<<" Cancelled"<<endl;
                        *(willbedeleted+m)=searchtflight(item,i,j)->flightnumber;
                        m++;
                        //This part is a bit critical. I used to remove flights in here. However, this caused deleting newly added
                        //flights too.Therefore i decided to create an array and store the flight numbers which will be deleted,then remove
                        //them at outside the iteration.
                    }
                }
            }
        }
    }
    *(unpops+t)=NULL;

    for(int b=0;b<m;b++){
            removetflight(item,*(willbedeleted+b)/100,*(willbedeleted+b)%100);  //I removed flights in willbedeleted array.
    }
    if(m==0)
        cout<<"No Cancelled Flights"<<endl;
    delete willbedeleted;
    cout<<endl;
    return unpops;          //returns stored flights in unpops
}

void discardunpopularflights(Graph& obj,Flight*& item,int* unpops){     //works with cancelunpopularflights function
    cout<<"Discarded Routes & Routes on Discount:"<<endl;
    for(int i=0;*(unpops+i)!=NULL;i++){                             //works up to reaching null in stored flights array
        if(searchtflight(item,*(unpops+i)/100,*(unpops+i)%100)==NULL){ //if that flight is deleted also delete route
            int w=*(unpops+i)/100;
            int z=*(unpops+i)%100;
            obj.removegroute(w-1,z-1);
            cout<<obj.city[w-1]<<" --> "<<obj.city[z-1]<<" Route Discarded"<<endl;
        }
        else if(searchtflight(item,*(unpops+i)/100,*(unpops+i)%100)->unpopularity==1){     //if that flight is not deleted
            int w=*(unpops+i)/100;                                                          //make a discount
            int z=*(unpops+i)%100;
            obj.routediscount(w-1,z-1);
            cout<<obj.city[w-1]<<" --> "<<obj.city[z-1]<<" ,fare:"<<obj.searchgroute(w-1,z-1)<<" is 50% Off!"<<endl;
        }
    }
    delete[] unpops;
    cout<<endl;
}



int* checknaddreturnroutes(Graph& obj){
    int k=0;
    for(int i=0;i<20;i++){                          //Detecting how many missing route there are
        for(int j=0;j<20;j++){
            if(obj.searchgroute(i,j)!=0){
                if(obj.searchgroute(j,i)==0){
                    k++;
                }
            }
        }
    }
    int* missingroutes=new int[k+1];
    int t=0;
    cout<<"Missing Return Routes"<<endl;
    for(int i=0;i<20;i++){                          //storing that routes and adding that routes
        for(int j=0;j<20;j++){
            if(obj.searchgroute(i,j)!=0){
                if(obj.searchgroute(j,i)==0){
                    obj.addgroute(j,i);
                    *(missingroutes+t)=(j+1)*100+(i+1);
                    t++;
                    cout<<obj.city[j]<<" --> "<<obj.city[i]<<" Return Route Added"<<endl;
                }
            }
        }
    }
    *(missingroutes+t)=NULL;
    cout<<endl;
    return missingroutes;
}

void addreturnflights(Flight*& item,int* missingflightnos){ //adds missing flights according to array in upper part
    cout<<"Missing Return Flights"<<endl;
    for(int i=0;*(missingflightnos+i)!=NULL;i++){
        addtflight(item,*(missingflightnos+i)/100,*(missingflightnos+i)%100);
        cout<<"Flight "<<flightnumber_to_flightname(*(missingflightnos+i))<<" Added"<<endl;
    }
    delete[] missingflightnos;
    cout<<endl;
}

bool displayrouteoptions(Graph& obj1,Flight*& obj2,string c1,string c2){       //DFT or BFT could be used in here but since
    cout<<"One Way Trip Options For "<<c1<<" --> "<<c2<<" :"<<endl;             //there is up to 2 stop i searched adj matrix.
        int temp=0;
        int c1no=obj1.searchgcity(c1);
        int c2no=obj1.searchgcity(c2);
                                                //If value of that place in adj matrix is not 0,that means there exist a
            if(obj1.searchgroute(c1no,c2no)!=0){    //direct route
                cout<<"Direct Option: "<<c1<<" --> "<<flightnumber_to_flightname(searchtflight(obj2,c1no+1,c2no+1)->flightnumber)
                <<" --> "<<c2<<" --> "<<" Fee: "<<obj1.searchgroute(c1no,c2no)<<endl;
                temp++;
            }

                                        //Go from end city to one city that is connected to starting city.if there is,
            for(int i=0;i<20;i++){      //one stop is satisfied.
                if(obj1.searchgroute(i,c2no)!=0&&obj1.searchgroute(c1no,i)!=0){
                    cout<<"1-Stop Option: "<<c1<<" --> "<<flightnumber_to_flightname(searchtflight(obj2,c1no+1,i+1)->flightnumber)
                    <<" --> "<<obj1.city[i]<<" --> "<<flightnumber_to_flightname(searchtflight(obj2,i+1,c2no+1)->flightnumber)
                    <<" --> "<<c2<<" Fee: "<<obj1.searchgroute(c1no,i)+obj1.searchgroute(i,c2no)<<endl;
                    temp++;
                }                       //Go from end city to one city that is also connected to a city which is connected
                for(int j=0;j<20;j++){  //to starting city.if there is,two stop is satisfied.
                    if(obj1.searchgroute(c1no,i)!=0&&obj1.searchgroute(i,j)!=0&&obj1.searchgroute(j,c2no)!=0){
                        cout<<"2-Stop Option: "<<c1<<" --> "<<flightnumber_to_flightname(searchtflight(obj2,c1no+1,i+1)->flightnumber)
                        <<" --> "<<obj1.city[i]<<" --> "<<flightnumber_to_flightname(searchtflight(obj2,i+1,j+1)->flightnumber)
                        <<" --> "<<obj1.city[j]<<" --> "<<flightnumber_to_flightname(searchtflight(obj2,j+1,c2no+1)->flightnumber)
                        <<" --> "<<c2<<" Fee: "<<obj1.searchgroute(c1no,i)+obj1.searchgroute(i,j)+obj1.searchgroute(j,c2no)<<endl;
                        temp++;
                    }
                }
            }
            if(temp==0){
                cout<<"No Trip Options"<<endl;
                cout<<endl;
                return false;
            }
            else
                cout<<endl;
                return true;

}



int main()
{                               //I used all this functions to create similar window with example run pa2.
    srand(time(0));
    Graph EEland;
    Flight* EEAirlines;
    int OT=70;
    int n=5;

    cout<<"----------------Month 1------------------:"<<endl;
    initroutemap(EEland);
    initflightplan(EEland,EEAirlines);
    EEland.listgroutes();
    printflights(EEAirlines);
    cout<<endl;

    cout<<"----------------Month 2------------------:"<<endl;
    collectfeedbackfrompassengers(EEAirlines,OT);                      //I collected feedbacks for previous months flights
    addmonthlynewflights(EEAirlines,addmonthlynewroutes(EEland,n),n);
    EEland.listgroutes();
    printflights(EEAirlines);
    cout<<endl;

    cout<<"----------------Month 3------------------:"<<endl;
    collectfeedbackfrompassengers(EEAirlines,OT);
    addmonthlynewflights(EEAirlines,addmonthlynewroutes(EEland,n),n);
    discardunpopularflights(EEland,EEAirlines,cancelunpopularflights(EEAirlines,OT));
    EEland.listgroutes();
    printflights(EEAirlines);
    cout<<endl;

    cout<<"----------------Month 4------------------:"<<endl;
    collectfeedbackfrompassengers(EEAirlines,OT);
    addmonthlynewflights(EEAirlines,addmonthlynewroutes(EEland,n),n);
    discardunpopularflights(EEland,EEAirlines,cancelunpopularflights(EEAirlines,OT));
    EEland.listgroutes();
    printflights(EEAirlines);
    cout<<endl;

    cout<<"----------------Month 5------------------:"<<endl;
    collectfeedbackfrompassengers(EEAirlines,OT);
    addmonthlynewflights(EEAirlines,addmonthlynewroutes(EEland,n),n);
    discardunpopularflights(EEland,EEAirlines,cancelunpopularflights(EEAirlines,OT));
    EEland.listgroutes();
    printflights(EEAirlines);
    cout<<endl;

    cout<<"----------------Month 6------------------:"<<endl;
    collectfeedbackfrompassengers(EEAirlines,OT);
    addmonthlynewflights(EEAirlines,addmonthlynewroutes(EEland,n),n);
    discardunpopularflights(EEland,EEAirlines,cancelunpopularflights(EEAirlines,OT));
    addreturnflights(EEAirlines,checknaddreturnroutes(EEland));
    EEland.listgroutes();
    printflights(EEAirlines);
    cout<<endl;


    cout<<"-----------------------------------------:"<<endl;           //This part can be changed,i randomly selected these
    displayrouteoptions(EEland,EEAirlines,"Las Datas","Logicheim");     //routes but it works for all of the routes if you
    displayrouteoptions(EEland,EEAirlines,"Analograd","Gulf of Archi"); //write city name correctly
    displayrouteoptions(EEland,EEAirlines,"Waverium","Analograd");
    cout<<endl;


    delete &EEland;             //I cleared graph and tree nodes for avoiding memory leakage.
    delete EEAirlines;
    return 0;
}


Graph::Graph(void){             //Constructor of graph

    for(int i=0;i<20;i++)               //I assigned 0 available cities
        available_cities[i]="\0";

    for(int i=0;i<20;i++)               //I assigned 0 to all fares initially
        for(int j=0;j<20;j++)
            adj_matrix[i][j]=0;


    string line;
    ifstream myfile ("citylist.txt");       //I red citylist.txt into city string array.
    if (myfile.is_open())
    {
    int i=0;
    while ( getline (myfile,line) )
    {
    city[i]=line;
    i++;
    }
    myfile.close();
    }
    else cout << "Unable to open file";
}

Graph::~Graph(void){                    //Destructor for graph
    for(int i=0;i<20;i++)
        delete[] adj_matrix[i];         //Firstly i am deleting matrix elements
    delete[] adj_matrix;                //then adj matrix,cities,and available cities.
    delete[] city;
    delete[] available_cities;
}


void Graph::addgcity(string c){         //add a city to available cities, corresponding to place in cities
    for(int i=0;i<20;i++)
        if(c==city[i])
            available_cities[i]=city[i];
}

void Graph::removegcity(string c){      //Remove city from available cities
    for(int i=0;i<20;i++)
        if(c==available_cities[i])
            available_cities[i]="\0";
}

int Graph::searchgcity(string c){       //Search for a city name and returns its city code if founded,otherwise returns -1
    for(int i=0;i<20;i++){
        if(c==available_cities[i])
            return i;
    }
    return -1;
}

void Graph::addgroute(int c1,int c2){       //Randomly assigns a number to fare
    adj_matrix[c1][c2]=rand()%100+1;
}

void Graph::removegroute(int c1,int c2){        //Set 0 of that matrix location
    adj_matrix[c1][c2]=0;
}

int Graph::searchgroute(int c1,int c2){         //search in adj matrix according to city codes,returns that locations value
    if(adj_matrix[c1][c2]!=0)                   //if it is not 0(fare)
        return adj_matrix[c1][c2];
    else{
        return 0;
    }
}

void Graph::listgroutes(void){                  //Prints routes.Basically prints matrix values which are not 0.
    cout<<"Routes:"<<endl;
    for(int i=0;i<20;i++)
        for(int j=0;j<20;j++)
            if(adj_matrix[i][j]!=0)
                cout<<city[i]<<" --> "<<city[j]<<" ,fare:"<<searchgroute(i,j)<<"\n";
    cout<<endl;
}

void Graph::routediscount(int c1,int c2){       //Divide the fare by 2 for 50% discount
    adj_matrix[c1][c2]=adj_matrix[c1][c2]/2;
}




Flight::Flight(const int& c1,const int& c2,Flight* lptr,Flight* rptr){  //Constructor for BST
    flightnumber=c1*100+c2;
    unpopularity=0;
    left=lptr;
    right=rptr;
}

void Flight::setoccupancyrate(void){                //Set occupancy rate between 50 and 100
    occupancyrate=rand()%50+50;
}

int Flight::getoccupancyrate(void)const{            //returns occupancy rate
    return occupancyrate;
}



Flight::~Flight(void){                              //Destructor for BST
    while(this!=NULL){
        delete this->left;
        delete this->right;
    }
}
