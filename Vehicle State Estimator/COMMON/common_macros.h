/*
 * common_macros.h
 *
 *  Created on: Dec 22, 2019
 *      Author: Khalaf & Zayed
 */

#ifndef _COMMON_MACROS_H_
#define _COMMON_MACROS_H_


/************************************************************************/
/*			       			BIT_MATH defines       	                    */
/************************************************************************/

/* Set VARiable's Certin BIT High */

#define SET_BIT(VAR,BIT_NB) 		(VAR)|=(BIT_NB)

/* Set VARiable's Certin BIT Low */

#define CLR_BIT(VAR,BIT_NB) 		(VAR)&=~(BIT_NB)

/* Toggle VARiable's Certin BIT */

#define TOGGLE_BIT(VAR,BIT_NB) 		(VAR)^=(BIT_NB)

/* Assign VARiable's Certin BIT by a Certin VALue */

#define ASSIGN_BIT(VAR,BIT_NB,VAL)  (VAR)=((VAR&(~(BIT_NB)))|(VAL&BIT_NB))

/* Get VARiable's Certin BIT Value */

#define GET_BIT(VAR,BIT_NB) 		(((VAR)&(BIT_NB))/(BIT_NB))

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )




#endif /* _COMMON_MACROS_H_ */