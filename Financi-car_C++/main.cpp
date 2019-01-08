#include <iostream>
#include "Juros.h"
#include "string.h"

#define n 5
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

float valor,juros,aux,listaAl[n];
char modelo[15],listaCarro[n];
int ops,i=0,mes,lista[n];

///funções//
void cadastro();
char menu();
Juros jr;


int main() {
 cout<<"########################################################################################################################"<<endl;


 while(1){
 	cout<<"\t\t\t\t\t\t Fim-Car"<<endl;
 	cout<<"\n\nCadastro dos Carros:\n";
	menu();
	cout<<"\nDigite Uma ops:";
	cin>>ops; 
	
	if(ops == 1){
	  cadastro();
	  lista[i] =  valor;
	  listaAl[i] = jr.getAlmento(jr.getconta());
	  i++;
	  
}
	else if(ops == 2){
	 cout<<"\t\t\tLista\n\n";
	 for(int i=0;i<n;i++){
	  cout<<"Modelo:"<<i<<"\t"<<"Valor:"<<lista[i]<<"\t"<<"Almento:"<<listaAl[i]<<endl;
	  if (i == 4)
	   system("pause");
                   }
	}
	  
	else if(ops == 4)
	  break;
	  
	else if(ops == 3){
	  cout<<"reset Lista de Carro...";
	  for(int i=0;i<n+1;i++){
	   lista[i] = {};
	   listaAl[i] = {};	  
     }
     i=0;
}
	else  
	  cout<<"Ops Errada";
	  system("cls");
	
 }
	return 0;
}



char menu(){
 char menu[50] = "  1- cadastro\n  2- Lista\n  3- reset\n  4- sair\n";
 for(int i=0;i<strlen(menu);i++)					 	                  
      cout<<menu[i];
  return 0;
}


void cadastro(){
 			
 cout<<"Modelo:";
 cin>>modelo;
 jr.setCarro(modelo);

 
	
 cout<<"Valor:";
 cin>>valor;
 
 cout<<"Mes:";
 cin>>mes;
 
 cout<<"Juros:";
 cin>>juros;
 
 system("cls");
 cout<<"Modelo:";
 cout<<jr.getCarro()<<"\t"<<"Valor do Carro:"<<jr.getValorcarro(valor)<<"\t"<<"Juros:"<<juros<<"%"<<"\t"<<"Numeos de Meses:"<<mes<<"\t"<<"Prestacao:"<<(valor/mes)<<endl;
 jr.setconta(valor,mes,juros);
 cout<<"\n\nCalculando...."<<"\n"<<"Modelo:";
 
 cout<<jr.getCarro()<<"\t"<<"Valor do Carro:"<<"\t"<<jr.getAlmento(jr.getconta())<<"\t"<<"Juros:"<<juros<<"%"<<"\t"<<"Numeos de Meses:"<<mes;
 jr.setconta(valor,mes,juros);
 cout<<"\t"<<"Almento na Prestacao:"<<jr.getresto()<<"\n\n\n";
 jr.setconta(valor,mes,juros);
 system("pause");
	
	
}




