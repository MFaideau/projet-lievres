#define MASTER 0x00   
#define SIMUL 0x01    
#define SYNOP 0x02   
#define BROADCAST 0xff   //Permet d'envoyer à toutes les cartes du réseau
#define PROD  0x10       //Puissance délivrée par le coeur en KW
#define TEMP1 0x11       //Température du Circuit Primaire en °C
#define VOL1 0x12        //Volume contenu dans le Circuit Primaire en m^3
#define SEC1 0x13        //Diamètre  du tuyau du Circuit Primaire en cm
#define ECH1 0x14        //Coefficient d'échange primaire - secondaire en %
#define RPM1 0x15        //Vitesse de la pompe du Circuit Primaire
#define PRES1 0x16       //Pression d'eau du circuit primaire en bar
#define CONSO 0x20       //Consommation électrique en KW (ce qui sort)
#define TEMP2 0x21       //Température du Circuit Secondaire en °C
#define VOL2 0x22        //Volume contenu dans le Circuit Secondaire en m^3
#define SEC2 0x23        //Diamètre  du tuyau du Circuit Secondaire en cm
#define ECH2 0x24        //Coefficient d'échange secondaire - tertiaire en %
#define RPM2 0x25        //Vitesse de la pompe du Circuit Secondaire 
#define TEMP3 0x31       //Température du Circuit Tertiaire en °C
#define VOL3 0x32        //Volume contenu dans le Circuit Tertiaire en m^3
#define SEC3 0x33        //Diamètre  du tuyau du Circuit Tertiaire en cm
#define ECH3 0x34        //Coefficient d'échange tertiaire - air en %
#define RPM3 0x35        //Vitesse de la pompe du Circuit Tertiaire
#define POWER 0x0F       //Consommation Electrique Voulue  
#define duree_bit 1      //
#define gap_octet 5      //
#define START LOW        //
#define STOP HIGH        //
#define DEBUG 1          //




