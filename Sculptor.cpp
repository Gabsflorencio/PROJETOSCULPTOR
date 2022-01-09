#include "Sculptor.h"
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

//construtor Sculptor
Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
    nx = _nx, ny = _ny, nz = _nz;
    if(nx <= 0 || ny <= 0 || nz <= 0){
        nx = ny = nz = 1;
    }
    //alocacao de memoria
    v = new Voxel **[nx];
    v[0] = new Voxel *[nx * ny];
    v[0][0] = new Voxel [nx * ny * nz];

    for(int i = 1; i < nx; i++){
        v[i] = v[i-1] + ny;
    }
    for(int i = 1; i < (nx * ny); i ++){
        v[0][i] = v[0][i-1] + nz;
    }
}
//destrutor Sculptor
Sculptor::~Sculptor()
{
    //liberacao de memoria em blocos
    delete [] v[0][0];
    delete [] v[0];
    delete [] v;
}
//adiciona cor
void Sculptor::setColor(float _r, float _g, float _b, float alpha){
    //usando escala de cor de 0.01 a 0.99, sendo 0.01 a ausencia da cor e 0.99 a cor absoluta
    r = _r;
    g = _g;
    b = _b;
    a = alpha;
}
//desenha o Voxel
void Sculptor::putVoxel(int x, int y, int z){
    v[x][y][z].isOn = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
}
//remove o Voxel
void Sculptor::cutVoxel(int x, int y, int z){
    v[x][y][z].isOn = false;
}
//constroi uma caixa com os Voxels
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int i = x0; i <= x1; i++){
        for(int j = y0; j <= y1; j++){
            for(int k = z0; k <= z1; k++){
                putVoxel(i,j,k);
            }
        }
    }
}
//deleta os voxels em forma de caixa
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int i = x0; i <= x1; i++){
        for(int j = y0; j <= y1; j++){
            for(int k = z0; k <= z1; k++){
                cutVoxel(i,j,k);
            }
        }
    }
}
//constroi uma esfera
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    float distancia;
    for(int i = 0; i <= nx; i++){
        for(int j = 0; j <= ny; j++){
            for(int k = 0; k <= nz; k++){
                distancia = sqrt(pow(i-xcenter,2)+ pow(j-ycenter,2) + pow(k-zcenter,2));
                if(distancia < radius){
                    putVoxel(i,j,k);
                }
            }
        }
    }
}
//corta esfera
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    float distancia;
    for(int i = 0; i <= nx; i++){
        for(int j = 0; j <= ny; j++){
            for(int k = 0; k <= nz; k++){
                distancia = sqrt(pow(i-xcenter,2)+ pow(j-ycenter,2) + pow(k-zcenter,2));
                if(distancia < radius){
                    cutVoxel(i,j,k);
                }
            }
        }
    }
}
//cria uma elipse
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    float distancia;
    for(int i = 0; i <= nx; i++){
        for(int j = 0; j <= ny; j++){
            for(int k = 0; k <= nz; k++){
                distancia = (float) pow((i - xcenter),2)/pow(rx,2) +
                 (float)pow((j-ycenter),2)/pow(ry,2) + (float)pow((k-zcenter),2)/pow(rz,2);
                 if(distancia < 1.0){
                    putVoxel(i,j,k);
                 }
            }
        }
    }
}
//corta a elipse
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    float distancia;
    for(int i = 0; i <= nx; i++){
        for(int j = 0; j <= ny; j++){
            for(int k = 0; k <= nz; k++){
                distancia = (float) pow((i - xcenter),2)/pow(rx,2) +
                 (float)pow((j-ycenter),2)/pow(ry,2) + (float)pow((k-zcenter),2)/pow(rz,2);
                 if(distancia < 1.0){
                    cutVoxel(i,j,k);
                 }
            }
        }
    }
}
//arquivo OFF
void Sculptor::writeOFF(const char* filename){
    int contador = 0, incremento = 0;

    ofstream arquivoOFF;
    arquivoOFF.open(filename);

    if (arquivoOFF.is_open()){
        cout << "Arquivo aberto" << endl;
    } else {
        cout << "Arquivo não abriu" <<endl;
    }

    arquivoOFF << "OFF" << endl;

    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                if(v[i][j][k].isOn == true){
                    contador++;
                }
            }
        }
    }

    arquivoOFF << contador*8 << " " << contador*6 << " 0"<<endl;

    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k= 0; k < nz; k++){
                if (v[i][j][k].isOn == true){
                    arquivoOFF << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                    arquivoOFF << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                    arquivoOFF << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                    arquivoOFF << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                    arquivoOFF << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                    arquivoOFF << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                    arquivoOFF << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                    arquivoOFF << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                }
            }
        }
    }
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k= 0; k < nz; k++){
                if (v[i][j][k].isOn == true){
                    arquivoOFF << 4 << " " << incremento + 0 << " " << incremento + 3 << " " << incremento + 2 << " " << incremento + 1 << " " <<
                    v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                    arquivoOFF << 4 << " " << incremento + 4 << " " << incremento + 5 << " " << incremento + 6 << " " << incremento + 7 << " " <<
                    v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                    arquivoOFF << 4 << " " << incremento + 0 << " " << incremento + 1 << " " << incremento + 5 << " " << incremento + 4 << " " <<
                    v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                    arquivoOFF << 4 << " " << incremento + 0 << " " << incremento + 4 << " " << incremento + 7 << " " << incremento + 3 << " " <<
                    v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                    arquivoOFF << 4 << " " << incremento + 3 << " " << incremento + 7 << " " << incremento + 6 << " " << incremento + 2 << " " <<
                    v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                    arquivoOFF << 4 << " " << incremento + 1 << " " << incremento + 2 << " " << incremento + 6 << " " << incremento + 5 << " " <<
                    v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                    incremento += 8;
                }
            }
        }
    }
    if(arquivoOFF.is_open()){
        cout << "Arquivo Salvo" << endl;
    }

    arquivoOFF.close();
}
