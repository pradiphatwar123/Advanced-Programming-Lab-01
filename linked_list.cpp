/*********************************************************************************************************
Subject           :  Advanced Programming Lab (CS6140)

Assignment        :  01 - Removing Duplicates from a list

File name         :  LINKED_LIST.CPP

Description       :  Implements Interfaces for LIST Abstract Data Type (ADT) using Single Linked List

Programmers       :  (1) Pradip Hatwar     (CS13M022)
                     (2) Hem Kapil         (CS13M023)
                     (3) Pradeep Vankadaru (CS13M037)

Compiler name     :  g++ 4.6

Date created      :  19/08/2013

List of functions : (1)  void MYLIST(void)
                    (2)  void ~MYLIST(void)
                    (3)  int INSERT(int , int )
                    (4)  int DELETE(int )
                    (5)  void PRINTLIST(void )
                    (6)  int FIRST(void)
                    (7)  int ENDL(void)
                    (8)  int NEXT(int)
                    (9)  int PREVIOUS(int )
                    (10) int RETRIEVE(int )

History           :  

*************************************************************************************************/
#include<iostream>
#include<math.h>
#include"list.h"


// Defination of linked list node 'LIST_NODE'
class LIST_NODE{
  public:
		LIST_NODE();
		~LIST_NODE();

		int data;
		LIST_NODE *next;
};

// Constructor for LIST_NODE
LIST_NODE::LIST_NODE()
{
                       
}

// Destructor for LIST_NODE
LIST_NODE::~LIST_NODE()
{
                       
}      

LIST_NODE *hdr; // Pointer referencing to Head node of linked list

//extern int LIST_LEN;

MYLIST::MYLIST()
{          
    	last = -1;
	position = 0;
     	success = true;      
	LIST_SIZE = INITIAL_LIST_SIZE;
  
	try{
	    	hdr = new LIST_NODE;
    	}catch (bad_alloc xa) {
        	success = false;   
        	cout << "Failed to Intialize Linked List Header Node" << endl;           
    	}
	hdr->data = POSITIVE_SENTINEL;//sentinal value,largest signed integer	
	hdr->next = NULL;	
}




MYLIST::~MYLIST(){
                  
    LIST_NODE   *temp;                
                                
    temp = hdr->next;
    while(temp != NULL){
        hdr->next = temp->next;
        delete temp;
        temp = hdr->next;     
    }             
    delete hdr;//Deleting Header Node       
}

/*********************************************************************************************************
Function Name            : INSERT 
Inputs                   : (1) int itemToInsert
                           (2) int position
Returns                  : -1 In case of any error occurred during INSERT operation on linked list
                            0 In case of successfull INSERT operation on linked list 
Description              : This function inserts element 'itemtoInsert' at given input position 
						   'position' in the linked list 
*********************************************************************************************************/
int MYLIST::INSERT(int itemToInsert, int position)
{
	int error = 0, count = 1;
	LIST_NODE *newnode = NULL, *temp = NULL, *temp1 = NULL;
	
    if(last >= (LIST_SIZE - 1))
    {
        cout << "\n List is full, Resizing\n";	
	LIST_SIZE = LIST_SIZE + LIST_INCREMENT;
    }else if(( position > (last + 1) ) || (position < 0)){ 	    
        cout << "\nPosition does not exist\n";
        error = -1;        
    }
    
    //This is c++ function to allocate memory dynamically
    	try{
	        newnode = new LIST_NODE;
        }catch (bad_alloc xa) {
            cout << "Failed to Allocate Momory for new node\n";           
            error = -1;            
        }		
        if(error != -1){
            newnode->data = itemToInsert;
	    newnode->next = NULL;
	    //Element is the 1st element inserting
	    if(position == 0)
	    {
                temp = hdr->next;                        
		hdr->next = newnode;
		newnode->next = temp;
		last++;
            }else{
                temp = hdr->next;		
		        while((temp->next != NULL) && (count < position))
			{                           	                    
			        temp = temp->next;
			        count++;
		        }
		        if(count == position){
                    temp1 = temp->next;        
                    temp->next = newnode;	
                    newnode->next = temp1;
                    last++;
                }else{
                    cout << "Position does not exist\n";
                    error = -1;                    
                }
            }
        } 
	return error;
}
/*********************************************************************************************************
Function Name            : DELETE 
Inputs                   : (1) int position                          
Returns                  : -1 In case of any error occurred during DELETE operation on linked list
                            0 In case of successfull DELETE operation on linked list 
Description              : This function deletes element at at given input position 'position' in the linked list 
*********************************************************************************************************/
int MYLIST::DELETE(int position)
{
	int error = 0, count = 0;
	LIST_NODE *temp = NULL, *temp1 = NULL, *temp2 = NULL;
	
	if((position > last) || (position < 0))
	{
            cout << "Invalid position\n";
            error = -1;         
	}
	else 
	{
            temp =  hdr->next;
    	    while((temp->next != NULL) && (count < position)) // To handle the deletion of node at given valid position in the list
		{
    		        temp1 = temp;             
    		        temp = temp->next;            
   		         count++;                                   
        	}
        	temp2 = temp->next;
        
	    if(temp1 == NULL)   // To handle the deletion of node at 0th position in the list
		{
	            if(temp->next != NULL)   
	                hdr->next = temp2;
	            else
	                hdr->next = NULL;     
	        }
           else               
   	         temp1->next = temp2;

            //Freeing the memory occupied by the element being deleted
            delete(temp);
            //Decrementing last counter whenever item is deleted
        last--;
      }
      
     return error;
}

/*********************************************************************************************************
Function Name            : PRINTLIST 
Inputs                   : void                         
Returns                  : void
Description              : This function prints all the items present in the linked list 
*********************************************************************************************************/
void MYLIST::PRINTLIST()
{
	LIST_NODE	*temp = NULL;
		
	temp = hdr->next;
	cout << "\nItems in the list are : "<< "\t" ;
	while(temp != NULL){
		cout << temp->data  << "\t";
		temp = temp->next;
    }    
    cout << endl;
}

/*********************************************************************************************************
Function Name            : FIRST 
Inputs                   : void                         
Returns                  : First position on the linked list
Description              : This function returns the first position on linked list                          
*********************************************************************************************************/

int MYLIST::FIRST()
{
	return 0;
}
/*********************************************************************************************************
Function Name            : ENDL 
Inputs                   : void                         
Returns                  : last position on the linked list
Description              : This function returns the last position on the linked list                          
*********************************************************************************************************/

int MYLIST::ENDL()
{
	return (last);
}

/*********************************************************************************************************
Function Name            : NEXT 
Inputs                   : (1) int position                         
Returns                  : last position on the linked list in case of successfull NEXT operation on linked list
                           -1 In case of any error occurred during DELETE operation on linked list
Description              : This function returns the position following at given input 'position' in the linked list                          
*********************************************************************************************************/
//Returns the Index of the next item in the list
int MYLIST::NEXT(int position)
{
	int newPosition = 0;
	
	newPosition = position + 1;
	if(newPosition > last)
	    return -1;
    	else
            return newPosition;
}

/*********************************************************************************************************
Function Name            : RETRIEVE 
Inputs                   : (1) int position                         
Returns                  : previous position on the linked list in case of successfull PREVIOUS operation 
                           -1 In case of any error occurred during PREVIOUS operation on linked list
Description              : This function returns the element at given input position in the linked list                         
*********************************************************************************************************/
int MYLIST::RETRIEVE(int position)
{
    	int          element, count = 0;
	LIST_NODE    *temp;
	
	if((position < 0 ) || (position > last)){
        	cout << "Element does not exist at the given position\n";
         	element = NEGATIVE_SENTINEL;//Sentinel value, Smallest signed Integer       
    	}else {                           
	     temp = hdr->next;
	     while((temp != NULL) && (count < position)){       
             temp = temp->next;
             count++;            
         }
         if(temp != NULL)
             element = temp->data;
         else
             element = NEGATIVE_SENTINEL;//Sentinel value, Smallest signed Integer    
    }
	return element;
}
  

