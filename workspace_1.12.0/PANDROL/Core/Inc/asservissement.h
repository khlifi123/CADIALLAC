/*
 * asservissement.h
 *
 *  Created on: Apr 24, 2023
 *      Author: m-ali.khlifi-ext
 */


#ifndef INC_ASSERVISSEMENT_H_
#define INC_ASSERVISSEMENT_H_



#endif /* INC_ASSERVISSEMENT_H_ */
void Regulation_Mt1( float vitessem1, float  vitessem2,float vitesseRef,float tensionMax);//reguler vitesse1 %vitesse reference et synchroniser avec vitesse2
void Regulation_Mt2( float vitessem2, float  vitessem1,float vitesseRef,float tensionMax);
void Regulation_Mt3( float vitessem3, float  vitessem4,float vf,float tensionMax);
void Regulation_Mt4( float vitessem4,float  vitessem3,float vf,float tensionMax);
void Regulation_Mt5( float vitessem5,float  vitessem6,float vf,float tensionMax);
void Regulation_Mt6( float vitessem6,float  vitessem5,float vf,float tensionMax);
void Initialization();
void Cleanup();

