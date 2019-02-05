/** Capteur Ultrasons HC-SR04 **/

/* Définition des broches utilisées */
int TRIGGER_PIN = 12;
int ECHO_PIN = 11;

/* Définition des variables */
long last_measure = 0;
const long MEASURE_TIMEOUT = 25000L; //Constante contenant le délais d'attente entre chaque impulsion en millisecondes (40Hz = 25ms)

void setup()
{
  /* Initialisation des broches */
  pinMode(TRIGGER_PIN, OUTPUT); //On défini la broche TRIGGER en tant que sortie
  digitalWrite(TRIGGER_PIN, LOW); //On initialise la broche TRIGGER avec un courant électrique LOW (pas de courant)
  pinMode(ECHO_PIN, INPUT); //On défini la broche ECHO en tant qu'entrée
  
  /* Mise en commun des résultats avec Processing */
  Serial.begin(9600);
}

void loop()
{
  /* 1) Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
  digitalWrite(TRIGGER_PIN, HIGH); //On envoie un courant électrique dans la broche TRIGGER
  delayMicroseconds(10); //On attend 10µs
  digitalWrite(TRIGGER_PIN, LOW); //On n'envoie plus de courant électrique dans la broche TRIGGER

  /* 2) Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);

  /* 3) Calcul la distance à partir du temps mesuré */
  measure = (measure / 2) * 340; //distance (résultat en µm) = temps mesuré x vitesse du son
  measure = measure / 1000; //On converti le résultat en millimètre
  measure = measure / 10; //On converti le résultat en centimètre

  /* 4) On vérifie s'il y a besoin d'alerter l'utilisateur ou non en comparant les deux dernières distances */
  //Si les deux dernières distances sont différentes de 0 et s'il n'y a eu une variation de distance supérieure à 5cm (marge d'erreur)
  //Alors on alerte l'utilisateur
  if (last_measure != 0 && measure != 0 && (last_measure > measure + 5 || last_measure < measure - 5))
  {
    Serial.write('A'); //On envoie le caractère 'A' dans le port sérieu (pour que Processing le réceptionne et puisse envoyer un email)
	exit(0); //Fin du programme
  }

  last_measure = measure; //On stock la dernière mesure afin de pouvoir la comparer avec la suivante

  /* Délai d'attente pour éviter d'afficher trop de résultats à la seconde */
  delay(100);
}
