// login.c: This is a cgi script that validates the login information
// posted from login.html with a local file called members.csv. If the
// validation is successful, then the page login
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

int verifyDB (char username[40], char password[40]);

int main(){

  printf("Content-type: text/html\n\n");

//Most of this code just stores the username, password entered in html form
//in variables username, password  
  char c;
  int i = 0;
  int j = 0;
  char input[200];
  char username[40];
  char password[40];

  int length = atoi(getenv("CONTENT_LENGTH"));
  
  length++;

  fgets (input,length,stdin);

  while ((c = input[i]) != '='){
    i++;
  }

  i++;

  while ((c = input[i]) != '&'){
      username[j] = c;
      i++;
      j++;
  }

  username[j] = '\0';
  
  j = 0;

  while ((c = input[i]) != '='){
    i++;
  }

  i++;

  while ((c = input[i]) != EOF && i < length){
      password[j] = c;
      i++;
      j++;
  }

  password[j] = '\0';

//Call verifyDB to get either 0 (un/pass failure)
//1 -> user,pass correct, user is of type USER
//2 -> user,pass correct, user is of type SYSTEM
  int result = verifyDB(username,password);
 
//Username and/or password don't exist, redirecting to login_error.html 
  if (result == 0){
    
    const char * redirect_page_format =
      "<html>\n"
      "<head>\n"
      "<meta http-equiv=\"REFRESH\"\n"
      "content=\"0;url=%s\">\n"
      "</head>\n"
      "</html>\n";
    
    printf (redirect_page_format, "login_error.html");

  }

//Username, password verfied, user is of type USER, displaying USER menu
  else if (result == 1){
    printf("<html><head><title>USER MENU</title></head><body>\n");
    printf("<p>USER menu:</p>\n");
    printf("<form method=\"POST\" action=menu.cgi>\n");
    printf("<p>Select one of the following options:</p>\n");
    printf("<input type =\"radio\" name=\"option\" value=\"0\">Change Password<br>\n");
    printf("<input type =\"radio\" name=\"option\" value=\"1\">See your purchase history.<br>\n");
    printf("<a href=\"index.html\"> Go to home page</a><br>\n");
    printf("<input type =\"submit\" value=\"Submit!\"><br>\n");  
    printf("</form></body></html>\n");
  }


//Username, password verified, user is of type SYSTEM, displaying SYSTEM menu
  else{
    printf("<html><head><title>SYSTEM MENU</title></head><body>\n");
    printf("<p>SYSTEM menu:</p>\n");
    printf("<form method=\"POST\" action=menu.cgi>\n");
    printf("<p>Select one of the following options:</p>\n");
    printf("<input type =\"radio\" name=\"option\" value=\"2\">Access passweb.c<br>\n");
    printf("<input type =\"radio\" name=\"option\" value=\"3\">See inventory.<br>\n");
    printf("<a href=\"index.html\">Go to home page</a><br>\n");
    printf("<input type =\"submit\" value=\"Submit!\"><br>\n");  
    printf("</form></body></html>\n");
  }

}

//Function that checks members.csv file for username/password,
int verifyDB (char username[40], char password[40])
{

                FILE *fp;
                char arr[50][50];
                int usernameFound = 0;
                char *line = NULL;
                size_t len = 0;
                int counter = 0;
                ssize_t read;
                int userType;                
 
                fp = fopen("members.csv","r");

                //copy file contents, line by line, into arr
                while( (read = getline(&line,&len,fp)) != -1  && counter < 50 )
                {
                  strcpy(arr[counter],line);
                  counter++;
                }
                
                //check each line of arr if username, password present
                for (int i = 0; i < 50; i ++)
                {
                        char *c;
                        char *d;

                        c = strstr(arr[i],username);
                        d = strstr(arr[i],password);

                        if (c != NULL && d != NULL){
                               
                            usernameFound = 1;
                            
                            if (strstr(arr[i],"SYSTEM"))
                              userType = 1;

                            else userType = 0;                    
                        }

                }

                fclose(fp);

                if (usernameFound ==  0)
                        return 0;

                //Will return 1 if user type is "USER" or 2 if user type is "SYSTEM"
                else 
                  return usernameFound + userType;
}


