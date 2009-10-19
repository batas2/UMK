#include<stdlib.h>
#include<stdio.h>
#include<pwd.h>
#include<sys/types.h>

int main(int argc, char *argv[])
{
	if(argc > 1){
		struct passwd *moj_passwd; //Deklaruje wskaznik na strukture passwd 
		moj_passwd = getpwnam(argv[1]); //Pobieram dane uzytkownia 
		printf("Imie Nazwisko: %s\nSHELL: %s\nGID: %d\nUID: %d\n", 
				moj_passwd->pw_gecos, moj_passwd->pw_shell, 
				moj_passwd->pw_gid, moj_passwd->pw_uid);
	}else{
		printf("Podaj jako pierwszy argument nazwe uzytokwnia.\n");
	}
}
