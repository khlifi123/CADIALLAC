/*
 * asservissement.h
 *
 *  Created on: Feb 27, 2024
 *      Author: m-ali.khlifi
 */

#ifndef INC_ASSERVISSEMENT_H_
#define INC_ASSERVISSEMENT_H_

void Regulation_Mt1( float vitessem1, float vf,float tensionMax);//reguler vitesse1 %vitesse reference et synchroniser avec vitesse2
void Regulation_MtR2( float vitessem2,float vf,float tensionMax);

#endif /* INC_ASSERVISSEMENT_H_ */
