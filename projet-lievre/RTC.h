void GetCurrentTime();

void wakeup_rtc() ;
void sleepNow()  ;

void setupRTC(int mfpPin, int annee, int mois, int date, int jourSem, int heures, int minutes, int secondes);
void startSleeping(int seconds) ;

