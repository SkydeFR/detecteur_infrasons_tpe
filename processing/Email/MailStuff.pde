import java.util.*;

// A function to send mail
void sendMail() {
  // Create a session
  String host="smtp.gmail.com";
  Properties props=new Properties();

  // SMTP Session
  props.put("mail.transport.protocol", "smtp");
  props.put("mail.smtp.host", host);
  props.put("mail.smtp.port", "587");
  props.put("mail.smtp.auth", "true");
  // We need TTLS, which gmail requires
  props.put("mail.smtp.starttls.enable","true");

  // Create a session
  Session session = Session.getDefaultInstance(props, new Auth());

  try
  {
    // Make a new message
    MimeMessage message = new MimeMessage(session);

    // Who is this message from
    message.setFrom(new InternetAddress("detection@chezmoi.maison", "Maison"));

    // Who is this message to (we could do fancier things like make a list or add CC's)
    message.setRecipients(Message.RecipientType.TO, InternetAddress.parse("monemail@perso.com", false));

    // Subject and body
    message.setSubject("Alerte intrusion !");
    message.setText("Une présence à été détectée chez vous par le capteur ultrason !");

    // We can do more here, set the date, the headers, etc.
    Transport.send(message);
    println("Mail envoyé!");
  }
  catch(Exception e)
  {
    e.printStackTrace();
  }

}