#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

int menu(void){                                         //menu interface
    cout<<"1. Initialize input array randomly"<<endl;
    cout<<"2. Load input array from a file"<<endl;
    cout<<"3. Perform Bubble Sort"<<endl;
    cout<<"4. Perform Quick Sort"<<endl;
    cout<<"5. Perform Selection Sort"<<endl;
    cout<<"6. Perform My Sort"<<endl;
    cout<<"7. Compare sorting algorithms"<<endl;
    cout<<"8. Delete and Finish"<<endl;                 //I added this to clear dynamically allocated memory
    cout<<"9. Performance Evaluation"<<endl;            //I added this for performance evaluation
    int operation;
    cin>>operation;
    cout<<endl;
    return operation;                               //I am reading and returning a user input for operation selection
}

int* init(int size_of_array){               //creates array with input size
    int* ptr=new int[size_of_array];
    for(int i=0;i<size_of_array;i++){
        *(ptr+i)=rand()%(10*size_of_array); //values are random between 0 and 10*size
    }
    return ptr;
}

void swapp(int &x,int &y){      //swap function, i will use it in sorting algorithms
    int temp;
    temp=x;
    x=y;
    y=temp;
}

int bubble(int arr[],int n){    //bubble sorting
    int i,j;
    int lastexc;
    int change_number=0;
    i=n-1;
    while(i>0){
        lastexc=0;
        for(j=0;j<i;j++){
            if(arr[j+1]<arr[j]){
                change_number++;
                swapp(arr[j+1],arr[j]);
                lastexc=j;
            }
        }
        i=lastexc;
    }
    return change_number;
}

void quick1(int arr[],int low,int high){    //Quick sort -- pivot as first element
    int pivot;
    if(low<high){
        int scanup=low+1;
        int scandown=high;
        pivot=arr[low];
        while(true){
            while(arr[scanup]<=pivot)
                scanup++;
            while(arr[scandown]>pivot)
                scandown--;
            if(scanup<scandown){
                swapp(arr[scandown],arr[scanup]);
            }
            else
                break;
        }
        swapp(arr[scandown],arr[low]);
        quick1(arr,low,scandown-1);
        quick1(arr,scandown+1,high);
    }
}

void quick2(int arr[],int low,int high){        //Quick sort -- pivot as middle element
    int i=low;
    int j=high;
    int pivot=arr[(low+high)/2];

    while(i<=j){
        while(arr[i]<pivot)
            i++;
        while(arr[j]>pivot)
            j--;
        if(i<=j){
            swapp(arr[i],arr[j]);
            i++;
            j--;
        }
    }
    if(low<j)
        quick2(arr,low,j);
    if(i<high)
        quick2(arr,i,high);
}




int part(int arr[],int low,int high)            //partition for quick sort 3
{
    int pivot=arr[high];
    int i=(low-1);

    for(int j=low;j<=high-1;j++)
    {
        if(arr[j]<=pivot){
            i++;
            swapp(arr[i],arr[j]);
        }
    }
    swapp(arr[i+1],arr[high]);
    return (i+1);
}

int part_r(int arr[],int low,int high)          //randomly selects pivot
{
    srand(time(0));
    int random =low+rand()%(high-low);
    swapp(arr[random],arr[high]);
    return part(arr,low,high);
}

void quick3(int arr[],int low,int high)         //quicksort 3 --randomly selected pivot
{
    if (low<high) {
        int pi=part_r(arr,low,high);
        quick3(arr,low,pi-1);
        quick3(arr,pi+1,high);
    }
}



int part_r_3(int arr[],int low,int high){       //randomly selection 3 value and selecting median from them
    srand(time(0));
    int random1,random2,random3;
    random1=low+rand()%(high-low);
    random2=low+rand()%(high-low);
    random3=low+rand()%(high-low);

    int median;
    if(arr[random1]>arr[random2]){
        if(arr[random2]>=arr[random3])
            median=random2;
        else if(arr[random3]>=arr[random1])
            median=random1;
        else
            median=random3;
    }
    else{
        if(arr[random3]>=arr[random2])
            median=random2;
        else if(arr[random1]>=arr[random3])
            median=random1;
        else
            median=random3;
    }

    swapp(arr[median],arr[high]);
    return part(arr,low,high);                      //I am using same partition function in this quicksort selection
}

void quick4(int arr[],int low,int high){            //quicksort -- pivot is median from randomly selected 3 value
    if(low<high){
        int pi=part_r_3(arr,low,high);
        quick4(arr,low,pi-1);
        quick4(arr,pi+1,high);
    }
}


int selection(int arr[],int n){                     //selection algorithm
    int change_number=0;
    int smallindex;
    int i,j;
    for(i=0;i<n-1;i++){
        smallindex=i;
        for(j=i+1;j<n;j++)
            if(arr[smallindex]>arr[j])
                smallindex=j;

        swapp(arr[i],arr[smallindex]);
        change_number++;
    }
    return change_number;
}

void insertion(int arr[], int n)                    //I am using this sorting algorithm in my own sort
{                                                   //I will combine insertion sort with quicksort
    int i, key, j;
    for(i=1;i<n;i++){
        key=arr[i];
        j=i-1;
        while(j>=0&&arr[j]>key){
            arr[j+1]=arr[j];
            j=j-1;
        }
        arr[j+1]=key;
    }
}


void combo(int arr[],int low,int high){         //My sort -- insertion sort for arrays smaller than 10
    int pivot;                                  //quicksort (quick1) for larger arrays
    if(low<high){
       if(high-low+1<10){
            insertion(arr,high-low);
        }
       else{
        int scanup=low+1;
        int scandown=high;
        pivot=arr[low];
        while(true){
            while(arr[scanup]<=pivot)
                scanup++;
            while(arr[scandown]>pivot)
                scandown--;
            if(scanup<scandown)
                swapp(arr[scandown],arr[scanup]);
            else
                break;
        }
        swapp(arr[scandown],arr[low]);
        quick1(arr,low,scandown-1);
        quick1(arr,scandown+1,high);
       }
    }
}

void comparison_bubble(int arr[],int n){            //comparison functions are for measuring # of comparisons,
    int moves;                                      //# of moves and elapsed time
    float t;                                        // this is for bubble
    if(n<=100){
            double start=double(clock());
            moves=bubble(arr,n);
            for(int i=0;i<99;i++){
                int *ptr=init(n);
                bubble(ptr,n);
            }
            double finish=double(clock());
            t=(finish-start)/100;
    }
    else{
        double start=double(clock());
        moves=bubble(arr,n);
        double finish=double(clock());
        t=finish-start;
    }

    cout<<"Bubble\t\t"<<n*n<<"\t\t"<<moves<<"\t\t"<<t<<endl;
}

void comparison_selection(int arr[],int n){             //measuring for selection sor
    int moves;
    float t;
    if(n<=100){
            double start=double(clock());
            moves=selection(arr,n);
                for(int i=0;i<99;i++){
                int *ptr=init(n);
                selection(ptr,n);
            }
            double finish=double(clock());
            t=(finish-start)/100;
    }
    else{
        double start=double(clock());
        moves=selection(arr,n);
        double finish=double(clock());
        t=finish-start;
    }
    cout<<"Selection\t"<<n*n<<"\t\t"<<moves<<"\t\t"<<t<<endl;
}


int partition_comp(int arr[], int low, int high, int & compr, int & mov) { //measuring for quicksort
    int pivot = arr[low];                                                  //It consists 3 functions with below ones
    int L=low+1;
    int R=high;
    while(true){
        compr++;
        while((L<R)&&(arr[R]>=pivot)){
            --R;
            compr++;
        }
        compr++;
        while((L<R)&&(arr[L]<pivot)){
            ++L;
            compr++;
        }
        if(L==R){
            break;
        }
    swapp(arr[L],arr[R]);
    mov += 2;
    }
}

void quickie(int arr[],int low,int high,int &compr,int &mov){        //make quick sort but this function consists compr and mov
    int boundary;                                                   //inputs also for comparing and moves numbers
    if (low<high){
        boundary=partition_comp(arr,low,high,compr,mov);
        quickie(arr,low,boundary-1,compr,mov);
        quickie(arr,boundary+1,high,compr,mov);
    }
}

void comparison_quick(int arr[],int low, int high,int &compr,int &mov){     //last function of these 3 functions.prints measured values
    int comp=0;
    int movv=0;
    float t;
    if(high-low<=100){
        double start=double(clock());
        quickie(arr,low,high,compr,mov);
            for(int i=0;i<99;i++){
                int *ptr=init(high-low);
                quickie(ptr,low,high,comp,movv);
            }
        double finish=double(clock());
        t=(finish-start)/100;
    }
    else{
        double start=double(clock());
        quickie(arr,low,high,compr,mov);
        double finish=double(clock());
        t=finish-start;
    }
        cout<<"Quick\t\t"<<compr<<"\t\t"<<mov<<"\t\t"<<t<<endl;
}

void performance_evaluation(int sizee){             //I am using this function when operation is performance evaluation
    cout<<"Algorithm\t"<<"comparisons\t\t"<<"moves\t\t"<<"time(msec)"<<endl;
    int* ptr1=init(sizee);
    int* ptr2=init(sizee);
    int* ptr3=init(sizee);
    int* ptr4=init(sizee);
    int* ptr5=init(sizee);

    comparison_bubble(ptr1,sizee);
    comparison_selection(ptr1,sizee);
    int compr=0;
    int mov=0;
    comparison_quick(ptr1,0,sizee,compr,mov);
    cout<<endl;

    comparison_bubble(ptr2,sizee);
    comparison_selection(ptr2,sizee);
    compr=0;
    mov=0;
    comparison_quick(ptr2,0,sizee,compr,mov);
    cout<<endl;

    comparison_bubble(ptr3,sizee);
    comparison_selection(ptr3,sizee);
    compr=0;
    mov=0;
    comparison_quick(ptr3,0,sizee,compr,mov);
    cout<<endl;

    comparison_bubble(ptr4,sizee);
    comparison_selection(ptr4,sizee);
    compr=0;
    mov=0;
    comparison_quick(ptr4,0,sizee,compr,mov);
    cout<<endl;

    comparison_bubble(ptr5,sizee);
    comparison_selection(ptr5,sizee);
    compr=0;
    mov=0;
    comparison_quick(ptr5,0,sizee,compr,mov);
    cout<<endl;
}



int main()
{
    int* arrayptr;
    int size_of_array;
    while(1){                           //Program works in infinite loop
        int op=menu();
        if(op==1){                      //initializes array with using init function
            cout<<"Size of the array?"<<endl;
            cin>>size_of_array;
            cout<<endl;
            arrayptr=init(size_of_array);
        }
        else if(op==2){                 //Loading data from input_array.txt,if array is small
            int init_numbers[1000];     //it loads up to last array element
            ifstream myfile("input_array.txt");
            int c=0;
            int x;
            while(c<1000&&myfile>>x)
                init_numbers[c++]=x;

            for(int i=0;i<size_of_array;i++){
                arrayptr[i]=init_numbers[i];
            }
            cout<<"Loaded from file"<<endl;
            cout<<endl;
        }
        else if(op==3){                 //bubble sorting
            bubble(arrayptr,size_of_array);
            for(int i=0;i<size_of_array;i++)    //printing sorted array
                cout<<arrayptr[i]<<endl;
        }
        else if(op==4){                 //quicksort
            int piv_select;
            cout<<"Pivot Selection?"<<endl;
            cout<<"1-select first element as pivot"<<endl;
            cout<<"2-select middle element as pivot)"<<endl;
            cout<<"3-select randomly chosen element of the array"<<endl;
            cout<<"4-select the median of 3 randomly chosen elements of the array as pivot"<<endl;
            cin>>piv_select;
            cout<<endl;

            switch(piv_select){     //using related function for different pivot selection
            case 1:
                quick1(arrayptr,0,size_of_array);
                break;
            case 2:
                quick2(arrayptr,0,size_of_array);
                break;
            case 3:
                quick3(arrayptr,0,size_of_array-1);
                break;
            case 4:
                quick4(arrayptr,0,size_of_array-1);
                break;
            default:
                cout<<"There is no such quick sort option"<<endl;
                break;
            }

            for(int i=0;i<size_of_array;i++)    //prints sorted array
                cout<<arrayptr[i]<<endl;
        }
        else if(op==5){                         //selection sorting
            selection(arrayptr,size_of_array);
            for(int i=0;i<size_of_array;i++)    //prints array
                cout<<arrayptr[i]<<endl;
        }
        else if(op==6){
            combo(arrayptr,0,size_of_array);    //insertion sort+quick sort1
            for(int i=0;i<size_of_array;i++)    //prints sorted array
                cout<<arrayptr[i]<<endl;
        }
        else if(op==7){                         //compares sorting algorithms
            cout<<"Array Size:"<<size_of_array<<endl;
            cout<<"Algorithm\t"<<"comparisons\t"<<"moves\t\t"<<"time(msec)"<<endl;
            cout<<endl;
            comparison_bubble(arrayptr,size_of_array);
            comparison_selection(arrayptr,size_of_array);
            int compr=0;
            int mov=0;
            comparison_quick(arrayptr,0,size_of_array,compr,mov);
            cout<<endl;
        }
        else if(op==8){                         //clears dynamically allocated memory
            delete arrayptr;
            break;
        }
        else if(op==9){                         //gets size and does performance evaluation
            int sizee;
            cout<<"What is the size of the arrays?"<<endl;
            cin>>sizee;
            performance_evaluation(sizee);
        }
        else{
            cout<<"There is no such operation"<<endl;
        }
    }
    return 0;
}

