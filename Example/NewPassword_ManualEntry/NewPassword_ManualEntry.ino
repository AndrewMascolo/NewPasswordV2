#include <NewPasswordV2.h>

NewPasswordV2 Mypass;

char Name[10];
char *Pword = " ";
char data;

void setup()
{
  Serial.begin(115200);

  Mypass.EnterKey('#'); // MANUAL MODE Must add # at the end of password to enter it
  Mypass.BackSpaceKey('-'); // MANUAL MODE '-' or (Backspace Key) will delete an index of the password array before checking it.

  Mypass.AddPassword("1234", "Andy", ShowAndrew); // password, name, function.
  Mypass.AddPassword("123", "Mike"); // regular password and username, no function required.
  Mypass.AddPassword("abcd", "Joe", ShowJoe);
}

void loop()
{
  if (Serial.available() > 0 )
  {
    data = Serial.read();
    if (Mypass.EnterData(data, Pword))
    {
      if ( Mypass.CheckPassword(Pword) )
      {
        Serial.print(F("Password was found: "));
        Serial.print(Mypass.CheckUser());
        Serial.println();
      }
      else
      {
        Serial.println(F("Password was not found \n"));
        //EnterNewPassword(); // Comment this out if you do not want to add new passwords
      }
    }
  }
}

void EnterNewPassword()
{
  Serial.println(F("Do you want to store this new password? (y | n): "));
  while (1)
  {
    if (Serial.available() > 0 )
    {
      char choice = Serial.read();
      if (choice == 'y' || choice == 'Y')
      {
        Serial.println(choice);
        Serial.println(F("Enter the person's name."));
        int cnt = 0;
        while (1)
        {
          if (Serial.available() > 0 )
          {
            char name = Serial.read();
            if (name == '.' || name == '\n' || name == '\r' ) break;
            else
            {
              Name[cnt++] = name;
              Name[cnt] = '\0';
            }
          }
        }
        Newpassword(Pword, Name);
      }
      else
        Serial.println(choice);

      break;
    }
  }
}

void Newpassword(char * New_Pass, char * New_U)
{
  Mypass.AddPassword(New_Pass, New_U);
  Serial.println(F("New Password was added: "));
}

void ShowAndrew()
{
  Serial.println(F("Andrew's Function!"));
}

void ShowJoe()
{
  Serial.println(F("Joe's Function!"));
}
