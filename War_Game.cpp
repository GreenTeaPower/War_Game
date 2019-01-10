/****************************
****Autor : Michal Pessel****
****Zadanie : Bojova hra ****
****Kruzok :  RK 2		 ****
*****************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ZIVOTY 5
#define BOJOVNICI 5


typedef struct bojovnik											/*struktura bojovnika*/
{
	int pocet_zivotov;
	int utok;
	int obrana;

}BOJOVNIK;




typedef struct hrac												 /*struktura pre hraca*/
{
	struct bojovnik	bojovnik[5];

}HRAC;

HRAC hrac_1, hrac_2;


void param_bojovnika(BOJOVNIK *p_a);
void param_hraca(HRAC *p_b);
int boj(HRAC *hrac_1, int hrac_1_bojovnik, HRAC *hrac_2, int hrac_2_bojovnik);
void vypis_hraca(HRAC *hrac, int cislo_hraca);
void about();
int vyhodnotenie_hraca(HRAC *hrac);
int vyber_bojovnika(HRAC *hrac, int cislo_hraca);
int vitaz(HRAC *hrac);



int main()
{
	about();
	int i = 0;
	int poradie = 1;						/*urcenie poradia hracov pri boji, hrac1-neparne , hrac2-parne*/
	int hrac_1_c_b;							/*cislo vybraneho bojovnika hraca cislo 1*/
	int hrac_2_c_b;						    /*cislo vybraneho bojovnika hraca cislo 2*/
	int c_1_bojovnika = 0;					/*vyber bojovnika*/
	int c_2_bojovnika = 0;

	srand(time(0));							/*zaciatok random*/


	param_hraca(&hrac_1);					/*naplnenie parametrov hraca1*/
	param_hraca(&hrac_2);					/*naplnenie parametrov hraca2*/
	
	
	


	while (vyhodnotenie_hraca(&hrac_1) != 0 && vyhodnotenie_hraca(&hrac_2) != 0)					/*vykonavanie boja az kym jeden z hracov nedosiahne 0 zivotov vsetkych bojovnikov */
	{ 	 
		do
		{
			vyber_bojovnika(&hrac_1, 1);
			printf("Zadaj cislo vybraneho bojovnika z intervalu (0-4): \n");
			scanf_s("%i", &c_1_bojovnika);

			vyber_bojovnika(&hrac_2, 2);
			printf("Zadaj cislo vybraneho bojovnika z intervalu (0-4): \n");
			scanf_s("%i", &c_2_bojovnika);

			if ((c_1_bojovnika > 4) || (c_2_bojovnika > 4) || (c_1_bojovnika < 0) || (c_2_bojovnika < 0))
			{
				printf("NESPRAVNY VYBER HRACOV!!!!!\n");
			}
		} while ((c_1_bojovnika > 4) || (c_2_bojovnika > 4) || (c_1_bojovnika < 0) || (c_2_bojovnika < 0));
	
	
		while (hrac_1.bojovnik[c_1_bojovnika].pocet_zivotov != 0 && hrac_2.bojovnik[c_2_bojovnika].pocet_zivotov != 0)		/*priebeh boja medzi dvoma bojovnikmi hraca1 a hraca2*/
		{
			if ((poradie % 2) > 0)
			{
				boj(&hrac_1, c_1_bojovnika, &hrac_2, c_2_bojovnika);
			}
			else
			{
				boj(&hrac_2, c_2_bojovnika, &hrac_1, c_1_bojovnika);
			}
			poradie++;
		}
		vypis_hraca(&hrac_1, 1);																	/*zatial kontrolny vypis stavu bojovnikov jednotlivych hracov*/

		vypis_hraca(&hrac_2, 2);

		printf("Pocet zivotov hraca - 1: %i\n", vyhodnotenie_hraca(&hrac_1));
		printf("Pocet zivotov hraca - 2: %i\n", vyhodnotenie_hraca(&hrac_2));
		
	}
	vitaz(&hrac_1);
	vitaz(&hrac_2);
	return 0;
}

void param_bojovnika(BOJOVNIK *p_a)
{
	int k = 0;
	p_a->pocet_zivotov = ZIVOTY;		  /*pocet zivotov*/
	k = rand() % 5 + 1;
	while (k == 0 || k == 5)
	{
		k = rand() % 5 + 1;
	}
	p_a->utok = k;						 /*realizacia random utoku*/
	p_a->obrana = 5 - p_a->utok;		 /*obrana*/

}

void param_hraca(HRAC *p_b)										   /*parametre hraca*/
{
	BOJOVNIK pom;
	int i = 0;
	for (i = 0; i < BOJOVNICI; i++)
	{
		param_bojovnika(&pom);
		p_b->bojovnik[i] = pom;
	}
}

int boj(HRAC *hrac_1, int hrac_1_bojovnik, HRAC *hrac_2, int hrac_2_bojovnik)										   /*funkcia ktora realizuje boj medzi dvoma bojovnikmi*/
{
	int a;
	int utok_obrana;
	int status;
	utok_obrana = hrac_1->bojovnik[hrac_1_bojovnik].utok + hrac_2->bojovnik[hrac_2_bojovnik].obrana;
	//printf("utok + obrana %i\n", utok_obrana);
	a = rand() % utok_obrana + 1;
	//printf("A = %i\n", a);

	if (hrac_1->bojovnik[hrac_1_bojovnik].utok > a)
	{
		//printf("ZASAH\n");
		hrac_2->bojovnik[hrac_2_bojovnik].pocet_zivotov = hrac_2->bojovnik[hrac_2_bojovnik].pocet_zivotov - 1;
		status = 1;
	}
	else
	{
		//printf("MISS\n");
		status = 0;
	}

	return status;
}

void vypis_hraca(HRAC *hrac, int cislo_hraca)											 /*vypise stav hracov*/
{
	int i;
	printf("Hrac: *%i*\n", cislo_hraca);
	for (i = 0; i < BOJOVNICI; i++)
	{
		printf("Bojovnik: [%i] UTOK=%i, OBRANA=%i ZIVOT=*%i*\n", i, hrac->bojovnik[i].utok, hrac->bojovnik[i].obrana, hrac->bojovnik[i].pocet_zivotov);
															   
	}
}

int vyhodnotenie_hraca(HRAC *hrac)								/*vyhodnotenie hraca po boji , kolko zivotov mu zostava*/
{
	int zivot = 0;
	int i = 0;

	for (i = 0; i < BOJOVNICI; i++)
	{
		zivot = zivot + hrac->bojovnik[i].pocet_zivotov;
	}

	return zivot;
}

int vyber_bojovnika(HRAC *hrac, int cislo_hraca)										 /*funkcia na vyber bojovnika na zaciatku hry, ale aj pocas boja*/
{
	printf("###############################################################\n");
	printf("Hrac cislo %i ma na vyber nasledovnych bojovnikov:\n", cislo_hraca);
	vypis_hraca(hrac, cislo_hraca);
	printf("###############################################################\n");
	return 0;
}

void about()
{
	printf("##########################\n");
	printf("#Zadanie : Bojova Hra    #\n");
	printf("#Autor\t : Michal Pessel #\n");
	printf("#Kruzok\t : RK 2          #\n");
	printf("##########################\n");
}

int vitaz(HRAC *hrac)							  /*funkcia na vypisanie a urcenie vitaza na zaklade zivotov*/
{
	
	int i = 0;
	
	if (vyhodnotenie_hraca(&hrac_1) == 0)
	{
		printf("VYHRAL HRAC CISLO **2**\n");
	}
	else if (vyhodnotenie_hraca(&hrac_2) == 0)
	{
		printf("VYHRAL HRAC CISLO **1**\n");
	}
	
	return 0;
}