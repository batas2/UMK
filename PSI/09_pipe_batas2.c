#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

int main(){

	const int 	buf_size = 1;
	char		cmd_error[] = "Nie ma takiego polecenia!";
	int			pid = 0;
	
	/*
 	 * fd0 => Rodzic pisze, potomek czyta
 	 * fd1 => Rodzic czyta, potomek pisze
 	 */
	int		fd0[2], fd1[2];

	if(pipe(fd0) != 0){
		perror("Blad pipe: fd0");
	}

	if(pipe(fd1) != 0){
		perror("Blad pipe: fd1");
	}


	if( (pid = fork()) < 0){
		perror("Blad fork");
	}else{
		if(pid == 0){
			char	cmd[20];

			close(fd0[1]);
			close(fd1[0]);

			if( read(fd0[0], cmd, sizeof(cmd)) < 0){		//czytamy komende od rodzica
				perror("Blad wyslania polecenia przez rodzica!");
				exit(0);
			}else{
				dup2(fd1[1], fileno(stdout));  			//kopiuje deskryptor stdout na fd[1] i zamykam stdout
				execlp(cmd, cmd, NULL);
			
				write(fd1[1], cmd_error, strlen(cmd_error));
				exit(0);
			}

		}else{
			char	cmd[20];
			char	buf[buf_size];
			int		status = 0, f = 0;

			close(fd0[0]);
			close(fd1[1]);
			
			printf("Podaj polecenie: ");
			scanf("%s", cmd);
			printf("Wynik: \n");

			write(fd0[1], cmd, sizeof(cmd)); 		//pisze polecenie do potomka

			while( waitpid(pid, &status, WNOHANG) == 0){} 	//czekam az potomek sie skonczy

			f = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

			while( read(fd1[0], buf, buf_size) > 0 ){ 	//zczytuje wszystko co potomek napisal
				write(fileno(stdout), buf, buf_size); 	//wypisuje na stdout
				write(f, buf, buf_size);		//wypisuje do pliku
			}
			
			close(f);
			return 0;
		}
	}
}
