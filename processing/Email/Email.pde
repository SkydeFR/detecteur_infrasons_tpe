// This code requires the Java mail library
// smtp.jar, pop3.jar, mailapi.jar, imap.jar, activation.jar
// Download: http://java.sun.com/products/javamail/

import javax.mail.*;
import javax.mail.internet.*;
import processing.serial.*;
char inBuffer; //On défini une variable de type caractère
Serial myPort;

void setup() {
  myPort = new Serial(this, Serial.list()[1], 9600); //On communique avec le port série d'Arduino
  //println(Serial.list());  permet de lister les ports existants
}

void draw()
{
  if(myPort.available() > 0) //S'il y a reception possible sur le port
  {
    inBuffer = myPort.readChar(); //On stock dans la variable l'octet reçu par le port série
    println(inBuffer); //On affiche le contenu de la variable
  }
  {
   println("Aucun port disponible"); 
  }
  
  //Si le contenu de la variable baut le caractère : 'A' (désignant la nécessité d'envoyer une alerte)
  //Alors on envoie un email d'alerte
  if(inBuffer == 'A')
  {
	  sendMail(); //Envoie de l'email
	  exit(); //Fin du programme
  }
  
}