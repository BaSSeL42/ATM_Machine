/*
 * database.h
 *
 *  Created on: Jan 2, 2024
 *      Author: hp
 */

#ifndef APP_DATABASE_H_
#define APP_DATABASE_H_


#define ACCOUNT_NUMBER_BUFFER_SIZE			20
#define DATABASE_BUFFER_SIZE				5
#define MAX_DAILY_LIMIT						5000.00
#define NAME_BUFFER_SIZE					50

typedef enum
{
	FRAUD_CARD 			= 0,
	BLOCKED 			= 1,
	MAX_LIMIT_EXCEED 	= 2,
	INSUFFICIENT_FUND 	= 3,
	RUNNING				= 4

}en_accountState_t;


typedef struct
{
	Uint8_t 			accountNumber[ACCOUNT_NUMBER_BUFFER_SIZE];
	Uint8_t 			name[NAME_BUFFER_SIZE];
	en_accountState_t 	en_accountState;
	Uint32_t			balance;

}st_database_t;




st_database_t st_database[DATABASE_BUFFER_SIZE] = {
		{ "1234567891234567", "Bassel",RUNNING, 2000},
		{ "1235123512351235", "Yasser" ,BLOCKED, 500000 }
};


#endif /* APP_DATABASE_H_ */
