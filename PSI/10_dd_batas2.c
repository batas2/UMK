#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

/*
 * Zmienne globalne oznaczajace czy zatrzymac kopiowanie 
 * oraz czy wyswietlic postepo
 */
int _stop = 0, _list = 0; 

/*
 * funkcja wywolana po otrzymaniu sygnalu SIGUSR1
 */
void list(int v)
{

	_list = 1;
	signal(SIGUSR1, list);
}

/*
 * funkcja wywolywana po otrzymaniu sygnalu SUGUSR2
 */
void stop(int v)
{
	_stop = 1;
}

/*
 * Funkcj kopiujaca plik uzywajaca strumieni danych
 */
int copy(const char *src_path, const char *dest_path,
	 const int block_count, const int block_size)
{

	FILE	*src_file, *dest_file;
	int	i = 0;
	char	*buf;
	
	src_file	= fopen(src_path, "r"); //Otwieram strumien do czytania
	dest_file	= fopen(dest_path, "w"); //Otwieram strumien do pisania
	buf		= (char *)malloc(sizeof(char) * block_size); //blok danych

	while( !feof(src_file) && (i++ < block_count) && !_stop ){
		fread(buf, sizeof(char), block_size, src_file); //czytam blok danych
		fwrite(buf, sizeof(char), block_size, dest_file); //pisze blok danych
		if(_list){
			printf("Przeslano: %dB\n", i * block_size);
			_list = 0;
		}
//		sleep(2);
	}
	
	fflush(dest_file); //Tak na wszelki wypadek bufor strumienia zapisuje do pliku
	
	fclose(src_file);
	fclose(dest_file);
	
	if(_stop){
		remove(dest_path); //usuwam plik
	}
			
}
/*
 * Autor: Bartosz Fr¹ckowiak
 * wwww:  http://www.batas2.boo.pl/
 */
int main(int argc, char *argv[])
{
	int	block_count = 0, block_size = 0;

	if(argc == 5){
		block_count = atoi(argv[3]);
		block_size = atoi(argv[4]);

		//rejestruje funkcje do przechwytywania sygnalow
		signal(SIGUSR1, list); 
		signal(SIGUSR2, stop);

		copy(argv[1], argv[2], block_count, block_size);
	}else{
		printf("Nie poprawne parametry!\nmojedd plik_wej plik_wyj ilosc_blokow rozmiar_bloku\n");
	}
}
