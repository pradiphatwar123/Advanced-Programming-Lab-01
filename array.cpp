
/*********************************************************************************************************
Subject           :  Advanced Programming Lab (CS6140)

Assignment        :  01 - Removing Duplicates from a list

File name         :  ARRAY.CPP

Description       :  Implements Interfaces for LIST Abstract Data Type (ADT) using Arrays

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

*********************************************************************************************************/

#include<iostream>
#include "list.h"
#include<math.h>


int	*listArray;// listArray is a global array for LIST operations

int 	resize_list(int *);


MYLIST::MYLIST() : last(-1), position(0),success(true),LIST_SIZE(INITIAL_LIST_SIZE)
{
	try{
		listArray = new int[LIST_SIZE];
	}catch(bad_alloc xa){
		success = false;
		cout << "Failed to intializa memory for Array List " << endl; 
	}
}


MYLIST::~MYLIST()
{	
	delete [] listArray; 	
}


/*********************************************************************************************************
Function Name            : INSERT 
Inputs                   : (1) int itemToInsert
                           (2) int position
Returns                  : -1 In case of any error occurred during INSERT operation on array
                            0 In case of successfull INSERT operation on array 
Description              : This function inserts element 'itemtoInsert' at given input position 
						   'position' in the Array 'listArray'
*********************************************************************************************************/
int MYLIST::INSERT(int itemToInsert, int position)
{
	int 	q=0, error = 0;
		
		
    if(last >= (LIST_SIZE - 1))
    {
        cout << "\n List is full, Resizing the Array" << endl;	
	error = resize_list(&LIST_SIZE);
    }else if ((position > (last + 1 )) || (position <0))
    {
	    cout << "Position does not exist" << endl;
	    error = -1;
    }
    if(error != -1)
    {	              
	for( q=last; q >= position; q--)
		listArray[q+1] = listArray[q];		     
        listArray[position] = itemToInsert;        
        last = last+1;	        
    }
    return error;
}

/*********************************************************************************************************
Function Name            : DELETE 
Inputs                   : (1) int position                          
Returns                  : -1 In case of any error occurred during DELETE operation on array
                            0 In case of successfull DELETE operation on array 
Description              : This function deletes an element at at given input position 'position' 
						   in the Array 'listArray'
*********************************************************************************************************/
int MYLIST::DELETE(int position)
{

	int q=0, error=0;

	if(( position > last) || ( position < 0)){
        	cout << "Invalid position\n"; 	
		error = -1;
    	}else
	{
		for( q=position; q<last ; q++)
			listArray[q] = listArray[q+1];
		last = last -1;
	}
	return error;
}

/*********************************************************************************************************
Function Name            : PRINTLIST 
Inputs                   : void                         
Returns                  : void
Description              : This function prints all the items present in the Array 'listArray'
*********************************************************************************************************/
void MYLIST::PRINTLIST(void)
{
	int j=0;
	
	cout << "\nItems in the list are : "<< "\t" ;
	for(j=0; j<=last; j++)
	    cout << listArray[j] << "\t" ;
    cout << endl;
  
}

/*********************************************************************************************************
Function Name            : FIRST 
Inputs                   : void                         
Returns                  : First position on 'listArray'
Description              : This function returns the first position on 'listArray'                          
*********************************************************************************************************/
int MYLIST::FIRST(void)
{
	return 0;
}

/*********************************************************************************************************
Function Name            : ENDL 
Inputs                   : void                         
Returns                  : last position on 'listArray'
Description              : This function returns the last position on 'listArray'                          
*********************************************************************************************************/
int MYLIST::ENDL(void)
{
	return (last );
}

/*********************************************************************************************************
Function Name            : NEXT 
Inputs                   : (1) int position                         
Returns                  : last position on 'listArray' in case of successfull NEXT operation on array
                           -1 In case of any error occurred during DELETE operation on array
Description              : This function returns the position following at given input 'position' in 'listArray'                          
*********************************************************************************************************/
int MYLIST::NEXT(int position)
{
	int newPosition=0;

	newPosition = position + 1;
	if (newPosition > last)
		newPosition = -1; 
	else
		newPosition = position + 1;
    
	return newPosition;
}

/*********************************************************************************************************
Function Name            : RETRIEVE 
Inputs                   : (1) int position                         
Returns                  : Returns Element stored at the given position
                          Sentinel value if given position is not valid
Description              : This function returns the element at given input position in the 'listArray'                          
*********************************************************************************************************/
int MYLIST::RETRIEVE(int position)
{
	int element;

	if ((position >= 0) && (position <= last))
	    	element = listArray[position]; 
	else{
        	cout << "\nElement does not exist at the given position\n"; 
		element = NEGATIVE_SENTINEL; //Sentinel value, Smallest signed Integer
    	}    
	return element;
}
/*********************************************************************************************************
Function Name            : resize_list
Inputs                   : (1) int reference to LIST_SIZE variable                         
Returns                  : It returns 0 in case of success
                           -1 In case of any error
Description              : This function resizes the List Array dynamically and modifies LIST_SIZE                          
*********************************************************************************************************/
int resize_list(int *LIST_SIZE){

	int	*temp, old_list_size, iter = 0,error = 0;		
	
	old_list_size =  *LIST_SIZE;
	//cout << "Old List Size is " << *LIST_SIZE << endl;
	*LIST_SIZE = *LIST_SIZE + LIST_INCREMENT;
	//cout << "New List Size is " << *LIST_SIZE << endl;
	try{
		temp = new int[*LIST_SIZE];
	}catch(bad_alloc xa){
		cout << "Failed to allocate memory for resized array" << endl;
		error = -1;
	}
	for(iter = 0; iter < old_list_size; iter++){
		temp[iter] = listArray[iter];
	}	
	delete [] listArray;
	listArray = temp;
	temp = NULL;

	return error;
}

