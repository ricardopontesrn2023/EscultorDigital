#include <iostream>
#include <cstdlib>
#include "Sculptor.h"
#include <fstream>
#include <string>

int main()
{
    //Exemplo
    Sculptor exemplo(60,60,60);

    exemplo.setColor(1.0, 0.79, 0.85, 1.0);

    exemplo.putVoxel(1, 2, 3);
    exemplo.cutVoxel(1, 2, 3);
    exemplo.putBox(15,20,36,40,30,36);
    exemplo.cutBox(17,19,38,40,30,32);
  
    exemplo.setColor(0.78, 0.63, 0.78, 1.0);
    exemplo.putEllipsoid(5, 25,30 ,6 ,10 ,6);
    exemplo.cutEllipsoid(5, 30, 30, 6, 10, 6);
  
    exemplo.setColor(1.0, 0.0 ,1.0 , 0.5);
    exemplo.putSphere(29, 30, 30, 10); 
    exemplo.cutSphere(29, 35, 30, 10);
 	
    exemplo.writeOFF((char*)"exemplo.off");
    
    //desenho do Bart Simpsom
    Sculptor desenho(100, 100, 100);
    //cabeça
    desenho.setColor(1.0, 1.0, 0, 1.0);
    desenho.putEllipsoid(25, 25, 25, 15, 1000, 15);
    desenho.cutBox(1, 50, 0, 60, 1, 50);
    //pescoço
    desenho.setColor(1.0, 1.0, 0, 1.0);
    desenho.putEllipsoid(25, 25, 25, 10, 1000, 10);
    desenho.cutBox(1, 50, 0, 52, 1, 50);
    //peitoral
    desenho.setColor(1.0, 0, 0, 1.0);
    desenho.putBox(10, 40, 50, 52, 9, 37);
    desenho.putBox(8, 42, 45, 49, 9, 37);
    desenho.putBox(6, 44, 34, 44, 9, 37);
    desenho.putBox(8, 9, 50, 51, 9, 37);
    desenho.putBox(9, 9, 52, 52, 9, 37);
    desenho.putBox(41, 42, 50, 51, 9, 37);
    //orelha direta
    desenho.setColor(1.0, 1.0, 0, 1.0);
    desenho.putSphere(11, 80, 25, 5);
    desenho.setColor(0, 0, 0, 0);
    desenho.putVoxel(10, 79, 29);
    desenho.putVoxel(9, 80, 29);
    desenho.putVoxel(10, 81, 29);
    //orelha esquerda
    desenho.setColor(1.0, 1.0, 0, 1.0);
    desenho.putSphere(39, 80, 25, 5);
    desenho.setColor(0, 0, 0, 0);
    desenho.putVoxel(40, 79, 29);
    desenho.putVoxel(41, 80, 29);
    desenho.putVoxel(40, 81, 29);
    //olho direito
    desenho.setColor(1.0, 1.0, 1.0, 1.0);
    desenho.putSphere(19, 85, 37, 5);
    desenho.setColor(0, 0, 0, 0);
    desenho.putVoxel(19, 85, 41);
    //olho esquerdo
    desenho.setColor(1.0, 1.0, 1.0, 1.0);
    desenho.putSphere(32, 85, 37, 5);
    desenho.setColor(0, 0, 0, 0);
    desenho.putVoxel(32, 85, 41);
    //cabelo
    desenho.setColor(0, 0, 0, 0);
    desenho.cutBox(13, 13, 98, 99, 11, 39);
    desenho.cutBox(17, 17, 98, 99, 11, 39);
    desenho.cutBox(15, 15, 98, 99, 11, 39);
    desenho.cutBox(19, 19, 98, 99, 11, 39);
    desenho.cutBox(21, 21, 98, 99, 11, 39);
    desenho.cutBox(23, 23, 98, 99, 11, 39);
    desenho.cutBox(25, 25, 98, 99, 11, 39);
    desenho.cutBox(27, 27, 98, 99, 11, 39);
    desenho.cutBox(29, 29, 98, 99, 11, 39);
    desenho.cutBox(31, 31, 98, 99, 11, 39);
    desenho.cutBox(33, 33, 98, 99, 11, 39);
    desenho.cutBox(35, 35, 98, 99, 11, 39);
    desenho.cutBox(37, 37, 98, 99, 11, 39);
    //nariz
    desenho.setColor(1.0, 1.0, 0, 1.0);
    desenho.putSphere(26, 80, 40, 4);
    //boca
    desenho.setColor(0, 0, 0, 0);
    desenho.putBox(21, 30, 70, 70, 39,39);
    desenho.putVoxel(31, 71, 39);
    desenho.putVoxel(32, 72, 39);
    desenho.putVoxel(20, 71, 39);
    desenho.putVoxel(19, 72, 39);

    desenho.writeOFF((const char*)"BartSimpson.off");

    std::cout << "passou\n";

    getchar();
    return 0;
}
