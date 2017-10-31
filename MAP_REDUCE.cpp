# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <iomanip>
# include <cmath>
# include <ctime>
# include <cstring>


using namespace std;

typedef struct node
{
  char *word;
  int count;
  struct node * next;
} NODE;

NODE *head=NULL,*newhead=NULL,*recent=NULL;


//Function that prints a linked list
void display(NODE * head)
{
  NODE *ptr1=head;
  while(ptr1!=NULL)
 {
 	printf("%s , %d \n",ptr1->word,ptr1->count);
 	ptr1=ptr1->next;	
 }
}

//Function inserts elements to a linked list at head
NODE * add(NODE *head, char *wordvalue,int count)
{
	int length;
	length=strlen(wordvalue);
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    newNode->word = (char *)malloc(sizeof(char*)*(length+1));
    if(head == NULL)
    {
        newNode->count = count;            
        strcpy(newNode->word, wordvalue);
        head = newNode;
    }
    else
    {
        newNode->count = count;
        strcpy(newNode->word, wordvalue);

        newNode->next = head;
        head = newNode;
    }
}

//Function that count the occurance of a word in a sorted list
int Count(char *p)
{
	int c=0;
	while (recent!=NULL)
	{
		if (strcmp(recent->word,p)==0)
		{
			c++;
			recent=recent->next;
		}
		else
			break;
	}
	return c;	
}

//Reduce function prepare a list with word and its associated counts
void Reduce()
{
	recent=head;
	while(recent!=NULL)
    {
    	char *data=recent->word;
		int count=Count(data);
		newhead= add(newhead, data, count);
	}


}

//inserting according to the alphabetical order
void insert(char *wordvalue)
{
	int length;
	NODE *ptr=NULL,*prev=NULL;
	length=strlen(wordvalue);
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    newNode->word = (char *)malloc(sizeof(char*)*(length+1));
    printf("\n%s",wordvalue);
    if(head == NULL)
    {
        newNode->count = 1;            
        strcpy(newNode->word, wordvalue);
        head = newNode;
    }
    else
    {   
        if (isdigit(*(wordvalue+0)))
        {
        	ptr=head;
        	prev=ptr;
        	while ( ptr!=NULL)
        	{
        		
        		 	if (atoi (wordvalue)>atoi(ptr->word))
        		 	{
        		 		break;
					 }
					 else
					 {
					 	prev=ptr;
        		 		ptr=ptr->next;
					 }
				 
				 
			}
        	newNode->count = 1;            
            strcpy(newNode->word, wordvalue);  
			newNode->next=ptr;
			prev->next=newNode;
		}
		else
		{
			ptr=head;
			prev=ptr;
		    newNode->count = 1;
	        strcpy(newNode->word, wordvalue);
	    	while( ptr!=NULL)
	    	{
	    		if (strcmp(ptr->word,newNode->word) >0 )
	    		{
	    			  	break;
				}
				else
				{
					prev=ptr;
	    			ptr=ptr->next;
				}
	    			
			}
	       
			newNode->next=ptr;
			prev->next=newNode;
		}
	}
}

//Map function reads a file and insert each word with count one into a linked list
void Map(FILE *fp)
{
  if(fp != NULL)
    {
    char *cp;
    char *bp;
    char line[5000];
	    while (fgets(line, sizeof(line), fp) != NULL) 
		{
	        bp = line;
	        while (1) 
			{
	            cp = strtok(bp, "(),.;:\"\"!?- \n");
	            bp = NULL; 
	            if (cp == NULL)
	                break;
	            insert(cp);
	
	        }
	    }
    }

}


//Main function first calls the map and then reduce to get the sorted list
int main()
{
	char filename[100];
	FILE *fp;
	printf("Enter the name of the file:");
	scanf("%s",filename);
	fp = fopen(filename, "r");
    if (!fp)
  {
    printf("Couldn't open the file for reading\n");
    return 1;
  }
    Map(fp);
    display(head);
    Reduce();
	printf("\nPrinting the Worcounts:-\n");
	display(newhead);
	fclose(fp);
	return 0;
}
  


