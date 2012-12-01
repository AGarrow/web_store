//  menu.c: Contains menu interface (menuPrompt function),
//  and add,edit,verify,delete (del) functions called my passweb.c's main()

void menuPrompt()
{

	while(1){
      
      printf("  MAIN MENU \n =========== \n 1. Add \n 2. Edit \n 3. Delete \n 4. Verify \n 5. Exit \n Selection:  ");   
      
      //Get selection from user
      char selection = getchar();
      char junk = getchar();

		//User chose add
      if ( selection == '1')
		{
			char username[15];
			char password[15];
			char type[15];

			printf("Enter a username to add:\n");
			gets(username);
			
			printf("Enter password:\n");
			gets(password);
			
			printf("Enter type:\n");
			gets(type);

			addDB(username,password,type);
		}
		
		 //User chose edit
		 else if ( selection == '2')
		{
			char username[15];
      char password[15];
      char type[15];
			char user_2[15];
			char pass_2[15];
			char type_2[15];
			
			printf("Enter a username to edit:\n");
      gets(username);
                        
      printf("Enter old password:\n");
      gets(password);
                        
      printf("Enter old type:\n");
      gets(type);
	
			printf("Enter new username:\n");
			gets(user_2);

      printf("Enter new password:\n");
      gets(pass_2);

      printf("Enter new type:\n");
      gets(type_2);

			editDB(username,password,type,user_2,pass_2,type_2);

		}

		//User chose delete
		else if ( selection == '3')

		{
			char username[15];

			printf("Enter a username to delete:\n");

			gets(username);

			delDB(username);

		}

		//User chose verify
		else if ( selection == '4')
		{

			char username[15];
			char password[15];
      int result;
		
			printf("Enter a username to verify:\n");
			
			gets(username);

      printf("Password:\n");
			
			gets(password);

			result = verifyDB(username,password);
			
			if (result == 0)
				printf("EXIT_FAILURE\n");

			if (result == 1)
				printf("EXIT_SUCCESS\n");
		}
		
		//User is exiting the menu interface
		else 
			return ;		

	}
}

//Functions to manipulate password.csv begin here (called by passweb.c, and
//menuPrompt() above...

//Verify function (username and password)
int verifyDB (char username[15], char password[15])
    {

		            FILE *fp;
                char arr[50][50];
                int usernameFound = 0;

                fp = fopen("../databases/members.csv", "r");

                decrypt(fp,arr);

                for (int i = 0; i < 20; i ++)
                {
                        char *c;
                        char *d;

                        c = strstr(arr[i],username);
                        d = strstr(arr[i],password);

                        if (c != NULL && d != NULL)
                               usernameFound = 1;

                }

                fclose(fp);

                if (usernameFound ==  0)
                        return 0;

                else if (usernameFound == 1)
                        return 1;
}

//Verify helper function (only username, used in add,edit,del)
int verifyUser (char username[15])
    {

		            FILE *fp;
                char arr[50][50];
                int usernameFound = 0;

                fp = fopen("../databases/members.csv", "r");

                decrypt(fp,arr);

                for (int i = 0; i < 50; i ++)
                {
                        char *c;

                        c = strstr(arr[i],username);

                        if (c != NULL)
                               usernameFound = 1;

                }

                fclose(fp);

                if (usernameFound ==  0)
                        return 0;

                else if (usernameFound == 1)
                        return 1;
}

//add function
void addDB (char username[15], char password[15], char type[15])        
{                
    int result = 0;                
    result = verifyUser(username);                

    if (result == 1)                
    { 
        printf("The username already exists, please try again.\n");
    }

    if (result == 0)
    {	
	      FILE *fp;
        char finalStr[50];
        char arr[50][50];

        fp = fopen("../databases/members.csv", "r");

        decrypt(fp,arr);

        fclose(fp);

        strcpy(finalStr,username);
        strcat(finalStr,", ");
        strcat(finalStr,password);
        strcat(finalStr,", ");
        strcat(finalStr,type);

        fp = fopen("../databases/members.csv", "a");

        fprintf(fp,"%s\n",finalStr);

        fclose(fp);

        printf("Success.\n");
    }
}

void delDB (char username[15])
        {
                int result = 0;

                result = verifyUser(username);

                if (result == 0)
                {
                        printf("The username does not exist - cannot delete. Please try again.\n");
                }

                if (result == 1)
                {       
			                  FILE *fp;			

                        char arr[50][50];

                        fp = fopen("../databases/members.csv", "r");

                        decrypt(fp,arr);

                        fclose(fp);

                        for (int i = 0; i < 50; i++)
                        {

                                char *c;

                                c = strstr(arr[i],username);

                                if (c != NULL)
                                {
                                        for (int j = 0; j < strlen(arr[i]); j++)
                                                arr[i][j] ="";
                                        
                                        while (i < 30){
                                          strcpy(arr[i],arr[i+1]);
                                          i++;
                                        }
                                        break;
                                }

                        }

                        fp = fopen("../databases/members.csv","w");

                        encrypt(arr,fp);

                        fclose(fp);

                        printf("Success\n");
                }

        }

void editDB (char username[15], char password[15],char type[15],char user_2[15],char pass_2[15], char type_2[15])
        {
                int result = 0;

                result = verifyUser(username);

                if (result == 0)
                {
                        printf("The username does not exist - cannot edit. Please try again.\n");
                }

                if (result == 1)
                {
                	      FILE *fp;
		                    char arr[50][50];
                        char finalStr[50];

                        fp = fopen("../databases/members.csv", "r");

                        decrypt(fp,arr);

                        fclose(fp);

                        strcpy(finalStr,user_2);
                        strcat(finalStr,", ");
                        strcat(finalStr,pass_2);
                        strcat(finalStr,", ");
                        strcat(finalStr,type_2);

                        for (int i = 0; i < 50; i++)
                        {
                                char *c;

                                c = strstr(arr[i],username);

                                if (c != NULL)
                                {
                                        strcpy(arr[i],finalStr);
                                        break;
                                }

                        }

                        fp = fopen("../databases/members.csv","w");

                        encrypt(arr,fp);

                        fclose(fp);

                }

        }
