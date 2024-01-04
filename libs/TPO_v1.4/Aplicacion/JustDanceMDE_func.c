/*
 * MDE_funciones.c
 *
 *  Created on: 11 oct. 2021
 *      Author: d_lugano
 */

#include "JustDanceMDE_func.h"
#include "Systick.h"

int32_t points=0;
uint8_t flagGameOver=0;
uint8_t flagEscape=0;
uint8_t flagDatos=0;

Canciones cancionero[2];
Paso pasos0[CANT_PASOS0];
Paso pasos1[CANT_PASOS1];

void Puntaje(uint32_t counter, uint32_t timestap , uint32_t dificultad )
{
	//Legend  	counter=timestap
	//Perfect  	+-0.05*dificultad
	//Good  	+-0.1*dificultad
	//Regular 	+-0.2*dificultad
	//Bad		-20

	if ( ( (timestap-dificultad*0.05) <= counter ) && ( (timestap + dificultad*0.05) >= counter) )
	{
		points+=100;
	}
	else if( ( (timestap-dificultad*0.1) <= counter ) && ( (timestap + dificultad*0.1) >= counter) )
	{
		points+=50;
	}
	else if( ( (timestap-dificultad*0.2) <= counter ) && ( (timestap + dificultad*0.2) >= counter) )
	{
		points+=20;
	}
	else
	{
		points+=0;
	}
}

void Puntaje_restar(uint8_t paso, uint8_t cant)
{
	points-=20;

	if(points<0)
		points=0;

	if( cant*70 >  (points+ (cant-paso)*100 ) )
	{
		flagGameOver=1;
	}
}

void EnviarStart(void)
{
	uint8_t buffer1[20]="AT+CIPSEND=1,6\r\n";
	uint8_t buffer2[10]="@ ST #";

	TxSerie1((uint8_t *)buffer1);

	while(flagRx!=1);

	TxSerie1((uint8_t *)buffer2);

	while(flagTx!=1);
}

void EnviarSelect(void)
{
	uint8_t buffer1[20]="AT+CIPSEND=1,6\r\n";
	uint8_t buffer2[10]="@ SE #";

	TxSerie1((uint8_t *)buffer1);

	while(flagRx!=1);

	TxSerie1((uint8_t *)buffer2);

	while(flagTx!=1);
}

void EnviarPuntaje(int32_t puntaje)
{
	uint8_t buffer1[20]="AT+CIPSEND=1,";
	uint8_t buffer2[20], buf_aux1[10], buf_aux2[10], buf_aux2_1[10], buf_aux1_1[10], i=0, len2=0, len1=0;
	uint32_t aux=0;

	buffer2[0]='&';
	buffer2[1]=' ';
	buffer2[2]='\0';

	if(puntaje != 0)
	{
		for(i=0, aux=puntaje ; aux>0; i++)
		{
			buf_aux2[i]=(aux%10) +48 ;
			aux/=10;
		}
		buf_aux2[i]='\0';
		my_revstr(buf_aux2, buf_aux2_1);
		my_strcat(buffer2, buf_aux2_1);
	}
	else
	{
		buffer2[2]=48;
		buffer2[3]='\0';
	}

	len2=my_strlen(buffer2);

	buffer2[len2++]=' ';
	buffer2[len2++]='@';
	buffer2[len2]='\0';	//El null no cuenta como el largo pero tiene que estar


	for(i=0, aux=len2; aux>0; i++)
	{
		buf_aux1[i]=(aux%10) +48 ;
		aux/=10;
	}

	my_revstr(buf_aux1, buf_aux1_1);
	my_strcat(buffer1, buf_aux1_1);
	len1=my_strlen(buffer1);
	buffer1[len1++]='\r';
	buffer1[len1++]='\n';
	buffer1[len1]='\0';

	TxSerie1(buffer1);

	while(flagRx!=1);

	TxSerie1(buffer2);

	while(flagTx!=1);
}

void EnviarDatos(uint8_t key, uint32_t timestap)
{
	uint8_t buffer1[20]="AT+CIPSEND=1,";
	uint8_t buffer2[20], buf_aux1[10], buf_aux2[10], buf_aux2_1[10], buf_aux1_1[10], i=0, len2=0, len1=0;
	uint32_t aux=0, aux1=0;

	buffer2[0]='#';
	buffer2[1]=' ';
	buffer2[2]=key+48;
	buffer2[3]=' ';
	buffer2[4]='\0';

	for(i=0, aux=timestap ; aux>0; i++)
	{
		buf_aux2[i]=(aux%10) +48 ;
		aux/=10;
	}
	buf_aux2[i]='\0';

	my_revstr(buf_aux2, buf_aux2_1);
	my_strcat(buffer2, buf_aux2_1);
	len2=my_strlen(buffer2);

	buffer2[len2++]=' ';
	buffer2[len2++]='@';
	buffer2[len2]='\0';	//El null no cuenta como el largo pero tiene que estar


	for(i=0, aux=len2; aux>0; i++)
	{
		buf_aux1[i]=(aux%10) +48 ;
		aux/=10;
	}

	my_revstr(buf_aux1, buf_aux1_1);
	my_strcat(buffer1, buf_aux1_1);
	len1=my_strlen(buffer1);
	buffer1[len1++]='\r';
	buffer1[len1++]='\n';
	buffer1[len1]='\0';

	TxSerie1(buffer1);

	while(flagRx!=1);

	TxSerie1(buffer2);

	while(flagTx!=1);
}

void InitMusica(void)
{
	cancionero[0].largo=34000;
	cancionero[0].cant=CANT_PASOS0;
	InitCancion0(pasos0);
	cancionero[0].paso=pasos0;

	cancionero[1].largo=98000;
	cancionero[1].cant=CANT_PASOS1;
	InitCancion1(pasos1);
	cancionero[1].paso=pasos1;
}

void InitCancion0( Paso* steps)
{
	steps[0].timestap=1000;
	steps[0].tecla=RIGHT_ARROW;

	steps[1].timestap=2000;
	steps[1].tecla=DOWN_ARROW;

	steps[2].timestap=3000;
	steps[2].tecla=LEFT_ARROW;

	steps[3].timestap=4000;
	steps[3].tecla=UP_ARROW;

	steps[4].timestap=5000;
	steps[4].tecla=RIGHT_ARROW;

	steps[5].timestap=6000;
	steps[5].tecla=DOWN_ARROW;

	steps[6].timestap=7000;
	steps[6].tecla=LEFT_ARROW;

	steps[7].timestap=8000;
	steps[7].tecla=UP_ARROW;

	steps[8].timestap=9000;
	steps[8].tecla=RIGHT_ARROW;

	steps[9].timestap=10000;
	steps[9].tecla=DOWN_ARROW;

	steps[10].timestap=11000;
	steps[10].tecla=LEFT_ARROW;

	steps[11].timestap=12000;
	steps[11].tecla=UP_ARROW;

	steps[12].timestap=13000;
	steps[12].tecla=RIGHT_ARROW;

	steps[13].timestap=14000;
	steps[13].tecla=DOWN_ARROW;

	steps[14].timestap=15000;
	steps[14].tecla=LEFT_ARROW;

	steps[15].timestap=16000;
	steps[15].tecla=UP_ARROW;

	steps[16].timestap=17000;
	steps[16].tecla=RIGHT_ARROW;

	steps[17].timestap=18000;
	steps[17].tecla=DOWN_ARROW;

	steps[18].timestap=19000;
	steps[18].tecla=LEFT_ARROW;

	steps[19].timestap=20000;
	steps[19].tecla=UP_ARROW;

	steps[20].timestap=21000;
	steps[20].tecla=RIGHT_ARROW;

	steps[21].timestap=22000;
	steps[21].tecla=DOWN_ARROW;

	steps[22].timestap=23000;
	steps[22].tecla=LEFT_ARROW;

	steps[23].timestap=24000;
	steps[23].tecla=UP_ARROW;

	steps[24].timestap=25000;
	steps[24].tecla=RIGHT_ARROW;

	steps[25].timestap=26000;
	steps[25].tecla=DOWN_ARROW;

	steps[26].timestap=27000;
	steps[26].tecla=LEFT_ARROW;

	steps[27].timestap=28000;
	steps[27].tecla=UP_ARROW;

	steps[28].timestap=29000;
	steps[28].tecla=RIGHT_ARROW;

	steps[29].timestap=30000;
	steps[29].tecla=DOWN_ARROW;

	steps[30].timestap=31000;
	steps[30].tecla=LEFT_ARROW;

	steps[31].timestap=32000;
	steps[31].tecla=UP_ARROW;

}

void InitCancion1( Paso* steps)
{
	steps[0].timestap=4000;
	steps[0].tecla=RIGHT_ARROW;

	steps[1].timestap=5000;
	steps[1].tecla=DOWN_ARROW;

	steps[2].timestap=6000;
	steps[2].tecla=LEFT_ARROW;

	steps[3].timestap=7000;
	steps[3].tecla=UP_ARROW;

	steps[4].timestap=8000;
	steps[4].tecla=DOWN_ARROW;

	steps[5].timestap=9000;
	steps[5].tecla=UP_ARROW;

	steps[6].timestap=10000;
	steps[6].tecla=RIGHT_ARROW;

	steps[7].timestap=11000;
	steps[7].tecla=LEFT_ARROW;

	steps[8].timestap=12000;
	steps[8].tecla=RIGHT_ARROW;

	steps[9].timestap=13000;
	steps[9].tecla=RIGHT_ARROW;

	steps[10].timestap=14000;
	steps[10].tecla=UP_ARROW;

	steps[11].timestap=15000;
	steps[11].tecla=LEFT_ARROW;

	steps[12].timestap=16000;
	steps[12].tecla=DOWN_ARROW;

	steps[13].timestap=17000;
	steps[13].tecla=LEFT_ARROW;

	steps[14].timestap=18000;
	steps[14].tecla=RIGHT_ARROW;

	steps[15].timestap=19000;
	steps[15].tecla=DOWN_ARROW;

	steps[16].timestap=20000;
	steps[16].tecla=LEFT_ARROW;

	steps[17].timestap=21000;
	steps[17].tecla=UP_ARROW;

	steps[18].timestap=22000;
	steps[18].tecla=DOWN_ARROW;

	steps[19].timestap=23000;
	steps[19].tecla=RIGHT_ARROW;

	steps[20].timestap=24000;
	steps[20].tecla=RIGHT_ARROW;

	steps[21].timestap=25000;
	steps[21].tecla=UP_ARROW;

	steps[22].timestap=26000;
	steps[22].tecla=RIGHT_ARROW;

	steps[23].timestap=27000;
	steps[23].tecla=DOWN_ARROW;

	steps[24].timestap=27700;
	steps[24].tecla=DOWN_ARROW;

	steps[25].timestap=28400;
	steps[25].tecla=LEFT_ARROW;

	steps[26].timestap=28900;
	steps[26].tecla=LEFT_ARROW;

	steps[27].timestap=30000;
	steps[27].tecla=UP_ARROW;

	steps[28].timestap=34000;
	steps[28].tecla=DOWN_ARROW;

	steps[29].timestap=34800;
	steps[29].tecla=DOWN_ARROW;

	steps[30].timestap=35600;
	steps[30].tecla=DOWN_ARROW;

	steps[31].timestap=36400;
	steps[31].tecla=DOWN_ARROW;

	steps[32].timestap=37200;
	steps[32].tecla=DOWN_ARROW;

	steps[33].timestap=38000;
	steps[33].tecla=DOWN_ARROW;

	steps[34].timestap=39000;
	steps[34].tecla=RIGHT_ARROW;

	steps[35].timestap=40000;
	steps[35].tecla=LEFT_ARROW;

	steps[36].timestap=41000;
	steps[36].tecla=RIGHT_ARROW;

	steps[37].timestap=42000;
	steps[37].tecla=LEFT_ARROW;

	steps[38].timestap=42800;
	steps[38].tecla=DOWN_ARROW;

	steps[39].timestap=43600;
	steps[39].tecla=LEFT_ARROW;

	steps[40].timestap=44400;
	steps[40].tecla=UP_ARROW;

	steps[41].timestap=45200;
	steps[41].tecla=UP_ARROW;

	steps[42].timestap=46000;
	steps[42].tecla=LEFT_ARROW;

	steps[43].timestap=47000;
	steps[43].tecla=DOWN_ARROW;

	steps[44].timestap=48000;
	steps[44].tecla=DOWN_ARROW;

	steps[45].timestap=50000;
	steps[45].tecla=UP_ARROW;

	steps[46].timestap=50800;
	steps[46].tecla=UP_ARROW;

	steps[47].timestap=51600;
	steps[47].tecla=UP_ARROW;

	steps[48].timestap=52400;
	steps[48].tecla=UP_ARROW;

	steps[49].timestap=53200;
	steps[49].tecla=UP_ARROW;

	steps[50].timestap=54000;
	steps[50].tecla=UP_ARROW;

	steps[51].timestap=55000;
	steps[51].tecla=RIGHT_ARROW;

	steps[52].timestap=56000;
	steps[52].tecla=LEFT_ARROW;

	steps[53].timestap=57000;
	steps[53].tecla=RIGHT_ARROW;

	steps[54].timestap=58000;
	steps[54].tecla=LEFT_ARROW;

	steps[55].timestap=58800;
	steps[55].tecla=DOWN_ARROW;

	steps[56].timestap=59600;
	steps[56].tecla=LEFT_ARROW;

	steps[57].timestap=60400;
	steps[57].tecla=UP_ARROW;

	steps[58].timestap=61200;
	steps[58].tecla=LEFT_ARROW;

	steps[59].timestap=63000;
	steps[59].tecla=DOWN_ARROW;

	steps[60].timestap=66000;
	steps[60].tecla=RIGHT_ARROW;

	steps[61].timestap=67000;
	steps[61].tecla=LEFT_ARROW;

	steps[62].timestap=68000;
	steps[62].tecla=DOWN_ARROW;

	steps[63].timestap=69000;
	steps[63].tecla=UP_ARROW;

	steps[64].timestap=70000;
	steps[64].tecla=UP_ARROW;

	steps[65].timestap=71000;
	steps[65].tecla=DOWN_ARROW;

	steps[66].timestap=72000;
	steps[66].tecla=LEFT_ARROW;

	steps[67].timestap=73000;
	steps[67].tecla=RIGHT_ARROW;

	steps[68].timestap=74000;
	steps[68].tecla=RIGHT_ARROW;

	steps[69].timestap=75000;
	steps[69].tecla=RIGHT_ARROW;

	steps[70].timestap=76000;
	steps[70].tecla=LEFT_ARROW;

	steps[71].timestap=77000;
	steps[71].tecla=UP_ARROW;

	steps[72].timestap=78000;
	steps[72].tecla=LEFT_ARROW;

	steps[73].timestap=79000;
	steps[73].tecla=DOWN_ARROW;

	steps[74].timestap=79700;
	steps[74].tecla=UP_ARROW;

	steps[75].timestap=80500;
	steps[75].tecla=DOWN_ARROW;

	steps[76].timestap=81200;
	steps[76].tecla=DOWN_ARROW;

	steps[77].timestap=82000;
	steps[77].tecla=UP_ARROW;

	steps[78].timestap=83000;
	steps[78].tecla=RIGHT_ARROW;

	steps[79].timestap=83800;
	steps[79].tecla=RIGHT_ARROW;

	steps[80].timestap=84600;
	steps[80].tecla=DOWN_ARROW;

	steps[81].timestap=85400;
	steps[81].tecla=DOWN_ARROW;

	steps[82].timestap=86200;
	steps[82].tecla=LEFT_ARROW;

	steps[83].timestap=87000;
	steps[83].tecla=RIGHT_ARROW;

	steps[84].timestap=87800;
	steps[84].tecla=UP_ARROW;

	steps[85].timestap=88600;
	steps[85].tecla=UP_ARROW;

	steps[86].timestap=89400;
	steps[86].tecla=LEFT_ARROW;

	steps[87].timestap=90200;
	steps[87].tecla=LEFT_ARROW;

	steps[88].timestap=91000;
	steps[88].tecla=RIGHT_ARROW;

	steps[89].timestap=91800;
	steps[89].tecla=RIGHT_ARROW;

	steps[90].timestap=92600;
	steps[90].tecla=LEFT_ARROW;

	steps[91].timestap=93400;
	steps[91].tecla=DOWN_ARROW;

	steps[92].timestap=94200;
	steps[92].tecla=LEFT_ARROW;

	steps[93].timestap=95000;
	steps[93].tecla=DOWN_ARROW;

	steps[94].timestap=96000;
	steps[94].tecla=LEFT_ARROW;

	steps[95].timestap=97000;
	steps[95].tecla=LEFT_ARROW;
}
