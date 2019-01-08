#ifndef JUROS_H
#define JUROS_H

#include <math.h>
#include <iostream>
#include <string.h>

using namespace std;
#define JUROS 10

class Juros
{
    private:
	char modelo[10];
	int n;
	float PV,i;
	  

	public:
		Juros(){
	  
	   
	   	 
		}
		
	
		
		
	public:void setCarro(char modelo[]){
		 strcpy(this->modelo,modelo);
	}
		
	public: char getCarro(){
		 int i =0;
		 char lista[10];
		 for(i=0;i<strlen(modelo);i++)
		    cout<<this->modelo[i];
		    
		 //strcpy(lista,this->modelo);
	     return modelo[i] ;
	}	
	
		
	public:
		void setconta(float PV,int n,float i){
		 this->i = i;
		 this->PV = PV;
		 this->n = n;
		}
		
		
	public:
		float getconta(){
			i = i/100;
			float pmtx1 =pow((1 + i),n) * i;
			float pmtx2=pow((1 + i),n) -1;
			float pmt = (PV / (pmtx2 /pmtx1));
		  	return pmt;
		}
		
   public:
   	    float  getresto(){
   	      float parcela = PV / n;
   	      float difere = parcela - getconta() ;
   	      return (difere * -1);
   	      //getconta() * mes
	}
	
	
	  public:
   	    float getAlmento(float getconta){
   	     float almento = getconta * n;
   	     return almento ;
   	     
   	 }
    
   	public:
   	    float getValorcarro(int valor){
   	     float aux = valor;
   	     return aux ;
   	        	    
	}
	  
	  
	  public:
   	    float getpretacao(){
   	     float valp = PV / n;
   	     return valp ;
   	        	    
	}
	   
	   
		
		

};

#endif
#ifndef JUROS_H
#define JUROS_H

class Juros
{
	public:
	protected:
};

#endif
