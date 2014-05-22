#include "stdafx.h"
#include "xstring.h"

// helper
char is_file(char *file_name)
{
	if(file_name==NULL || esta_vacio(file_name))
		return 0;

	FILE *fp;
	char rta=1;
	if((fp=fopen(file_name,"rt"))==NULL)
		rta=0;
	else
		fclose(fp);
	return(rta); 
}

// devuelve TRUE si el string esta vacio,
// es decir si es "", o bien solo tiene espacios
bool esta_vacio(char *s)
{
	bool rta;
	if(s[0]==0)
		rta = true;		// se trata de ""
	else
		if(s[0]!=32)
			rta = false;	// no esta vacio
		else
		{
			// empieza en espacios, pero puede llegar a 
			// tener algo en el medio
			rta = true;		// supongo que esta vacio
			int i=0;
			while(s[i] && rta)
				if(s[i]!=32)
					rta = false;		// no esta vacio
				else
					++i;
		}
		return rta;
}

void extension(char *file,char *ext)
{
	int i=0;

	// Le saco la extension que tenia antes
	// si es que tiene extension
	char * pos = strchr(file, '.');

	if(ext && ext[0])
	{
		// Ahora no tiene mas extension, le agrego la nueva
		pos[0] = '.';
		strcpy(pos + 1, ext);
	}
	else {
		pos[0] = '\0';
	}
}

char *rtrim(char *string)
{
	int l=strlen(string)-1;
	while(l>=0 && (*(string+l)==' ' || *(string+l)=='\t'))
	{
		*(string+l)='\0';
		--l;
	}
	return(string);
}

char *ltrim(char *string)
{
	int l = strlen(string);
	char *buffer = new char[l+1];
	int i=0;
	while(string[i]==' ' || string[i]=='\t')
		++i;
	strcpy(buffer,string+i);
	strcpy(string,buffer);
	delete []buffer;
	return(string);
}

char *que_extension(char *file,char *ext)
{
	int t =0;
	// busco el punto (empiezando desde atras)
	char *p = strrchr(file,'.');
	if(p!=NULL)
	{
		// salteo el punto
		++p;
		while((*p)!=NULL)
			ext[t++] = *p++;
	}
	ext[t] = '\0';
	return ext;
}

