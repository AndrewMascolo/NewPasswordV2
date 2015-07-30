//Passwords
#include "NewPasswordV2.h"

NewPasswordV2::NewPasswordV2()
{
  cnt = 0;
  User_Inc = 0;
  for(byte i = 0; i < (Max_Lenght_of_Passwords+1); i++)
  {
    nt[i] = '\0';
  }
  SetPasswordLength(0); // 0 tells the code to use the default value 
}

void NewPasswordV2::SetPasswordLength(unsigned char L)
{
  if(L != 0)
    PassLen = L;
  else
    PassLen = Max_Lenght_of_Passwords;
}

void NewPasswordV2::AddPassword(char * NewPass, char * NewUser, void (*userFunc)(void))
{
 if( User_Inc < Max_Num_of_Passwords)
 {
   strncpy(Password[User_Inc], NewPass, 10);
   strncpy(Username[User_Inc], NewUser, 10);
   intFunc[User_Inc] = userFunc;
   
   User_Inc++;
  }
  else 
    Serial.println("Exceeded Maximum number of users");
}

void NewPasswordV2::AddPassword(char * NewPass, char * NewUser)
{
  AddPassword(NewPass, NewUser, NULL);
}

void NewPasswordV2::EnterKey(char ENT)
{
  _ENT = ENT;
}

void NewPasswordV2::BackSpaceKey(char CLR)
{
  _CLR = CLR;
}

void NewPasswordV2::SetLockout(byte attempts, unsigned long lockTime)
{
  Attempts = attempts;
  LockTime = lockTime;
}

byte NewPasswordV2::CheckPassword(char * Entry) 
{
  byte result = 0;
  byte idx = 0;
  userFound = -1;
  static byte Ampts = Attempts;
  
  while(idx < User_Inc)
  {
    if(!strcmp(Password[idx], Entry))
	{
	  result = 1;
	  userFound = idx;
	  if(*intFunc[idx])
	    intFunc[idx]();
		
	  Ampts = Attempts;
      break;
	}
	else
	  idx++;
  }
  
  if(result == 0)
    Ampts--;
  
  if(Ampts == 0)
  {
    unsigned long prevTime = millis();
    while(1)
	{
      if(millis() - prevTime >= (LockTime * 60UL*1000UL))
	  {
	    Ampts = Attempts;
	    break;
	  }
	}
  }
  return result;
}

byte NewPasswordV2::RemainingAttempts()
{
  return Attempts;
}

char * NewPasswordV2::CheckUser() 
{
  if(userFound != -1)
    return  Username[userFound];
  else
    return "Not Found";
}

byte NewPasswordV2::EnterData(char data, char * PassReturn)
{
	if((data >= '0' && data <= '9') || (data >= 'A' && data <= 'Z') || (data >= 'a' && data <= 'z'))
	{
	  if(data != _CLR && data != _ENT)
	  {
	    nt[cnt] = data;
	    nt[cnt + 1] = '\0';
	    cnt++;
	  }
	}
	else if(data == _CLR)
	{
	  nt[cnt] = '\0';
	  cnt > 0? cnt-- : cnt = 0;
	}
	else if( (data == _ENT) || (cnt == PassLen ) )
	{
	  //Serial.println(cnt);
	  cnt = 0;
	  strncpy(PassReturn, nt, sizeof(nt)); 
	  return 1;
	}
	//Serial.println(cnt);
	return 0;
}


