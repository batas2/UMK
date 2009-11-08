#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

int _stop = 0, _list = 0;

void list(int v)
{

	_list = 1;
	signal(SIGUSR1, list);
}

void stop(int v)
{
	_stop = 1;
}

int copy(const char *src_path, const char *dest_path,
	 const int block_count, const int block_size)
{

	FILE	*src_file, *dest_file;
	int	i = 0;
	char	*buf;
	
	src_file	= fopen(src_path, "r");
	dest_file	= fopen(dest_path, "w");
	buf		= (char *)malloc(sizeof(char) * block_size);

	while( !feof(src_file) && (i++ < block_count) && !_stop ){
		fread(buf, sizeof(char), sizeof(char) * block_size, src_file);
		fwrite(buf, sizeof(char), sizeof(char) * block_size, dest_file);
		if(_list){
			printf("Przeslano: %dB\n", i * block_size);
			_list = 0;
		}
//		sleep(2);
	}
	
	fflush(dest_file);
	
	fclose(src_file);
	fclose(dest_file);
	
	if(_stop){
		remove(dest_path);
	}
			
}

int main(int argc, char *argv[])
{
	int	block_count = 0, block_size = 0;

	block_count = atoi(argv[3]);
	block_size = atoi(argv[4]);

	signal(SIGUSR1, list);
	signal(SIGUSR2, stop);

	copy(argv[1], argv[2], block_count, block_size);
}
