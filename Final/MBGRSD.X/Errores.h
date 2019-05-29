/* 
 * File:   Errores.h
 * Author: eduar
 *
 * Created on 15 de mayo de 2019, 04:47 PM
 */

#ifndef ERRORES_H
#define	ERRORES_H
#define _mSec 1


void Error(int a){
    LATD = 0x00;
    TRISD = 0x00;       //Todos como salida digital
    ANSELD = 0x00;
    LATE = 0x00;
    TRISE = 0x00;       //Todos como salida digital
    ANSELE = 0x00;

    unsigned char v_seg[10]={0x7E,0x30,0x6D,0x79,0x33,0x5B,0x5F,0x70,0x7F,0x73};
    if(a != 33 && a != 55){   
    LATD = v_seg[a];              //asigna valor Display a puerto D
    LATE = 0x01;                    //Enciende display     
    }
    else if(a == 33){
    LATD = v_seg[6];              //asigna valor Display a puerto D
    LATE = 0x02;  
    }
    else if(a == 999){              //asigna valor Display a puerto D
    LATE = 0x00;  
    }
    else {
    LATD = v_seg[0];              //asigna valor Display a puerto D
    LATE = 0x01;                    //Enciende display 
    __delay_ms(_mSec);              //Retardo
    
    LATE = 0x00;                    //Apaga display
    LATD = v_seg[9];              //asigna valor Display a puerto D
    LATE = 0x02;                    //Enciende display 
    __delay_ms(_mSec);              //Retardo
    
    LATE = 0x00;                    //Apaga display
    LATD = v_seg[6];       //asigna valor con punto Display a puerto D
    LATE = 0x04;                    //Enciende display 
    __delay_ms(_mSec);              //Retardo
    
    LATE = 0x00;                    //Apaga display
    }
}


#endif