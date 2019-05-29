#include "mcc_generated_files/mcc.h"  //Librerias
#include "ff.h"
#include "Errores.h"

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>


#define _mSec 1                     //Variables definidas
#define _vin 5.0
#define _base 1023.0

unsigned int adcin;

char data [10];
char *word;
FATFS FatFs;
FIL Fil;


void InitPortA(void);           //Función de inicialización puerto A
void InitPortC(void);           //Función de inicialización puerto C
int interruptadc(int);          //Función de interrupciones del ADC   
void grabador(void);            //Función que inicia la grabación
void reproductor(void);         //Función que inicia la reproducción 
void guardar(char* data);       //Función de guardado 
void __delay_sec(char sec);     //Función de delay


void main(void)
{                   //Se inicializa variables
    adcin = 0;
    int a = 0;
    int out;
    
    int o;
    char letra;
    o = 10;
    letra = "Hola perro :v";
    
    word = &letra;
    
    InitPortA();        //Inicializa puerto A
    InitPortC();        //Inicializa puerto C
      
    OSCCON = 0x53;      //Oscilador interno 4 MHz
    ADCON2 = 0x94;      //ACQT = 4TAD, TAD de 1microS, Justificado derecha 
    ADCON1 = 0x00;      //Vref- = GND, Vref+ = +5V
    ADCON0 = 0x39;      //Enciendo ADC, canal AN14
    GIE = 1;            //Habilita interrupciones globales
    PEIE = 1;           //Habilita interrupciones de periféricos
    ADIE = 1;           //Habilita interrupción ADC
    
    guardar(word);
    while(1){
        ADCON0bits.GO=1;                    //Inicia conversión ADC
        adcin = interruptadc(adcin);        //Envía analagico, recibe digital
        PORTA = adcin/4;                    //Asigna valor adcin a puerto A
    }
    return;
}

int interruptadc(int adcin) {                //Interrupción conversión                       
    if(ADIF==1) {                            //verifica bandera conversión ADC
        ADIE=0;                              //Deshabilita interrupción ADC
        adcin = (ADRESH<<8)+ADRESL;          //Asigna valor ADRESH y ADRESL a adcin
    }
    ADIE=1;                                  //Habilita interrupción ADC
    ADIF=0;                                  //Limpia bandera conversión ADC
    return adcin;                            //Regresa adcin como digital
}


void InitPortA(void)
{
    LATA = 0x00;        //Limpia puerto A
    TRISA = 0x00;       //Puerto A como salida
    ANSELA = 0x00;      //Puerto A como digital
    
    return;
}

void InitPortC(void)
{
    LATC = 0x00;        //Limpia puerto C
    TRISC = 0x04;       //bit RC2 como entrada
    ANSELC = 0x04;      //RC2 como analógico
    
    return;
}

void grabador(void){
         //   __delay_ms(1);              //Retardo para conversión
   
     
}

void reproductor(void){
        
        //Display7Seg(volt);          //Llama a función desplegar en displays
        //LA1=out;
         //IO_RA1_SetLow();
}


void __delay_sec(char sec) {
    for(char i=0;i<=(50*sec);i++) {
        __delay_ms(20);
    }
}

void guardar(char* data){
    UINT bw;   
    SYSTEM_Initialize();
    if (f_mount(&FatFs, "", 1) != FR_OK) {	/* Inicializa SD */
        
        Error(33);
        __delay_sec(2);
        while(f_mount(&FatFs, "", 1) != FR_OK) {
            ;
        }
    }    
    
    Error(1);
    __delay_sec(2);
        
    if (f_open(&Fil, "BeeDev.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE) == FR_OK) {	/* Abre o crea el archivo */
        Error(2);
        
       
        __delay_sec(2);
         Error(3);
            
			if ((Fil.fsize != 0) && (f_lseek(&Fil, Fil.fsize) != FR_OK)) goto endSD;	/* Salta al final del archivo */
                Error(4);
                __delay_sec(2);
                
                f_write(&Fil, data , 28 , &bw);	// DATA ARRAY, NUMERO DE CHAR
                //f_printf(&fil, "%s", "String");  
                Error(5);
                __delay_sec(2);
                endSD: f_close(&Fil);								/* Cierra el archivo */
                Error(6);
                __delay_sec(1);
                
                Error(7);
                __delay_sec(2);
     
	}
    else {
        Error(0);
    }
}