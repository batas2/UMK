#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>
#include<dirent.h>
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
/*
 * funkcja formatujaca czas z time_t na tablice char w formacie: %Y-%m-%d %H:%M:%S
 */
void format_time(time_t st_time, char *str);

/*
 * funkcje zwracajace odpowiednio sformatowane prawa dostepu jak i czasy plikow
 */
void get_mode(struct stat *moj_stat, char *mode);
void get_time(struct stat *moj_stat, char *atime, char *ctime, char *mtime);

/*
 * funkcje wyswietlajace informacje odpowiednio o pliku jak i o katalogu
 */
void info_file(const char *file_name);
void info_dir(const char *dir);

int main(int argc, char *argv[])
{
	argc > 1 ? info_file(argv[1]) : info_dir(".");
}


void info_file(const char *file_name)
{
	struct	stat *moj_stat = (struct stat *)malloc(sizeof(struct stat));
	int 	result;
	
	//funkcja stat zwraca w strukturze moj_stat informacje o pliku; result < 0 => blad
	result = stat(file_name, moj_stat);

	if(result < 0){
		perror("Blad funkcji stat");
	} else {
		//przydzielam pamiec zmiennym tymczasowym
		//odpowiedzialnym za czasy jak i prawa dostepu
		char *buf_atime = (char *)malloc(sizeof(char) * 17);	
		char *buf_ctime = (char *)malloc(sizeof(char) * 17);
		char *buf_mtime = (char *)malloc(sizeof(char) * 17);
		
		char *buf_mode = (char *)malloc(sizeof(char) * 10);
		
		//podbieram czas i prawa dostepu
		get_time(moj_stat, buf_atime, buf_ctime, buf_mtime);
		get_mode(moj_stat, buf_mode);
		
		//wyswietlanie
		printf("%s\t%d\t%ld\t%s\t%s\t%s\t%s\n", 
				buf_mode,  
			       	moj_stat->st_blksize, moj_stat->st_size,
				buf_atime, buf_ctime, buf_mtime, file_name);

		//zwalnianie pamieci
		free(buf_atime); free(buf_ctime); free(buf_mtime);
	}
	free(moj_stat); 
}

void info_dir(const char *dir)
{
	struct	dirent **name_list;
	int	n;
	
	//pobieram liste plikow katalogu biezacego; n - liczba plikow; n < 0 => blad
	n = scandir(dir, &name_list, 0, alphasort);

	if (n < 0){
		perror("Blad funkcji scandir");
	} else {
		int i;
		
		for(i = 0; i < n; i++){
			info_file(name_list[i]->d_name);
			free(name_list[i]);
		}
		free(name_list);
	}		
}

void format_time(time_t st_time, char *str)
{
	struct tm  *ts;
	
	ts = localtime(&st_time);
	strftime(str, sizeof(str) * 20, "%y/%m/%d %H:%M:%S", ts);
}

void get_mode(struct stat *moj_stat, char *mode)
{
	//Typ pliku
	mode[0] = 	moj_stat->st_mode & S_IFDIR ? 'd' : 
		  	moj_stat->st_mode & S_IFREG ? '-' :  
		  	moj_stat->st_mode & S_IFBLK ? 'b' : 
		  	moj_stat->st_mode & S_IFCHR ? 'c' : 
			moj_stat->st_mode & S_IFIFO ? 'p' : 
			moj_stat->st_mode & S_IFLNK ? 's' : '-';

 	//Prawa dostepu wlascicela
	mode[1] =	moj_stat->st_mode & S_IRUSR ? 'r' : '-';
	mode[2] =	moj_stat->st_mode & S_IWUSR ? 'w' : '-';
	mode[3] =	moj_stat->st_mode & S_IXUSR ? 'x' : '-';
	
	//Prawa dostepu grupy
	mode[4] =	moj_stat->st_mode & S_IRGRP ? 'r' : '-';
	mode[5] =	moj_stat->st_mode & S_IWGRP ? 'w' : '-';
	mode[6] =	moj_stat->st_mode & S_IXGRP ? 'x' : '-';
	
	//Prawa dostepu innych
	mode[7] =	moj_stat->st_mode & S_IROTH ? 'r' : '-';
	mode[8] =	moj_stat->st_mode & S_IWOTH ? 'w' : '-';
	mode[9] =	moj_stat->st_mode & S_IXOTH ? 'x' : '-';

	mode[10] =	'\0';
}

void get_time(struct stat *moj_stat, char *atime, char *ctime, char *mtime)
{
	format_time(moj_stat->st_atime, atime);
	format_time(moj_stat->st_ctime, ctime);
	format_time(moj_stat->st_mtime, mtime);
}
