#include "Sculptor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <vector>

Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
    int i, j, k;  //Variaveis para lassos
    nx = _nx; //Variaveis de dimensoes recebendo os valores de inicializacao do construtor
    ny = _ny;
    nz = _nz;

    v = new Voxel**[nx]; //Alocacao dos voxels do eixo x da matriz

    for (i=0; i < nx; i++)
    {
        v[i] = new Voxel*[ny]; //Alocacao dos voxels do eixo y da matriz
    }
    for (i=0; i < nx; i++)
    {
        for (j=0; j<ny; j++)
        {
            v[i][j] = new Voxel[nz]; //Alocacao dos voxels do eixo z da matriz
        }
    }
}

Sculptor::~Sculptor()
{
    int i, j, k;
    for (i=0; i < nx; i++)
    {
        for (j=0; j<ny; j++)
        {
            delete [] v[i][j]; //Liberacao dos voxels do eixo z da matriz
        }
    }

    for (i=0; i < nx; i++)
    {
        delete [] v[i]; //Liberacao dos voxels do eixo y da matriz
    }
    
    delete [] v; //Liberacao completa da matriz
}

void Sculptor::setColor(float _r, float _g, float _b, float a)
{
    Sculptor::r = _r; Sculptor::g = _g; Sculptor::b = _b; Sculptor::a = a;
}
void Sculptor::putVoxel(int x, int y, int z)
{
    if (nx>x && ny>y && nz>z)
    {
        v[x][y][z].isOn = true;// insere um voxel
    // repassa cor e transparência do voxel
        v[x][y][z].r = r; 
        v[x][y][z].g = g; 
        v[x][y][z].b = b; 
        v[x][y][z].a = a; 
        
    }
}
void Sculptor::cutVoxel(int x, int y, int z)
{
    if(nx>x && ny>y && nz>z)
    {
        v[x][y][z].isOn = false;
    }
}
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
   
    if (x0>= 0 && x1<nx && y0 >= 0 && y1 <ny && z0>= 0 && z1<nz)
    {
       //Define uma sequencia de voxel
        for(int i = x0; i<=x1; i++){
            for (int j = y0; j<=y1; j++){
                for (int k = z0; k<=z1; k++){
                    v[i][j][k].isOn=true;
                    v[i][j][k].r = r;
                    v[i][j][k].g = g;
                    v[i][j][k].b = b;
                    v[i][j][k].a = a;
             }
         }
      }  
    } 
}
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    if(x0>=0 && x1<nx && y0>=0 && y1<ny && z0>=0 && z1<nz)
    {
       for(int i=x0; i<=x1; i++)
       {
           for(int j=y0; j<=y1; j++)
           {
               for(int k=z0; k<=z1; k++)
               {
                   v[i][j][k].isOn = false;
               }
           }
       }
    }
}
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius)
{
//Recebe as coordenadas e o raio da esfera
  if(nx>xcenter>0 && ny>ycenter>0 && nz>zcenter>0 && nx>radius>0)
  {
      for( int i = -radius; i<=radius; i++){ //pecorre o diametro
          for(int j = -radius; j<=radius; j++){
              for(int k = -radius; k<=radius; k++){
                  if ((i*i+j*j+k*k) < radius*radius)
                  { //condição da esfera centrada na origem
                      putVoxel(i+xcenter,j+ycenter,k+zcenter); //adiciona um voxel
                  }
              }
          }
      }
  }
}  
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius)
{
//Recebe as coordenadas e o raio da esfera
  if(nx>xcenter>0 && ny>ycenter>0 && nz>zcenter>0 && nx>radius>0)
  {
      for( int i = -radius; i<=radius; i++){ //percorre o diametro
          for(int j = -radius; j<=radius; j++){
              for(int k = -radius; k<=radius; k++){
                  if ((i*i+j*j+k*k) < radius*radius)
                  { //condição da esfera centrada na origem
                      cutVoxel(i+xcenter,j+ycenter,k+zcenter); //exclui um voxel
                  }
              }
          }
      }
  }
}
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    float x,y,z;
  //Define uma elipsoide
   //recebe as coordenadas das dimensões e coordenadas do centro
    if(nx>xcenter>0 && ny>ycenter>0 && nz>zcenter>0)
    {
       for ( int i = 0; i < nx; i++){
           for ( int j = 0; j < ny; j++){
               for (int k = 0; k < nz; k++){
            //calculo da condição de existencia da elipsoide
                x = ((float)(i-xcenter)*(float)(i-xcenter))/(rx * rx);
                y = ((float)(j-ycenter)*(float)(j-ycenter))/(ry * ry);
                z = ((float)(k-zcenter)*(float)(k-zcenter))/(rz * rz);
                   if((x+y+z)<1)
                   {
                       putVoxel(i,j,k); 
                   }
                }
            }
        } 
    }
}
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    float x,y,z;
    //Define uma elipsoide
   //recebe as coordenadas das dimensões e coordenadas do centro
    if(nx>xcenter>0 && ny>ycenter>0 && nz>zcenter>0)
    {
       for ( int i = 0; i < nx; i++){
           for ( int j = 0; j < ny; j++){
               for (int k = 0; k < nz; k++){
            //calculo da condição de existencia da elipsoide
                x = ((float)(i-xcenter)*(float)(i-xcenter))/(rx * rx);
                y = ((float)(j-ycenter)*(float)(j-ycenter))/(ry * ry);
                z = ((float)(k-zcenter)*(float)(k-zcenter))/(rz * rz);
                   if((x+y+z)<1)
                   {
                       cutVoxel(i,j,k); 
                   }
                }
            }
        }
    }
}
void Sculptor::writeOFF(const char *filename)
{
    int qtd_Voxel = 0;
    int ref;
    int  i, j, k, a, b, c; //auxiliares
    float fix = 0.5;
    std::ofstream endArq;
    endArq.open(filename);
    if (endArq.is_open()){
        endArq<<"OFF\n"; //Define off na primeira linha

        // Percorre todas as dimensoes verificando os voxel em exibiçao
        for (i = 0; i < nx; i++){
            for (j = 0; j <ny; j++){
                for (k = 0; k <nz; k++){
                    if(v[i][j][k].isOn == true){
                    qtd_Voxel++; //Guarda a quantidade de voxel ativos
                    }
                }
            }
        }
        endArq<<qtd_Voxel * 8<<" "<<qtd_Voxel * 6 << " " << "0" << "\n"; 
        // exibe a quantidade total de vertices, faces e arestas

        //Pecorre as posições a, b, c e exibe as coordenadas do voxel
        //No primeiro voxel o fix será o valor de referencia
        for (a = 0; a < nx; a++){
            for (b = 0; b < ny; b++){
                for (c = 0; c < nz; c++){
                    if(v[a][b][c].isOn == true){
                        endArq << a - fix << " " << b + fix << " " << c - fix << "\n" << std::flush;
                        endArq << a - fix << " " << b - fix << " " << c - fix << "\n" << std::flush;
                        endArq << a + fix << " " << b - fix << " " << c - fix << "\n" << std::flush;
                        endArq << a + fix << " " << b + fix << " " << c - fix << "\n" << std::flush;
                        endArq << a - fix << " " << b + fix << " " << c + fix << "\n" << std::flush;
                        endArq << a - fix << " " << b - fix << " " << c + fix << "\n" << std::flush;
                        endArq << a + fix << " " << b - fix << " " << c + fix << "\n" << std::flush;
                        endArq << a + fix << " " << b + fix << " " << c + fix << "\n" << std::flush;
                    }
                }
            }
        }

        qtd_Voxel = 0; //Reseta a quantidade de voxel

        // percorre todas as dimensoes
        // Verifica os voxel ativos e exibe as linhas com numeros de faces e as combinacoes que exibem a face
        for (a= 0; a<nx; a++){
            for (b = 0; b<ny; b++){
                for (c= 0; c<nz; c++){
                    if(v[a][b][c].isOn == true){
                    ref = qtd_Voxel * 8;
                    endArq << std::fixed;

                    // Construir linha que monta as faces a partir do vertices:
                    //Valores exemplos do site quando ref = 0:
                    endArq << "4" << " " << 0+ref << " " << 3+ref << " " << 2+ref << " " << 1+ref << " ";
                    //exibindo propriedades do voxel:
                    endArq << std::setprecision(2)<<v[a][b][c].r << " " << std::setprecision(2)<<v[a][b][c].g <<" " << std::setprecision(2)<<v[a][b][c].b << " " << std::setprecision(2) << v[a][b][c].a << "\n";

                    endArq << "4" << " " << 4+ref << " " << 5+ref << " " << 6+ref << " " << 7+ref << " ";
                    endArq << std::setprecision(2)<<v[a][b][c].r << " " << std::setprecision(2)<<v[a][b][c].g <<" " << std::setprecision(2)<<v[a][b][c].b << " " << std::setprecision(2) << v[a][b][c].a << "\n";

                    endArq << "4" << " " << 0+ref << " " << 1+ref << " " << 5+ref << " " << 4+ref << " ";
                    endArq << std::setprecision(2)<<v[a][b][c].r << " " << std::setprecision(2)<<v[a][b][c].g <<" " << std::setprecision(2)<<v[a][b][c].b << " " << std::setprecision(2) << v[a][b][c].a << "\n";

                    endArq << "4" << " " << 0+ref << " " << 4+ref << " " << 7+ref << " " << 3+ref << " ";
                    endArq << std::setprecision(2)<<v[a][b][c].r << " " << std::setprecision(2)<<v[a][b][c].g <<" " << std::setprecision(2)<<v[a][b][c].b << " " << std::setprecision(2) << v[a][b][c].a << "\n";

                    endArq << "4" << " " << 3+ref << " " << 7+ref << " " << 6+ref << " " << 2+ref << " ";
                    endArq << std::setprecision(2)<<v[a][b][c].r << " " << std::setprecision(2) <<v[a][b][c].g <<" " << std::setprecision(2)<<v[a][b][c].b << " " << std::setprecision(2) << v[a][b][c].a << "\n";
                    endArq << "4" << " " << 1+ref << " " << 2+ref << " " << 6+ref << " " << 5+ref << " ";
                    endArq << std::setprecision(2)<<v[a][b][c].r << " " << std::setprecision(2)<<v[a][b][c].g <<" " << std::setprecision(2)<<v[a][b][c].b << " " << std::setprecision(2) << v[a][b][c].a << "\n";

                    qtd_Voxel++; //incrementa a qtd de voxels
                    }
                }
            }
        }
    }
    else{
    std::cout << "Erro ao abrir arquivo de texto."; 
    }
    
    endArq.close();
}
