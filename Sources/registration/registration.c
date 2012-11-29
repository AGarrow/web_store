/* 
 * Version: 1.0
 * Created: 28/12/2012
 * Purpose: Allow an user to register for the website for the last assignement of comp 206.
 * Inputs: The query from the website containing the username, password, firstname and lastname as entered by the user in the CGI form.
 * Outputs: Either redirect the user back to the registration page with an error message or to the login page with a successful message (and the .csv file updated with his information).
 * Notes: 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 100
#define QUERYBUFFER 1024

char firstname[BUFFER];
char lastname[BUFFER];
char username[BUFFER];
char pwd[BUFFER];

char queryuncoded[QUERYBUFFER];

int getquery(void){

	int i, j;
	int querylength = atoi(getenv("CONTENT_LENGTH"));
	
	if(QUERYBUFFER < querylength+1){
		printf("Internal Error: Query is overflowing the buffer...\n");
		return -1;
	}
	
	char query[querylength+1];
	char c;
	
	for(i = 0; (c = getchar()) != EOF && i <= querylength; ++i)
		query[i] = c;
	
	query[i] = '\0';
	
	for(i = 0, j = 0; query[i] != '\0'; ++i, ++j){
		
		if(query[i] == '+')
			queryuncoded[j] = ' ';
			
		else if(query[i] == '%'){
			
			int code;
			
			if(sscanf(&query[i+1], "%2x", &code) != 1) /*The idea come from the textbook p.160.*/
				code = '?';

			queryuncoded[j] = code;
			i += 2;
			
		}
		
		else
			queryuncoded[j] = query[i];
			
	}
			
	queryuncoded[j] = '\0';
	
	return 0;
	
}

int dividequery_registration(void){
	
	int j, i = 0;
	char temp[BUFFER];
	
	while(queryuncoded[i] != '\0'){
		
		j = 0;
		while(queryuncoded[i] != '=' && queryuncoded[i] != '\0'){
			temp[j++] = queryuncoded[i];
			++i;
		}
		temp[j] = '\0';
		++i;
		
		if(strcmp("pwd", temp) == 0){
			j = 0;
			while(queryuncoded[i] != '&' && queryuncoded[i] != '\0'){
				pwd[j++] = queryuncoded[i];
				++i;
			}
			++i;
		}
		
		else if(strcmp("username", temp) == 0){
			j = 0;
			while(queryuncoded[i] != '&' && queryuncoded[i] != '\0'){
				username[j++] = queryuncoded[i];
				++i;
			}
			++i;
		}
		
		else if(strcmp("firstname", temp) == 0){
			j = 0;
			while(queryuncoded[i] != '&' && queryuncoded[i] != '\0'){
				firstname[j++] = queryuncoded[i];
				++i;
			}
			++i;
		}
		
		else if(strcmp("lastname", temp) == 0){
			j = 0;
			while(queryuncoded[i] != '&' && queryuncoded[i] != '\0'){
				lastname[j++] = queryuncoded[i];
				++i;
			}
			++i;
		}
		
		else{
			printf("<html><body>Internal Error: Variable received not understood...</body></html>\n");
			return -1;
		}
		
	}
	
	return 0;
		
}

int main(void){

	printf("%s%c%c\n", "Content-Type:text/html; charset= iso-8859-1", 13, 10);

	char request[BUFFER*5] = "\0";

	int return_system;
	int check;

	check = getquery();
	
	if(check != 0)
		return -1;
		
	check = dividequery_registration();
	
	if(check != 0)
		return -1;

	strcat(request, "./passweb.cgi -add ");
	strcat(request, username);
	strcat(request, " ");
	strcat(request, pwd);
	strcat(request, " ");
	strcat(request, "user");

	return_system = system(request);
		
	if(return_system == 0){
		printf("<html><head><meta http-equiv=\"refresh\" content=\"1; url=http://www.cs.mcgill.ca/~agarro/login.html\"></head><body> You will be redirected... If not click <a href=\"http://www.cs.mcgill.ca/~agarro/login.html\">here</a>...</body></html>");
		return 0;
	}

	else{
		printf("<html><head><meta http-equiv=\"refresh\" content=\"1; url=http://www.cs.mcgill.ca/~agarro/register_failed.html\"></head><body> You will be redirected... If not click <a href=\"http://www.cs.mcgill.ca/~agarro/register_failed.html\">here</a>...</body></html>");
		return -1;
	}

}
