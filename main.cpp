#include <iostream>
#include <cmath>
#include "cCompression.h"
#include "cHuffman.h"

using namespace std;

int main()
{
    /*const unsigned taille = 8;
    int image[taille][taille] = {
                                { 139, 144, 149, 153, 155, 155, 155, 155 },
                                { 144, 151, 153, 156, 159, 156, 156, 156 },
                                { 150, 155, 160, 163, 158, 156, 156, 156 },
                                { 159, 161, 162, 160, 160, 159, 159, 159 },
                                { 159, 160, 161, 162, 162, 155, 155, 155 },
                                { 161, 161, 161, 161, 160, 157, 157, 157 },
                                { 162, 162, 161, 163, 162, 157, 157, 157 },
                                { 162, 162, 161, 161, 163, 158, 158, 158 }
                            };

    cCompression CC(taille, taille, image);
    cout << "image : " << endl;
    CC.Affichage(image);

    double DCT_Img[taille][taille];
    CC.Calcul_DCT_Block(DCT_Img, image);
    cout << "DCT_Img : " << endl;
    CC.Affichage(DCT_Img);

    int Img_Quant[taille][taille];
    CC.quant_JPEG(DCT_Img, Img_Quant);
    cout << "Img_Quant : " << endl;
    CC.Affichage(Img_Quant);

    double Img_DeQuant[taille][taille];
    CC.dequant_JPEG(Img_DeQuant, Img_Quant);
    cout << "Img_DeQuant : " << endl;
    CC.Affichage(Img_DeQuant);

    int IDCT[taille][taille];
    CC.Calcul_IDCT(Img_DeQuant, IDCT);
    cout << "IDCT : " << endl;
    CC.Affichage(IDCT);

    cout << "Equart Quadratique Moyen : " << CC.EQM(IDCT) << endl;
    cout << "Taux de compression : " << CC.taux_compression(Img_DeQuant) << "%" << endl;

    //CC.Testalgo();

    int Trame[(2*taille)-2];
    CC.RLE_Block(Img_Quant, Img_Quant[0][0], Trame);

    cout << "Trame = [ ";
    for(unsigned m=0; m<(2*taille)-2; m++)
    {
        cout << Trame[m] << ", ";
    }
    cout << Trame[(2*taille)-2] << " ]" << endl;

    int TrameT[(2*taille)-2];
    CC.RLE(Img_Quant, TrameT);

    cout << "TrameT = [ ";
    for(unsigned m=0; m<(2*taille)-2; m++)
    {
        cout << TrameT[m] << ", ";
    }
    cout << TrameT[(2*taille)-2] << " ]" << endl;*/




    char trame[6] = {'a', 'b', 'c', 'd', 'e', 'f'};
    double freq[6] = {5, 3, 7, 1, 10, 2};
    cHuffman ARBRE(6, trame, freq);

    double newtrame[6];



    return 0;
}
