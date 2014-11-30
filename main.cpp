/*********************************************************************************************************
Subject           :  Advanced Programming Lab (CS6140)

Assignment        :  01 - Removing Duplicates from a list

File name         :  MAIN.CPP

Description       :  Implements main functions required to remove duplicates from a list

Programmers       :  (1) Pradip Hatwar     (CS13M022)
                     (2) Hem Kapil         (CS13M023)
                     (3) Pradeep Vankadaru (CS13M037)

Compiler name     :  g++ 4.6

Date created      :  19/08/2013

List of functions : (1)  int main(int argc, char *argv[])
                    (2)  int PURGE(MYLIST *L)
                    (3)  int check_files(char *inpfile, char *optfile)
                    (4)  int read_inpfile(char *inpfile, MYLIST *L)
                    (5)  int validate_input(char *input)
                    (6)  write_output
History           :  

*********************************************************************************************************/
#include<iostream>
#include<cstdlib>
#include<ctype.h>
#include<malloc.h>
#include<fstream>
#include<string.h>

#include "list.h"

/*********************************************************************************************************
Function Name            : main 
Inputs                   : (1) Name of Input Text file to read items of list
						   (2) Name of output text file to print list after purging
Outputs                  : int
Description              : This is a 'main'function which calls other function for removing duplicates 
						   from a list.
*********************************************************************************************************/

int main(int argc, char *argv[])
{
	
	int retval = 0;
	MYLIST L;
		
	
	if(argc != 3)  // Check if proper number of inputs are not given in the command line
	{   
		cout << "Error: valid command for execution is <exename> <inpfilename> <optfilename>"<< endl;
		cout << "Exiting ....." <<endl;
		exit(-1);		
	}
	else if(check_files(argv[1],argv[2]) == -1) // Check for successful file existence operation on input file and
	{					    // successful create operation on outfile file given
	
		exit(-1);	
	}
	else if(L.success == false)	// Check if unable to create object of LIST ADT
	{				
		cout << "Failed to create LIST object, Exiting" << endl;
        	exit(-1);         
	}
	else if(read_inpfile(argv[1], &L) == -1)  // Check for the validity of items in the input file and insert into LIST ADT
	{  
		exit(-1);	
	}
	else
	{	
		cout << "\nBefore Purging................." ;
	
		L.PRINTLIST();			// Print the items in the list before purging
			
		retval = PURGE(&L);		// Purges duplicate element from the LIST ADT
		if(retval == -1)
		{
			cout << "Failed to Purge List, Exiting...." << endl;	
			exit(-1);			
		}
		else
		{
			cout << "\nAfter Purging.................." ;
			L.PRINTLIST();				// Print the items in the list after purging
		
			if(write_output(&L,argv[2]) == -1)  	// Check for successful write operation to output file
			{	
				cout << "Failed to write to output file" << endl;
			}
			else
			{
				cout << endl << "Program completed successfully" << endl;
			}
		}
	} // End 
	
	getchar();
	return 0;
}

/*********************************************************************************************************
Function Name            : PURGE 
Inputs                   : (1) Reference to the LIST object	   
Outputs                  : int
Description              : This function removes duplicates from the list of items

Psuedo Code		 :
			   procedure PURGE(var L: LIST)
			   begin
			   	p= FIRST(L)
			   
			   	while p<> ENDL(L) do begin
					q= NEXT(p)
					
					while q <> ENDL(L) do begin
						if RETRIEVE(p) == RETRIEVE(q)then
							DELETE(q)
						else
							q = NEXT(q)
					end
					p= NEXT(p)
			  	end
			    end
*********************************************************************************************************/


int PURGE(MYLIST *L)
{

	int p1=0; 	/* p1 is the current position in L */
	int q1=0; 	/* q1 moves ahead in the list L to find equal elements */
	int error =0;

	p1= L->FIRST();

	while ( (p1 < L->ENDL()) && (p1 != -1)) /* p1 is either valid position or -1 */
	{
		q1= L->NEXT(p1);
		
		while((q1!= (L->ENDL() + 1)) && (q1!= -1))   /* q1 is either valid position or -1 */
		{			
			if(L->RETRIEVE(p1)==L->RETRIEVE(q1)) /* Check for equal items in the list*/
			{
				error = L->DELETE(q1);	     /* Deleting duplicate from list*/			
			}
			else
			{
				q1=L->NEXT(q1);		    
			}
			
		}  
		p1=L->NEXT(p1);
	} 
	return error;
}


/*********************************************************************************************************
Function Name            : check_files 
Inputs                   : (1) Reference to input file
						   (2) Reference to output file
Outputs                  : -1 In case of any error occurrs
                            0 In case of sucessful file operations
Description              : This function verifies the existence of input file, output file and 
						   creates output file if it does not exist
*********************************************************************************************************/
int check_files(char *inpfile, char *optfile)
{

	int		retval = 0;
	ifstream	inpstrm ; // Input file reference
	ofstream	optstrm ; // Output file reference
	

	inpstrm.open(inpfile, ios::in); /* Opening Input file */

	if(!inpstrm)
	{
		cout << "Input File does not exist" << endl;
		cout << "Exiting...." << endl;
		retval = -1;
	}
	else
	{	
		inpstrm.close();
		optstrm.open(optfile, ios::out | ios::trunc); /* Creating output file */

		if(!optstrm)
		{
			cout << "Output File does not exist" << endl;
			cout << "Exiting...." << endl;
			retval = -1;
		}
		else
		{	
			optstrm.close();
		} // End of if(!optstrm)

	} // End of if(!inpstrm)
	
		
	return retval;
}

/*********************************************************************************************************
Function Name            : read_inpfile 
Inputs                   : (1) Reference to input file
						   (2) Reference to LIST object
Outputs                  : -1 In case of any error occurrs
                            0 In case of sucessful read from input file and insert into list is over
Description              : This function reads data from input file and validates its contents and 
						   inserts the validated item into LIST object
*********************************************************************************************************/
int read_inpfile(char *inpfile, MYLIST *L)
{

	int		retval = 0, count = 0;
	ifstream	inpstrm ;	
	char		buff[100],ch;

	
	inpstrm.open(inpfile, ios::in);	/* Opening Input file */

	if(!inpstrm){
		cout << "Input File does not exist" << endl;
		cout << "Exiting...." << endl;
		retval = -1;
	}
	else
	{	
		
		while(inpstrm)
		{			
			inpstrm.getline(buff,100,' ');	/* Reading Input file item wise */
			
			if(inpstrm)
			{
				if(inpstrm.eof()) 
				{
					buff[strlen(buff)-1] = '\0';
				}

				retval = validate_input(buff); /* Validating items read from Input file */

				if(retval != -1)
				{
					retval = L->INSERT(atoi(buff),count); /* Insert valid items in the LIST ADT   */

					if(retval == -1)
					{
						cout << "Failed to add data to List" << endl;
						retval = 0;
						break;
					}	

					count++;
				}
				else
				{
					retval =0;
				}
			}
		}

		inpstrm.close(); /* Closing the input file */
	}

	 if (count ==0) /* Check for empty Input List */ 
	  {
	     
	    cout << endl << "Nothing to purge...Input List is invalid/empty!!!" << endl;
	    retval = -1;
	  }

	return retval;
}

/*********************************************************************************************************
Function Name            : validate_input 
Inputs                   : (1) Reference to input file					
Outputs                  : -1 In case of any error occurrs
                            0 In case of sucessful read from input file and insert into list is over
Description              : This function validates the token read by read_inpfile to be valid integers
*********************************************************************************************************/
int validate_input(char *input)
{

	int	retval =0, iter =0;

	//Verifying if blank space is received
	if(strlen(input) == 0)
	{
		retval = -1;
	}
	else
	{
		//Verifying if first character is starting with  either minus symbol or digit
		if((input[0] == '-') || (isdigit(input[0]))|| (input[0] == '+'))
		{
			//Verifying if string is starting with -1, checking all digits from 2nd digit onwards
			if((input[0] == '-') || (input[0] == '+'))
			{
				//Verifying If string is starting with -/+ and it's length is '1', it's not a valid number
				if(strlen(input) == 1)
				{
					retval = -1;
					cout << input << " is not a valid number, Discarding it" << endl;	
				}
				else
				{
					for(iter = 1; iter <  strlen(input); iter++)
					{
						if(!isdigit(input[iter]))
						{
							retval = -1;
							cout << input << " is not a valid number, Discarding it " << endl;
							break;
						}									
					}			
				}
			}
			//Verifying if string is starting with digit, checking all digits from first digit onwards
			else
			{

				for(iter = 0; iter <  strlen(input); iter++)
				{
					if(!isdigit(input[iter]))
					{
						retval = -1;
						cout << input << " is not a valid number, Discarding it " << endl;
						break;
					}									
				}
				
			}
		}
		else
		{
			cout << input << " is not a valid number, Discarding it" << endl;			
			retval = -1;

		}	
	}
	return retval;
}


/*********************************************************************************************************
Function Name            : write_output 
Inputs                   : (1) Reference to LIST object
						   (2) Reference to input file
Outputs                  : -1 In case of any error occurrs
                            0 In case of sucessful read from input file and insert into list is over
Description              : This function writes the purged items into the output text file
*********************************************************************************************************/

int write_output(MYLIST *L, char *optfile){

	int 		retval = 0, p1 = 0, no_chars = 0;
	ofstream 	optstrm;
	char		buff[100];

	optstrm.open(optfile, ios::out | ios::trunc); /* Opening output file */

	if(!optstrm)
	{
		cout << "Output File does not exist" << endl;		
		retval = -1;
	}
	else
	{	
		p1= L->FIRST();	

		while ( (p1 <= L->ENDL()) && (p1 != -1))
		{			
			//writing value to the output file
			no_chars = sprintf(buff,"%d",L->RETRIEVE(p1));
			buff[no_chars] = '\0';
			if(optstrm.write(buff,no_chars))
			{
				//For writing blank space after every value is written to the file
				buff[0] = ' ';
				no_chars = 1;
				buff[no_chars] = '\0';
				if(!optstrm.write(buff,no_chars))
				{
					retval = -1;
					break;					
				}
			}
			else
			{
				retval = -1;
				break;	
			}
		
			p1=L->NEXT(p1);
		}
		optstrm.close();	/* Closing output file */
	}
	
	return retval;	
}
	

