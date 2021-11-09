#include <iostream>
#include <fstream>
#include "Pythia8/Pythia.h" // Include Pythia headers.
using namespace Pythia8; // Let Pythia8:: be implicit.
int main(){

// Create and open a text file
ofstream MyFile("myfile.txt");
//seu code
// Set up generation.
Pythia pythia; // Declare Pythia object
pythia.readString("Charmonium:all = on");
pythia.readString("Beams:eCM = 14000."); // 14 TeV CM energy.

pythia.init(); // Initialize; incoming pp beams is default.
// Generate event(s).
//int ipsi = 0;
int imu1 = 0;
int imu2 = 0;
for (int iEvent = 0; iEvent < 1000000; ++iEvent) { //gerando 1000000 eventos
	pythia.next();
	for (int i = 0; i < pythia.event.size(); ++i) { //loop para selecionar os muons desejados

		if (pythia.event[i].id() == 443){ //loop para selecionar todos os J/Psi que foram gerados em cada evento
			imu1=pythia.event[i].daughter1(); //pegando o evendo da particula filha 1
			imu2=pythia.event[i].daughter2(); //pegando o evendo da particula filha 2
			//verificando se ambas são muons
			if ( abs(pythia.event[imu1].id()) == 13 || abs(pythia.event[imu2].id()) == 13){
				//verificando se os muons tem cargas opostas
				if(pythia.event[imu1].charge()*pythia.event[imu2].charge()<0){
				MyFile << pythia.event[imu1].pT()<<" "<<pythia.event[imu1].eta()<<" "<<pythia.event[imu1].phi()<<" "<<pythia.event[imu2].pT()<<" "<<pythia.event[imu2].eta()<<" "<<pythia.event[imu2].phi()<<" "<<endl; //Escrevendo os parametros desejados dentro do arquivo que será usado no exercicio
				}
			}
		}
	}
}

MyFile.close();

}
