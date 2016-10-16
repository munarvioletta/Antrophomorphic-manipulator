//program_reka
//Proegram realizujacy sterowanie ukladem serwomechanizmĂłw
#include <Servo.h>
Servo servo1; // deklaracja zmiennej servo 1
Servo servo2; // deklaracja zmiennej servo 2
Servo servo3; // deklaracja zmiennej servo 3
Servo servo4; // deklaracja zmiennej servo 4
Servo servo5; // deklaracja zmiennej servo 5

//definicj tablicy serw
Servo tablicaSerw[] = { servo1, servo2, servo3, servo4, servo5}; 

// alokowanie pamieci w zmiennej typu string dla odbieranych danych
String inputString = "";         
boolean stringComplete = false;  // definicja zmiennej stringComplete 

//program glowny

void setup()
{

  servo1.attach(11); // podlaczenie serwa 1 do pinu nr 11
  servo2.attach(10); // podlaczenie serwa 2 do pinu nr 10
  servo3.attach(9); // podlaczenie serwa 3 do pinu nr 9
  servo4.attach(6); // podlaczenie serwa 4 do pinu nr 6
  servo5.attach(5); // podlaczenie serwa 5 do pinu nr 5

  Serial.begin(9600); //rozpoczecie transmisji
    
  // rezerwacja miejsca - 200 bajtow
  inputString.reserve(200);
  
  // zadanie okreslonych katow na serwa - ustawienia poczatkowe

  // 10 stopni to poczatkowa wartosc aby sie serw
  servo1.write(10);
  servo2.write(10);
  servo3.write(10);
  servo4.write(10);
  servo5.write(10);
  
  delay(500);
  //fragment kodu  odpowiedzialny za wyswietlanie komunikatow
  //na monitorze portu szeregowego
  String msg = "Wybierz numer sekwencji ruchu od 1 do 5";
  String msg1 = " 1 - wyprostowanie palcow";
  String msg2 = " 2 - ruch cylindryczny";
  String msg3 = " 3 - ruch szczypcowy";
  String msg4 = " 4 - ruch sferyczny";
  String msg5 = " 5 - ruch pojedynczy kazdego palca";
  String msg6 = " 6 - sekwencja wszystkich chwytow";
  Serial.println(msg);
  Serial.println(msg1);
  Serial.println(msg2);
  Serial.println(msg3);
  Serial.println(msg4);
  Serial.println(msg5);
  Serial.println(msg6);
}

// petla loop() realizowana w programie glownym

void loop()
{
  
 if (stringComplete) 
 {
    // sekwencja 1 - wyprost palcow
    if (inputString.startsWith("1")) 
    {
      Serial.println("Wybrales sekwencje 1 - wyprostowanie palcow");
      
      wyprost(10,1000); 
    }
    // sekwencja 2 - chwyt cylindryczny
    if (inputString.startsWith("2")) 
    {
       Serial.println("Wybrales sekwencje 2 - chwyt cylindryczny");
      cylindryczny(180,1000);
    }
    // sekwencja 3 - chwyt szczypcowy
    if (inputString.startsWith("3")) 
    {
      Serial.println("Wybrales sekwencje 3 - chwyt szczypcowy");
      szczypcowy(63,175,80,80,20,1000);
    }
    // sekwencja 4 - chwyt sferyczny
    if (inputString.startsWith("4")) 
    {
      Serial.println("Wybrales sekwencje 4 - chwyt sferyczny");
      sferyczny(180,145,165,1000);
    }
    // sekwencja 5 - zginanie palcow po kolei
    if (inputString.startsWith("5")) 
    {
      Serial.println("Wybrales sekwencje 5 - ruch kazdego palca po kolei");
      machajReka(10, 180, 10,1000,2000);
    }
       // sekwencja 6 - ruch zgrupowany
       
    if (inputString.startsWith("6")) 
    {
     Serial.println("Wybrales sekwencje 6 - wszystkie sekwencje chwytow wykonaja sie po kolei 2 razy");
     wszystkiesekwencje();
     }      
     
     
    //Serial.println("Wyierz nr sekwensji do wykonania od 1 do 5");     
    
    inputString = "";
    stringComplete = false;
  }
           
}

// funkcja machajReka
void machajReka(int k1, int k2, int k3, int T1, int T2) 
{
  for (int i=0; i<5; i++)

  {
    tablicaSerw[i].write(k1);
    delay(T1);
    tablicaSerw[i].write(k2);
    delay(T2);
    tablicaSerw[i].write(k3);
  }
}

// funkcja wyprost
void wyprost(int k1, int T) 
{
  delay(T);
  servo1.write(k1);// ustawienie zadanej wartosci kata na serwo 1
  servo2.write(k1);// ustawienie zadanej wartosci kata na serwo 2
  servo3.write(k1);// ustawienie zadanej wartosci kata na serwo 3
  servo4.write(k1);// ustawienie zadanej wartosci kata na serwo 4
  servo5.write(k1);// ustawienie zadanej wartosci kata na serwo 5
  delay(T);
}

// funkcja cylindryczny
void cylindryczny(int k1, int T) 
{
  delay(T);
  servo2.write(k1);// ustawienie zadanej wartosci kata na serwo 2
  servo3.write(k1); // ustawienie zadanej wartosci kata na serwo 3
  servo4.write(k1); // ustawienie zadanej wartosci kata na serwo 4
  servo5.write(175); // ustawienie zadanej wartosci kata na serwo 5
  delay(100);
  servo1.write(k1); // ustawienie zadanej wartosci kata na serwo 1
  delay(T);
}
// funkcja szczypcowy
void szczypcowy(int k1, int k2, int k3, int k4, int k5, int T) 
{
  delay(T);
  servo1.write(k1); // ustawienie zadanej wartosci kata na serwo 1
  servo3.write(k3); // ustawienie zadanej wartosci kata na serwo 3
  servo4.write(k4); // ustawienie zadanej wartosci kata na serwo 4
  servo5.write(k5); // ustawienie zadanej wartosci kata na serwo 5
  delay(140);
  servo2.write(k2); // ustawienie zadanej wartosci kata na serwo 2
  delay(T);
}

// funkcja realizujÄ…ca chwyt sferyryczny
void sferyczny(int k1, int k2, int k3, int T) 
{
  delay(T);
  servo2.write(k1); // ustawienie zadanej wartosci kata na serwo 2
  servo3.write(k2); // ustawienie zadanej wartosci kata na serwo 3
  servo4.write(k2); // ustawienie zadanej wartosci kata na serwo 4
  servo5.write(k1); // ustawienie zadanej wartosci kata na serwo 5
  delay(100);
  servo1.write(k3); // ustawienie zadanej wartosci kata na serwo 1
  delay(T);
}
// funkcja realizujaca sekwencje chywtow po kolei po sobie 2 razy
void wszystkiesekwencje()
{
  for(int i=0; i<3; i++)
  {
   //wyprost
      wyprost(10,1000);  
   // delay(T);
    
    // funkcja realizujaca chwyt cylindryczny
      cylindryczny(180,1000);
    
      wyprost(10,1000); 
   // funkcja realizujaca chwyt szczypcowy
     szczypcowy(63,175,80,80,20,1000);
     
     wyprost(10,1000); 
     
  // funkcja realizujaca chwyt sferyczny
     sferyczny(180,145,165,1000);
     
     wyprost(10,1000); 
    
  }
}
// funkcja realizujaca obsluge przerwania 
//wywolanego rozpoczeciem transmisji danyh do mikrokontrolera
void serialEvent() {
  while (Serial.available()) {
    // pobieranie nowego bajtu
    char inChar = (char)Serial.read(); 
    // dodawaniego nowego bajtu do inputString
    inputString += inChar;
   //jeÄąâ€şli nowey znak w linii, ustaw flage
      if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}



