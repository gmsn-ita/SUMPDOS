#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "filipe.h"

int main(int argc, char *argv[])
{
FILE *dos,*dos1,*out,*dost,*eigenval;
double energia,efermi,b,d,up,down,lixo,ref;
int atom,natom,pts,i,j,k;
char ch;


printf("\n\n");
printf("------------------------------------------------------------------------------------------------------\n");
printf("PROGRAMA PARA SOMAR PDOS DOS ARQUIVOS DE SAÍDA DO PROGRAMA VASP.\n");
printf("Por Filipe Matusalem - Janeiro de 2014\n\n");


 if( argc < 2 ){
printf("\n\n");
printf("EEEEEEE   RRRRRRRR   RRRRRRRR   OOOOOOO   RRRRRRRR\n");
printf("EE        RR    RR   RR    RR   OO   OO   RR    RR\n");
printf("EE        RR    RR   RR    RR   OO   OO   RR    RR\n");
printf("EEEE      RRRRRRRR   RRRRRRRR   OO   OO   RRRRRRRR\n");
printf("EE        RRRR       RRRR       OO   OO   RRRR\n");
printf("EE        RR  RR     RR  RR     OO   OO   RR  RR\n");
printf("EEEEEEE   RR    RR   RR    RR   OOOOOOO   RR    RR\n\n");

printf("Enter the number of atom to sum as argument for the program! e.g. ./somapdos 001\n\n");
printf("A second argument, fermi, homo or lumo shift the origin to the Fermi, homo or lumo energy. e.g. ./somapdos 001 fermi  or ./somapdos 001 5.3247\n\n");
 exit(0);}


atom=atoi(argv[1]);

char str1[70] = "";
strcat(str1,argv[1]);

strcat(str1,".dat");
char str2[70] = "atom.";
strcat(str2,str1);


dos = fopen("DOSCAR","r"); /* Arquivo ASCII */
if(!dos)
{printf( "Erro na abertura do arquivo DOSCAR\n");
exit(0);
}

dos1 = fopen(str2,"w"); /* Arquivo ASCII */
if(!dos)
{printf( "Erro na criacao do arquivo atom.xxx.dat\n");
exit(0);
}

eigenval = fopen("EIGENVAL","r"); /* Arquivo ASCII */
if(!eigenval)
{
printf( "Erro na abertura do arquivo EIGENVAL\n");
exit(0);
}

dost = fopen("dost.dat","w"); /* Arquivo ASCII */
if(!dost)
{printf( "Erro na criacao do arquivo dost.dat\n");
exit(0);
}

fscanf(dos,"%d",&natom);

for(i=0;i<5;i++){
do
ch = getc(dos);              /*pula 5 linhas*/
while(ch!='\n');}


fscanf(dos,"%lf",&efermi);
fscanf(dos,"%lf",&efermi);
fscanf(dos,"%d",&pts);
fscanf(dos,"%lf",&efermi);



if(argc > 2){
if(strcmp(argv[2],"fermi")==0)ref=efermi;
else {if(strcmp(argv[2],"homo")==0)ref=homo(0); else {if(strcmp(argv[2],"lumo")==0)ref=lumo(0); else{ref=atof(argv[2]);}}}}

else {ref=0;}


do
ch = getc(dos);              /*pula 1 linhas*/
while(ch!='\n');


for(i=0;i<4;i++){
fscanf(eigenval,"%d",&k);}
fclose(eigenval);   
/*---with spin------------------------------------------------------*/

if(k==2){  

for(i=0;i<pts;i++){

fscanf(dos,"%lf",&energia);
fscanf(dos,"%lf",&up);
fscanf(dos,"%lf",&down);
do
ch = getc(dos);              /*pula 1 linhas*/
while(ch!='\n');

fprintf(dost,"%lf ",energia-ref);
fprintf(dost,"%.6lE %.6lE \n",up,down);

}

do
ch = getc(dos);              /*pula 1 linhas*/
while(ch!='\n');



for(i=1;i<atom;i++){
for(j=0;j<pts+1;j++){
do
ch = getc(dos);              /*pula 1 linhas*/
while(ch!='\n');
}
}

for(i=0;i<pts;i++){
fscanf(dos,"%lf",&energia);
fprintf(dos1,"%lf ",energia-ref);
for(j=0;j<18;j++){
fscanf(dos,"%lf",&energia);
fprintf(dos1,"%lE ",energia);}
fprintf(dos1,"\n");
}


fclose(dos);
fclose(dos1);
fclose(dost);

dos1 = fopen(str2,"r"); /* Arquivo ASCII, para leitura */
if(!dos1)
{printf( "Erro na abertura do arquivo atom.xxx.dat\n");
exit(0);
}

dost = fopen("dost.dat","r"); /* Arquivo ASCII, para leitura */
if(!dost)
{printf( "Erro na abertura do arquivo dost.dat\n");
exit(0);
}

strcpy(str1,"");
strcat(str1,argv[1]);
strcat(str1,".dat");
strcpy(str2,"soma-orbitais");
strcat(str2,str1);

out = fopen(str2,"w"); /* Arquivo ASCII, para escrita */
if(!out)
{
printf( "Erro na criacao do arquivo soma-orbitaisxxx.dat\n");
exit(0);
}

/*fprintf(out,"Energia(eV)  total-up      total-down   s-up          s-down       p-up          p-down       d-up          d-down\n");*/


for(j=0;j<pts;j++){
b=0;
d=0;

fscanf(dost,"%lf",&energia);
fscanf(dost,"%lf",&up);
fscanf(dost,"%lf",&down);

fprintf(out,"%lf ",energia);
fprintf(out,"%.6lE %.6lE ",up,-1*down);



fscanf(dos1,"%lf",&energia);
fscanf(dos1,"%lf",&up);
fscanf(dos1,"%lf",&down);
fprintf(out,"%.6lE %.6lE ",up,-1*down);


for(i=0;i<3;i++){
fscanf(dos1,"%lf",&up);
fscanf(dos1,"%lf",&down);
b=b+up;
d=d+down;}
fprintf(out,"%.6lE %.6lE ",b,-1*d);

b=0;
d=0;
for(i=0;i<5;i++){
fscanf(dos1,"%lf",&up);
fscanf(dos1,"%lf",&down);
b=b+up;
d=d+down;}
fprintf(out,"%.6lE %.6lE \n",b,-1*d);
}

}
/*---without spin------------------------------------------------------*/

else {

for(i=0;i<pts;i++){

fscanf(dos,"%lf",&energia);
fscanf(dos,"%lf",&up);

do
ch = getc(dos);              /*pula 1 linhas*/
while(ch!='\n');

fprintf(dost,"%lf ",energia-ref);
fprintf(dost,"%.6lE\n",up);

}

do
ch = getc(dos);              /*pula 1 linhas*/
while(ch!='\n');



for(i=1;i<atom;i++){
for(j=0;j<pts+1;j++){
do
ch = getc(dos);              /*pula  linhas*/
while(ch!='\n');
}
}

for(i=0;i<pts;i++){
fscanf(dos,"%lf",&energia);
fprintf(dos1,"%lf ",energia-ref);
for(j=0;j<9;j++){
fscanf(dos,"%lf",&energia);
fprintf(dos1,"%lE ",energia);}
fprintf(dos1,"\n");
}


fclose(dos);
fclose(dos1);
fclose(dost);   

dos1 = fopen(str2,"r"); /* Arquivo ASCII, para leitura */
if(!dos1)
{printf( "Erro na abertura do arquivo atom.xxx.dat\n");
exit(0);
}

dost = fopen("dost.dat","r"); /* Arquivo ASCII, para leitura */
if(!dost)
{printf( "Erro na abertura do arquivo dost.dat\n");
exit(0);
}


strcpy(str1,"");
strcat(str1,argv[1]);
strcat(str1,".dat");
strcpy(str2,"soma-orbitais");
strcat(str2,str1);

out = fopen(str2,"w"); /* Arquivo ASCII, para escrita */
if(!out)
{
printf( "Erro na criacao do arquivo soma-orbitaisxxx.dat\n");
exit(0);
}

/*fprintf(out,"Energia(eV)  total-up      total-down   s-up          s-down       p-up          p-down       d-up          d-down\n");*/


for(j=0;j<pts;j++){
b=0;
d=0;
fscanf(dost,"%lf",&energia);
fscanf(dost,"%lf",&up);


fprintf(out,"%lf ",energia);
fprintf(out,"%.6lE %.6lE ",up,-1*up);


fscanf(dos1,"%lf",&energia);
fscanf(dos1,"%lf",&up);
fprintf(out,"%.6lE %.6lE ",up,-1*up);


for(i=0;i<3;i++){
fscanf(dos1,"%lf",&up);
b=b+up;}
fprintf(out,"%.6lE %.6lE ",b,-1*b);

b=0;
d=0;
for(i=0;i<5;i++){
fscanf(dos1,"%lf",&up);
b=b+up;}
fprintf(out,"%.6lE %.6lE \n",b,-1*b);
}
}

fclose(dos1);
fclose(out);
fclose(dost);



/*elimina a primeira linha dos aquivos de dados


strcpy(str2,"");
sprintf(str2,"sed -i 1d atom.%s",str1);
system(str2);

/*printf("%s\n",str2);
strcpy(str2,"");
/*sprintf(str2,"sed -i 1d soma-orbitais%s",str1);
/*system(str2);
printf("%s\n",str2);
/*system("sed -i 1d dost.dat");


/*cria arquivo configurações xmgrace*/

dost = fopen("dos-grace.bfile","w"); /* Arquivo ASCII */
if(!dost)
{printf( "Erro na criacao do arquivo dos-grace.bfile\n");
exit(0);
}

fprintf(dost,"title font 14 \n");
fprintf(dost,"subtitle font 14  \n");
fprintf(dost,"legend font 14  \n");
fprintf(dost,"xaxis label font 14  \n");
fprintf(dost,"xaxis ticklabel font 14  \n");
fprintf(dost,"yaxis label font 14  \n");
fprintf(dost,"yaxis ticklabel font 14  \n");
fprintf(dost,"read block \"%s\" \n",str2);
fprintf(dost,"block xy \"1:2\" \n");
fprintf(dost,"s0 symbol 0 \n");
fprintf(dost,"s0 line type 1 \n");
fprintf(dost,"s0 line linestyle 1 \n");
fprintf(dost,"s0 line linewidth 1 \n");
fprintf(dost,"s0 line color 1 \n");
fprintf(dost,"s0 comment \"Total up\" \n");
fprintf(dost,"s0 legend  \"Total\" \n");
fprintf(dost,"block xy \"1:3\" \n");
fprintf(dost,"s1 symbol 0 \n");
fprintf(dost,"s1 line type 1 \n");
fprintf(dost,"s1 line linestyle 1 \n");
fprintf(dost,"s1 line linewidth 1 \n");
fprintf(dost,"s1 line color 1 \n");
fprintf(dost,"s1 comment \"Total down\" \n");
fprintf(dost,"s1 legend  \"\" \n");
fprintf(dost,"block xy \"1:4\" \n");
fprintf(dost,"s2 symbol 0 \n");
fprintf(dost,"s2 line type 1 \n");
fprintf(dost,"s2 line linestyle 1 \n");
fprintf(dost,"s2 line linewidth 1 \n");
fprintf(dost,"s2 line color 2 \n");
fprintf(dost,"s2 comment \"s up\" \n");
fprintf(dost,"s2 legend  \"s\" \n");
fprintf(dost,"block xy \"1:5\" \n");
fprintf(dost,"s3 symbol 0 \n");
fprintf(dost,"s3 line type 1 \n");
fprintf(dost,"s3 line linestyle 1 \n");
fprintf(dost,"s3 line linewidth 1 \n");
fprintf(dost,"s3 line color 2 \n");
fprintf(dost,"s3 comment \"s down\" \n");
fprintf(dost,"s3 legend  \"\" \n");
fprintf(dost,"block xy \"1:6\" \n");
fprintf(dost,"s4 symbol 0 \n");
fprintf(dost,"s4 line type 1 \n");
fprintf(dost,"s4 line linestyle 1 \n");
fprintf(dost,"s4 line linewidth 1 \n");
fprintf(dost,"s4 line color 3 \n");
fprintf(dost,"s4 comment \"p up\" \n");
fprintf(dost,"s4 legend  \"p\" \n");
fprintf(dost,"block xy \"1:7\" \n");
fprintf(dost,"s5 symbol 0 \n");
fprintf(dost,"s5 line type 1 \n");
fprintf(dost,"s5 line linestyle 1 \n");
fprintf(dost,"s5 line linewidth 1 \n");
fprintf(dost,"s5 line color 3 \n");
fprintf(dost,"s5 comment \"p down\" \n");
fprintf(dost,"s5 legend  \"\" \n");
fprintf(dost,"block xy \"1:8\" \n");
fprintf(dost,"s6 symbol 0 \n");
fprintf(dost,"s6 line type 1 \n");
fprintf(dost,"s6 line linestyle 1 \n");
fprintf(dost,"s6 line linewidth 1 \n");
fprintf(dost,"s6 line color 4 \n");
fprintf(dost,"s6 comment \"d up\" \n");
fprintf(dost,"s6 legend  \"d\" \n");
fprintf(dost,"block xy \"1:9\" \n");
fprintf(dost,"s7 symbol 0 \n");
fprintf(dost,"s7 line type 1 \n");
fprintf(dost,"s7 line linestyle 1 \n");
fprintf(dost,"s7 line linewidth 1 \n");
fprintf(dost,"s7 line color 4 \n");
fprintf(dost,"s7 comment \"d down\" \n");
fprintf(dost,"s7 legend  \"\" \n");
fprintf(dost,"world -10.000, -20.000, 20.000, 20.000 \n"); 
fprintf(dost,"yaxis  tick on  \n");
fprintf(dost,"yaxis  tick major 4  \n");
fprintf(dost,"yaxis  tick minor ticks 1  \n");
fprintf(dost,"yaxis  tick major size 1.000000 \n");
fprintf(dost,"yaxis  ticklabel char size 1.500000 \n");
fprintf(dost,"yaxis  label \"DOS (Arb. unit.)\" \n");
fprintf(dost,"yaxis  label font 14 \n");
fprintf(dost,"yaxis  label char size 1.500000 \n");
fprintf(dost,"xaxis  tick on  \n");
fprintf(dost,"xaxis  tick major 2  \n");
fprintf(dost,"xaxis  tick minor ticks 1  \n");
fprintf(dost,"xaxis  tick major size 1.000000 \n");
fprintf(dost,"xaxis  ticklabel char size 1.500000 \n");
fprintf(dost,"xaxis  label \"Energy (eV)\" \n");
fprintf(dost,"xaxis  label font 14 \n");
fprintf(dost,"xaxis  label char size 1.500000 \n");

fclose(dost);




/*plota xmgrace*/
strcpy(str1,"");
strcat(str1,argv[1]);

strcpy(str2,"");
sprintf(str2,"gracebat -param dos-grace.bfile -saveall pdos%s.agr -hdevice EPS",str1);
system(str2);


}
