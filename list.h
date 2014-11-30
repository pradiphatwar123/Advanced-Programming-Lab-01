
#ifndef _MYLIST_H_
#define _MYLIST_H_

#define INITIAL_LIST_SIZE 1024
#define LIST_INCREMENT 512

#define POSITIVE_SENTINEL ((pow(2,((sizeof(int)*8)-1))) - 1)

#define NEGATIVE_SENTINEL (-(pow(2,((sizeof(int)*8)-1)))) 

 
using namespace std;

/* LIST Abstract Data Type Definition with interfaces */
class MYLIST
{

	public:
		MYLIST();
		~MYLIST();
		int INSERT(int itemToInsert, int position);
		int RETRIEVE(int position);
		int DELETE(int position);
		int NEXT(int position);
		int ENDL();
		int FIRST();
		void PRINTLIST();
    		bool success;
	private:
		int last;
		int position;	
		int LIST_SIZE;	
};

/*Function to remove duplicates from LIST */
int	PURGE(MYLIST *);

/*Function to check existence of input files */
int 	check_files(char *, char *);

/*Function to read items from input file */
int 	read_inpfile(char *, MYLIST *);

/*Function to validate items read from input file */
int 	validate_input(char *);

/*Function to write purged items from the list to output file */
int	write_output(MYLIST *, char *);

#endif 
