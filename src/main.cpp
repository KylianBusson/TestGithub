#include <Arduino.h>

#define Vmes 32

// tableau des valeurs pour la correction 
float tab_mesures_reelles[34] = {
  0,0,104,321,341,463,580,704,822,948,1083,1198,1325,1434,1591,1703,1833,1971,2082,2177,
  2292,2415,2553,2655,2801,2926,3069,3202,3390,3606,3847,4090,4095,4095};

float tab_mesures_theoriques[34] = 
{0.000, 124.091, 248.182, 372.273, 496.364, 620.455, 744.545, 868.636, 992.727,1116.818, 
1240.909, 1365.000, 1489.091, 1613.182, 1737.273, 1861.364, 1985.455, 2109.545, 2233.636, 
2357.727, 2481.818,2605.909, 2730.000, 2854.091, 2978.182, 3102.273, 3226.364, 3350.455, 
3474.545, 3598.636, 3722.727, 3846.818, 3970.909, 4095.000};

float tab_mesures_corrigees[4096];

int Nreel;
float Ncorrige;
int Rmes;


void monADC_init();

void setup() 
{
   Serial.begin(115200);
   monADC_init();
   pinMode(Vmes,INPUT);
 
}

void loop() 
{
  Rmes =  3.3 /analogRead(Vmes) - 1 ;
  Rmes =  1000 / Rmes ;
  Serial.println(Rmes);
  delay(1000);
  Serial.println(Vmes);
  delay(1000);

}

void monADC_init()
{
  int i;                      // variable de boucle pour tab_mesures_corrigées
  int j;                      // variable de boucle pour tab_mesures_reelles et tab_mesures_theo

  tab_mesures_corrigees[0] = 0;
  tab_mesures_corrigees[4095] = 4095;

  // trouver la 1ère valeur non nulle de tab_mesures_reelles
  j = 0;
  while (tab_mesures_reelles[j] == 0)
  {
    j++;
  }
 //générer le 1er tronçon

  for (i = 0; i < tab_mesures_reelles[j]; i++)
  {
    tab_mesures_corrigees[i] = tab_mesures_theoriques[j] * i / tab_mesures_reelles[j];
  }
 // générer les tronçons suivants
  for (j = j + 1; j < 33; j++)
  {

    for (i; i < tab_mesures_reelles[j]; i++)
    {
      tab_mesures_corrigees[i] = (tab_mesures_theoriques[j] - tab_mesures_theoriques[j - 1]) * (i - tab_mesures_reelles[j - 1]) / (tab_mesures_reelles[j] - tab_mesures_reelles[j - 1]) + tab_mesures_theoriques[j - 1];
    }
  }
}