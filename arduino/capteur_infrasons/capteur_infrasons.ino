/* Capteur Ultrason HC-SR04 */
/* Note : passer les écritures dans le port série en commentaire si liaison avec processing */

/* Définition des broches utilisées */
int TRIGGER_PIN = 12;
int ECHO_PIN = 11;

/* Définition des variables */
long last_measure = 0;
int alerte = 0;
const long MEASURE_TIMEOUT = 25000L; // 40Hz = 25ms
//const int led = 53; /* optionnel (alerte lumineuse) */

int i = 0;
char lettre;

void setup()
{
  /* Initialisation des broches */
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
  //pinMode(led, OUTPUT); /* optionnel (alerte lumineuse) */
  //digitalWrite(led, HIGH); /* optionnel (alerte lumineuse) */
  
  /* Pour l'affichage des résultats */
  Serial.begin(9600);
  /* Message d’accueil */
  Serial.println(F("~~ HC-SR04 ~~"));
}

void loop()
{
  if (alerte == 0)
  {
    /* 1) Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);

    /* 2) Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
    long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
    
    /* 3) Calcul la distance à partir du temps mesuré */
    long um = (measure / 2) * 340; /* d = v x t (Résultat en µm) */
    long mm = um / 1000; /* Résultat en mm */

    /* Affiche les résultats en mm, cm et m */
    Serial.print(F("Distance: "));
    Serial.print(mm);
    Serial.print(F("mm ("));
    Serial.print(mm / 10.0, 2);
    Serial.print(F("cm, "));
    Serial.print(mm / 1000.0, 2);
    Serial.println(F("m)"));

    measure = (mm / 10);

    Serial.print(measure);
    Serial.print(" and ");
    Serial.println(last_measure);
    
    if (last_measure != 0 && measure != 0 && (last_measure > measure + 5 || last_measure < measure - 5))
    {
      alerte = 1;
      Serial.write('A');
    }

    last_measure = (mm / 10);

    /* Délai d'attente pour éviter d'afficher trop de résultats à la seconde */
    delay(100);
  }
  else
  {
    Serial.println("Alerte");
    //digitalWrite(led, LOW);
    //delay(500);
    //digitalWrite(led, HIGH);
    //delay(500);
  }
}
