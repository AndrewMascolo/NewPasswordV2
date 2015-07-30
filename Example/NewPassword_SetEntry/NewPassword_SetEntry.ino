#include <NewPasswordV2.h>

NewPasswordV2 Mypass;

char Name[10]= {NULL};
char Pword[5] = {'\0'};
char data;

void setup(){
  Serial.begin(115200);
  Mypass.SetPasswordLength(4);
  Mypass.AddPassword("1234","Andy",ShowAndrew); // password, name, function.
  Mypass.AddPassword("0123","Mike"); // When not using the Enterkey, you can either enter the max password length or set your own length.
                                     // However, if you choose not to use the EnterKey, then the passwords MUST all be the same length and 
                                     // you must set the Serial monitor to add NewLine (its the box next to the baud rate ie. 9600)
  Mypass.AddPassword("abcd","Joe",ShowJoe); 
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
  Serial.print("Do you want to store this new password? (y | n): ");
  while(1)
  {
    if(Serial.available() > 0 )
    {
      char choice = Serial.read();
      if(choice == 'y' || choice == 'Y')
      {
        Serial.println(choice);
        Serial.println("Enter the person's name.");
        int cnt = 0;
        while(1)
        {
          if(Serial.available() > 0 )
          {
            char name = Serial.read(); 
            if(name == '.' || name == '\n' || name == '\r' ) break;
            else
            {
              Name[cnt++] = name;
              Name[cnt] = '\0';
            }
          }
        }
        Newpassword(Pword,Name);
        break;
      }
      else{
        Serial.println(choice); 
        break;
      }
      break;
    }
  }
}

void Newpassword(char * New_Pass, char * New_U)
{
  Mypass.AddPassword(New_Pass, New_U);
  Serial.println("New Password was added: ");
  //Mypass.MemCheck();
}

void ShowAndrew()
{
  Serial.println("Andrew's Function!");
}

void ShowJoe()
{
 Serial.println("Joe's Function!"); 
}
