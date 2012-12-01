//PASSWEB.C: Contains main() function and command line processing of switches.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include "menu_webstore.h" //addDB, verifyDB, delDB, editDB, menuPrompt
#include "cipher_webstore.h" //encrypt, decrypt
#include "menu_webstore.c"
#include "cipher_webstore.c"

int main(int argc, char *argv[])
{
	int ctr, add, menu, del, edit, verify, unames;	
	char username[15], password[15], type[15], user_2[15], pass_2[15], type_2[15];
	
	add = 0;
	menu = 0;
	del = 0;
	edit = 0;
	verify = 0;
	unames = 0;
	

	//Check existence of file "password.csv", if not present, create it.
	FILE *file;
	if ((file = fopen("../databases/members.csv", "r")) == NULL) 
	{
  		if (errno == ENOENT) 
		{
    printf("members.csv doesn't exiist, creating it\n");
  		       	file = fopen("../databases/members.csv","w");
			fclose(file);
		} 
		else 
		{
    			printf("Some other error occured\n");
  	      return 0;
    }
	} 
	
	else 
	{
  		fclose(file);
	}
	
	//check which command line switches present, fill variables with info
	for(ctr=1; ctr < argc; ctr++)
		{
			if (strcmp(argv[ctr],"-add") == 0)
				add++;

			else if (strcmp(argv[ctr],"-menu") == 0)
				menu ++;

			else if (strcmp(argv[ctr],"-del") == 0)
				del ++;

			else if (strcmp(argv[ctr],"-edit") == 0)
				edit++;

			else if (strcmp(argv[ctr],"-verify") == 0)
				verify++;
		
			else if (argv[ctr][0] == '-')
      {
        fprintf(stderr, "Error: please choose a valid option.\n Syntax: passweb -menu -add –del –edit –verify username password type user_2 pass_2 type_2\n");
        return 0;
      }
			else 
			{	

				while ( ctr < argc ){
 
				switch (unames)
				{
				case 0:
					strcpy(username,argv[ctr]);
					unames++;
					break;
				case 1:
					strcpy(password,argv[ctr]);
					unames++;
					break;
				case 2:
					strcpy(type,argv[ctr]);
					unames++;
					break;
				case 3:
					strcpy(user_2,argv[ctr]);
					unames++;
					break;
				case 4:
					strcpy(pass_2,argv[ctr]);
					unames++;				
					break;
				case 5:
					strcpy(type_2,argv[ctr]);
					unames++;
					break;
				default:
					printf("You have entered too many parameters.\n Syntax: passweb -menu -add –del –edit –verify username password type user_2 pass_2 type_2\n");
					return 0;
				}

				ctr ++;
			}

			}

		}
	
  //ensure only one argument present
	if (menu == 1)
	{	
		menuPrompt();
    return 0;
  }

	if ((add == 1) && (del == 1 || edit == 1 || verify == 1))
	{		
	fprintf(stderr, "Only enter one option please.\n Syntax: passweb -menu -add –del –edit –verify username password type user_2 pass_2 type_2\n");
	return 0;
	}

	if ((del == 1) && (add == 1 || edit == 1 || verify == 1)) 	
	{	
	fprintf(stderr, "Only enter one option please.\n Syntax: passweb -menu -add –del –edit –verify username password type user_2 pass_2 type_2\n");
	return 0;
	}

	if ((edit == 1) && (add == 1 || del == 1 || verify == 1))
	{
	fprintf(stderr, "Only enter one option please.\n Syntax: passweb -menu -add –del –edit –verify username password type user_2 pass_2 type_2\n");
	return 0;
	}
	
	if ((verify == 1) && (add == 1 || del == 1 || edit == 1))
	{	
	fprintf(stderr, "Only enter one option please.\n Syntax: passweb -menu -add –del –edit –verify username password type user_2 pass_2 type_2\n");
	return 0;
	}

  //depending on switch selected, call corresponding function
	if (verify == 1)
	{
		int result;
		
		verifyDB(username,password);


	}

	if (add == 1)
	{
		addDB(username,password,type);
	}


	if (del == 1)
	{
		delDB(username);
	}


	if (edit == 1)
	{
		editDB(username,password,type,user_2,pass_2,type_2);
	}

	return 0;
}
