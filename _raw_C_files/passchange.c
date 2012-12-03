//passchange.cgi : code to execute password change option (essentially
//some processing and a system() call to passweb_store 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

int main(){

  printf("Content-type: text/html\n\n");

  //Most of this code just stores the username, old password, new password entered in html form
  //in variables username, oldpass, newpass

  char c;
  int i = 0;
  int j = 0;
  char input[200];
  char username[40] = {0};
  char oldpass[40] = {0};
  char newpass[40] = {0};
  char command[100] = {0};

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

  while ((c = input[i]) != '&'){
    oldpass[j] = c;
    i++;
    j++;
  }

  oldpass[j] = '\0';

  j = 0;

  while ((c = input[i]) != '='){
    i++;
  }

  i++;

  while ((c = input[i]) != EOF && i < length){
    newpass[j] = c;
    i++;
    j++;
  }

  newpass[j] = '\0'; 

  //Now, call system() with info to change password, print result on html page.

  strcat(command, "./passweb_store -edit ");
  strcat(command, username);
  strcat(command," ");
  strcat(command, oldpass);
  strcat(command," USER ");
  strcat(command, username);
  strcat(command, " ");
  strcat(command, newpass);
  strcat(command," USER");

  int log = system(command);

  printf("<head><title>Success</title></head><body>");
  printf("Your password was successfully changed<br>");
  printf("<a href=\"../home.html\">Home</a>   ");
  printf("<a href=\"javascript: window.history.go(-2)\">Go back to menu.</a>");
  printf("</body></html>");

}
