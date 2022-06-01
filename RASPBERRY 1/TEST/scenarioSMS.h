class scenarioSMS{
  private :
  horaires ljj;
  reception_433 fenetre;
  int POWERKEY = 6;
  char* phone_number = "0754180255";
  char* message = "La fenetre est ouverte";
  string nomfic = "etat.txt";
  public :
  void open();
  void close();
  void attendre();
  void envoiSMS();
  void etabli_ouvert();
  //scenarioSMS(char phone_number[], char message[]);
  void traitement();
  
};

