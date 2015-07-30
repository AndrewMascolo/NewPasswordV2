//password.h

#ifndef NewPasswordV2_h
#define NewPasswordV2_h

#include <Arduino.h>

#define Max_Num_of_Passwords  10
#define Max_Lenght_of_Passwords 6

class NewPasswordV2 {

	public:
				NewPasswordV2();
		void	AddPassword(char * NewPass, char * NewUser);
		void	AddPassword(char * NewPass, char * NewUser, void(*userFunc)(void));
		void	SetLockout(byte attempts = 3, unsigned long lockTime = 1);
		void 	EnterKey(char ENT = '+');
		void 	BackSpaceKey(char CLR = '-');
		void	SetPasswordLength(unsigned char L = 0);
		byte	RemainingAttempts();
		
		byte	CheckPassword(char*);
		char	* CheckUser();
		byte 	EnterData(char, char*);	
		void	DeleteEventPassword(char*);
	
	private:		
		char _CLR;
		char _ENT;
		char nt[Max_Lenght_of_Passwords];
		unsigned char 
			cnt, 
			User_Inc,
			userFound,
			PassLen;
			
		byte Attempts;
		unsigned long LockTime;
		
	protected:
		void (*intFunc[Max_Num_of_Passwords])();
	    char Password[Max_Num_of_Passwords][Max_Lenght_of_Passwords];
		char Username[Max_Num_of_Passwords][10];
};

#endif