// This code requires the Java mail library
// smtp.jar, pop3.jar, mailapi.jar, imap.jar, activation.jar
// Download: http://java.sun.com/products/javamail/

import javax.mail.*;
import javax.mail.internet.*;
import processing.serial.*; //add
char inBuffer; //add
Serial myPort; //add

void setup() {
  myPort = new Serial(this, Serial.list()[1], 9600); //add
  //println(Serial.list());  permet de lister les ports existants
}

void draw()
{
  if(myPort.available() > 0) //si il y a reception sur le port
  {
    inBuffer = myPort.readChar(); //on inscrit dans une variable l'octet reçu
    println(inBuffer); //au passage on l'ecrit pour qu'il soit visible
  }
  {
   println("Aucu port disponible"); 
  }
  
  // Function to check mail
  //checkMail();
  
  if(inBuffer == 'A') //si le contenu du buffer vaut le caratère : A
  {
  // Function to send mail
  sendMail();
  noLoop();
  }
  
}