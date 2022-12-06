#ifndef CCOMPRESSION_H
#define CCOMPRESSION_H
#include <cmath>
#include <iostream>

using namespace std;

const unsigned taille = 8;

class cCompression
{
    unsigned int mLargeur;  //La largeur de l'image
    unsigned int mHauteur;  //La hauteur de l'image
    unsigned int **mBuffer;    //L'image
    unsigned int mQualite;      //Qualité de la compression (0 à 100) 50 par défaut
    int Q[taille][taille] = {
                                { 16, 11, 10, 16, 24,  40,  51,  61  },
                                { 12, 12, 14, 19, 26,  58,  60,  55  },
                                { 14, 13, 16, 24, 40,  57,  69,  56  },
                                { 14, 17, 22, 29, 51,  87,  80,  62  },
                                { 18, 22, 37, 56, 68,  109, 103, 77  },
                                { 24, 35, 55, 64, 81,  104, 113, 92  },
                                { 49, 64, 78, 87, 103, 121, 120, 101 },
                                { 72, 92, 95, 98, 112, 100, 103, 99  },
                            };

    public:
        //! Constructeur de la classe cCompression
        /**@brief
        *   Cette fonction permet de creer un objet cCompression a partir des parametres suivants
        *
        *@param[in] Largeur
        *   unsigned int avec la valeur de la largeur de l'image en pixels
        *@param[in] Hauteur
        *   unsigned int avec la valeur de la hauteur de l'image en pixels
        *@param[in] Bloc8x8
        *   tableau realise en allocation dynamique representant la valeur de chaque pixel de l'image
        *@param[in] qualite
        *   unsigned int avec la valeur de la qualite de l'image
        */
        cCompression(unsigned int largeur, unsigned int hauteur, int Bloc8x8[][taille], unsigned int qualite=50)
        {
            mLargeur = largeur; //stockage de la largeur
            mHauteur = hauteur; //stockage de la hauteur
            mQualite = qualite; //stockage de la qualité

            //Création du tableau mbuffer
            mBuffer = new unsigned int*[taille];
            for(unsigned i=0; i<taille; i++)
            {
                mBuffer[i] = new unsigned int[taille];
            }
            for(unsigned i=0; i<taille; i++)
            {
                for(unsigned j=0; j<taille; j++)
                {
                    mBuffer[i][j] = Bloc8x8[i][j];
                }
            }
        }

        //! Destructeur de la classe cCompression
        /**@brief
        *   Cette fonction permet de supprimer une variable de cCompression
        */
        virtual ~cCompression() {/*Destructeur*/}

        //! Getteur de largeur
        /**@brief
        *   Cette fonction permet de recuperer la largeur de l'image
        *
        *@retval unsigned int mLargeur
        *   Largeur de l'image
        */
        unsigned int GetLageur() const{return mLargeur;}

        //! Getteur de hauteur
        /**@brief
        *   Cette fonction permet de recuperer la hauteur de l'image
        *
        *@retval unsigned int mHauteur
        *   Hauteur de l'image
        */
        unsigned int GetHauteur() const{return mHauteur;}

        //! Getteur de qualite
        /**@brief
        *   Cette fonction permet de recuperer la qualite de l'image
        *
        *@retval unsigned int mQualite
        *   Qualite de l'image
        */
        unsigned int GetQualite() const{return mQualite;}

        //! Setteur de lageur
        /**@brief
        *   Cette fonction permet de modifier la largeur de l'image
        *
        *@param[in] L
        *   unsigned int avec la nouvelle largeur de l'image
        */
        void SetLageur(unsigned int L){mLargeur = L;}

        //! Setteur de hauteur
        /**@brief
        *   Cette fonction permet de modifier la hauteur de l'image
        *
        *@param[in] H
        *   unsigned int avec la nouvelle hauteur de l'image
        */
        void SetHauteur(unsigned int H){mHauteur = H;}

        //! Setteur de qualite
        /**@brief
        *   Cette fonction permet de modifier la qualite de l'image
        *
        *@param[in] Q
        *   unsigned int avec la nouvelle qualite de l'image
        */
        void SetQualiteSetQualite(unsigned int Q){mQualite = Q;}

        //! Calcul de la DCT
        /**@brief
        *   Cette fonction permet de calculer la DCT d'une image
        *
        *@param[out] DCT_Img
        *   tableau permettant de stocker la DCT de l'image
        *@param[in] Bloc8x8
        *   tableau avec l'image cible
        */
        void Calcul_DCT_Block(double DCT_Img[][taille], int Bloc8x8[][taille])
        {
            unsigned x, y, u, v;
            double C[8];
            C[0] = 1./sqrt(2);
            for(unsigned n=1; n<8; n++)
            {
                C[n] = 1.;
            }
            double somme = 0.;

            //Calcul de la DCT avec la formule dans le sujet
            for(u=0; u<8; u++)
            {
                for(v=0; v<8; v++)
                {
                    for(x=0; x<8; x++)
                    {
                        for(y=0; y<8; y++)
                        {
                            somme += (Bloc8x8[x][y]-128) * cos( (2*x+1)*M_PI*u / 16 ) * cos( (2*y+1)*M_PI*v / 16 ); //img-128 pour ramener entre -128 et 127
                        }//fin for(y)
                    }//fin for(x)
                    DCT_Img[u][v] = round( (1./4) * C[u] * C[v] * somme * 100)/100;
                    somme = 0.;
                }//fin for(v)
            }//fin for(u)
        }

        //! Calcul de la IDCT
        /**@brief
        *   Cette fonction permet de calculer linverse de la DCT d'une image
        *
        *@param[in] DCT_Img
        *   tableau contenant la DCT cible
        *@param[out] Bloc8x8
        *   tableau permettant de stocker l'IDCT
        */
        void Calcul_IDCT(double DCT_Img[][taille], int Bloc8x8[][taille])
        {
            //Calcul de l'inverse de la DCT avec la formule dans le sujet
            unsigned x, y, u, v;
            double C[8];
            C[0] = 1./sqrt(2);
            for(unsigned n=1; n<8; n++)
            {
                C[n] = 1.;
            }
            double somme = 0.;

            for(x=0; x<8; x++)
            {
                for(y=0; y<8; y++)
                {
                    for(u=0; u<8; u++)
                    {
                        for(v=0; v<8; v++)
                        {
                            somme += DCT_Img[u][v] * C[u] * C[v] * cos( (2*x+1)*M_PI*u / 16 ) * cos( (2*y+1)*M_PI*v / 16 );
                        }//fin for(v)
                    }//fin for(u)
                    Bloc8x8[x][y] = round(somme / 4) + 128;
                    somme = 0.;
                }//fin for(y)
            }//fin for(x)
        }

        //! Calcul de la Quantification d'une image
        /**@brief
        *   Cette fonction permet de quantifier une image
        *
        *@param[in] DCT_Img
        *   tableau contenant l'image/DCT cible
        *@param[out] Img_Quant
        *   tableau permettant de stocker l'image quantifiée
        */
        void quant_JPEG(double Img_DCT[][taille], int Img_Quant[][taille])
        {
            //Calcul de la quantification avec la formule dans le sujet
            int Qtab[taille][taille];
            creationQtab(Qtab);

            for(unsigned u=0; u<taille; u++)
            {
                for(unsigned v=0; v<taille; v++)
                {
                    Img_Quant[u][v] = round( Img_DCT[u][v] / Qtab[u][v] );
                }
            }
        }

        //! Creation de la matrice Qtab
        /**@brief
        *   Cette fonction permet calculer Qtab qui permettra de quantifier ou de dequantifier une image
        *
        *@param[out] Qtab
        *   tableau permettant de stocker la matrice Qtab
        */
        void creationQtab(int Qtab[][taille])
        {
            //Création de la matrice Qtab avec la formule dans le sujet (Q est initialisée)
            double lbd;
            double cond;

            if(mQualite < 50)
            {
                lbd = 5000. / mQualite;
            }
            else
            {
                lbd = 200 - 2*mQualite;
            }

            for(unsigned i=0; i<taille; i++)
            {
                for(unsigned j=0; j<taille; j++)
                {
                    cond = (Q[i][j]*lbd + 50) / 100;
                    if(cond < 1)
                    {
                        Qtab[i][j] = 1;
                    }
                    else if(cond > 255)
                    {
                        Qtab[i][j] = 255;
                    }
                    else
                    {
                        Qtab[i][j] = cond;
                    }
                }
            }
        }

        //! Calcul de la Dequantification d'une image
        /**@brief
        *   Cette fonction permet de dequantifier une image, soit l'inverse de la quantification
        *
        *@param[out] Img_DCT
        *   tableau permettant de stocker l'image dequantifiee
        *@param[in] Img_Quant
        *   tableau contenant l'image quantifiee cible
        */
        void dequant_JPEG(double Img_DCT[][taille], int Img_Quant[][taille])
        {
            //Pour la déquantification, on fait juste l'inverse du calcul de la quantification
            int Qtab[taille][taille];
            creationQtab(Qtab);

            for(unsigned u=0; u<taille; u++)
            {
                for(unsigned v=0; v<taille; v++)
                {
                    Img_DCT[u][v] = round( Img_Quant[u][v] * Qtab[u][v] );
                }
            }
        }

        //! Calcul de l'Ecart Quadiatrique Moyen (EQM)
        /**@brief
        *   Cette fonction permet de calculer l'EQM entre l'image obtenue et celle d'origine
        *
        *@param[in] Img_IDCT
        *   tableau contenant l'image approchee pour la comparer a celle d'origine
        *@retval double EQM
        *   EQM entre l'image approchee et l'originale
        */
        double EQM(int Img_IDCT[][taille])
        {
            //Le calcul de l'EQM est sur le sujet
            double somme = 0.;
            double EQM = 0.;

            for(unsigned i=0; i<taille; i++)
            {
                for(unsigned j=0; j<taille; j++)
                {
                    somme += (mBuffer[i][j] - Img_IDCT[i][j]) * (mBuffer[i][j] - Img_IDCT[i][j]);
                }
            }
            EQM = round(somme / (taille*taille));
            return EQM;
        }

        //! Calcul du taux de compression
        /**@brief
        *   Cette fonction determine le taux de compression en comparant l'image compressee avec celle d'origine en compatant les 0
        *
        *@param[in] Bloc8x8
        *   tableau contenant l'image compressee pour la comparer a celle d'origine
        *@retval double taux
        *   taux de compression entre l'image compressee et l'originale
        */
        double taux_compression(double Bloc8x8[][taille])
        {
            double taux = 0.;
            int nbinit = 0;
            int nbcomp = 0;
            for(unsigned i=0; i<taille; i++)
            {
                for(unsigned j=0; j<taille; j++)
                {
                    if(mBuffer[i][j] != 0)
                    {
                        nbinit++;
                    }
                    if(Bloc8x8[i][j] != 0)
                    {
                        nbcomp++;
                    }
                }
            }
            taux = round( 100-((100*nbcomp)*1./nbinit) );
            return taux;
        }

        //! Calcul de la trame RLE pour un block de taille (8x8)
        /**@brief
        *   Cette fonction determine la tramme de l'image quantifiee
        *
        *@param[in] Bloc8x8
        *   tableau contenant l'image quantifiee
        *@param[in] DC_precedent
        *   int contenant la premiere valeur de l'image
        *@param[out] Trame
        *   tableau permettant de stocker la trame calculee
        */
        void RLE_Block(int Bloc8x8[][taille], int DC_precedent, int Trame[(2*taille)-2])
        {
            unsigned i = 0;
            unsigned j = 0;
            Trame[0] = DC_precedent;
            int ctrame = 1;
            int nbzero = 0;

            for(unsigned k=2; k <= taille; k++)      //k représente le nombre d'élément en diagonale
            {
                for(unsigned im=0; im<k; im++)       //Fonctionnement normal
                {
                    if(k%2==0)      //si k est pair, on monte
                    {
                        i = 0+im;
                        j = (k-1)-im;
                    }
                    else            //sinon on descend
                    {
                        i = (k-1)-im;
                        j = 0+im;
                    }

                    if(Bloc8x8[i][j]==0)
                    {
                        nbzero++;
                    }
                    if(Bloc8x8[i][j]!=0)
                    {
                        Trame[ctrame] = nbzero;
                        Trame[ctrame+1] = Bloc8x8[i][j];
                        nbzero = 0;
                        ctrame+=2;
                    }
                }//fin for(im)
            }//fin for(k)

            for(unsigned k=(taille-1); k >= 1; k--)      //k représente le nombre d'élément en diagonale
            {
                for(unsigned im=0; im<k; im++)       //Fonctionnement final
                {
                    if(k%2!=0)
                    {
                        i = (taille-1)-im;
                        j = (taille-k)+im;
                    }
                    else
                    {
                        i = (taille-k)+im;
                        j = (taille-1)-im;
                    }
                    if(Bloc8x8[i][j]==0)
                    {
                        nbzero++;
                    }

                    if(Bloc8x8[i][j]!=0)
                    {
                        Trame[ctrame] = nbzero;
                        Trame[ctrame+1] = Bloc8x8[i][j];
                        nbzero = 0;
                        ctrame+=2;
                    }
                }//fin for(im)
            }//fin for(k)
            if(Bloc8x8[taille-1][taille-1]==0)
            {
                Trame[ctrame] = 0;
                Trame[ctrame+1] = Bloc8x8[taille-1][taille-1];
            }
        }

        //! Calcul de la trame RLE totale
        /**@brief
        *   Cette fonction determine la tramme de l'image quantifiee avec une taille multible de 8
        *
        *@param[in] Bloc8x8
        *   tableau contenant l'image quantifiee
        *@param[out] Trame
        *   tableau permettant de stocker la trame finale
        */
        void RLE(int Bloc8x8[][taille], int *Trame)
        {
            unsigned n = taille/8;   //Nombre de blocks de 8*8
            int TrameUnit[2*taille-2];

            for(unsigned nb=0; nb<n; nb++)
            {
                for(unsigned i=(nb*8); i<(8+(8*nb)); i++)
                {
                    RLE_Block(Bloc8x8, Bloc8x8[nb*8][nb*8], TrameUnit);
                    for(unsigned j=(nb*8); j<(2*8+(8*nb)); j++)
                    {
                        Trame[j]=TrameUnit[j];
                    }
                }
            }
        }

        template <typename T>
        //! Fonction affichage des images
        /**@brief
        *   Cette fonction permet d'afficher un tableau quelque soit son type
        *
        *@param[in] img
        *   tableau contenant l'image a afficher
        */
        void Affichage(T img[][taille]) const
        {
            cout << "[  ";
            for(unsigned i=0; i<taille; i++)
            {
                for(unsigned j=0; j<taille; j++)
                {
                    if(j<taille-1)
                    {
                        cout << img[i][j] << ",   ";
                    }
                    else
                    {
                        cout << img[i][j];
                    }
                }
                if(i<taille-1)
                {
                    cout << "  ]" << endl << "[  ";
                }
                else
                {
                    cout << "  ]" << endl;
                }
            }
        }

};

#endif // CCOMPRESSION_H
