#include <NewPasswordV2.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 20, 4);

NewPasswordV2 Mypass;

char Name[10] = {NULL};
char Pword[5] = {'\0'};
char data;

void setup() {
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  Serial.begin(9600);
  Mypass.AddPassword("1234", "Andy");
  Mypass.AddPassword("abcd", "Joe");
  Mypass.AddPassword("ASDF", "John");
  Mypass.AddPassword("8520", "Sam");
  Mypass.AddPassword("1111", "Mike");
}

void loop() {
  lcd.setCursor(0, 0);
  if (Serial.available() > 0 ) 
  {
    data = Serial.read();
    if (Mypass.EnterData(data, Pword))
    {
      switch ( Mypass.CheckPassword(Pword) )
      {
        case 1:
          lcd.clear();
          lcd.print("Password was found: ");
          lcd.setCursor(0, 1);
          lcd.print(Mypass.CheckUser());
          break;

        case 0:
          lcd.clear();
          lcd.print("Password not found ");
          EnterNewPassword(); // Comment this out if you do not want to add new passwords
          break;
      }
    }
  }
}

void EnterNewPassword()
{
  lcd.setCursor(0, 1);
  lcd.print("Store it? Y | N: ");
  while (1)
  {
    if (Serial.available() > 0 )
    {
      char choice = Serial.read();
      if (choice == 'y' || choice == 'Y')
      {
        lcd.print(choice);
        lcd.setCursor(0, 2);
        lcd.print("Enter name.");
        int cnt = 0;
        while (1)
        {
          if (Serial.available() > 0 )
          {
            char name = Serial.read();
            if (name == '.') break;
            else
            {
              Name[cnt++] = name;
              Name[cnt] = '\0';
            }
          }
        }
        Newpassword(Pword, Name);
        break;
      }
      else {
        lcd.print(choice);
        break;
      }
      break;
    }
  }
}

void Newpassword(char * New_Pass, char * New_U)
{
  Mypass.AddPassword(New_Pass, New_U);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Password was added: ");
}



