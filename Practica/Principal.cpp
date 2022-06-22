#include <iostream>
#include <cstdlib>
// Librerías de OpenCV
#include <opencv2/core/core.hpp> // Contiene las definiciones base de matrices y estructuras
#include <opencv2/highgui/highgui.hpp> // Interfaz gráfica de usuario
#include <opencv2/imgproc/imgproc.hpp> // Procesamiento de imágenes
#include <opencv2/imgcodecs/imgcodecs.hpp> // Códecs para leer los distintos formatos de imágenes (JPG, PNG, etc.)
#include <opencv2/video/video.hpp> // Lectura de vídeos
#include <opencv2/videoio/videoio.hpp> // Lectura y escritura de videos

//#include <opencv2/opencv.hpp> // Permite cargar todas las librerías de OpenCV

using namespace std;
using namespace cv; // Espacio de nombres de OpenCV para llamar a los métodos de forma más directa

int main(int argc, char *argv[]){

Mat imagen=imread("./BRUCEBANERORG.png");
Mat imagenTriangulo=imread("./BRUCE_BANER.png");
Mat resta;
Mat imgGO;
Mat imgGT;
    namedWindow("Imagen", WINDOW_AUTOSIZE);
    namedWindow("ImagenT", WINDOW_AUTOSIZE);
    namedWindow("Final", WINDOW_AUTOSIZE);
    namedWindow("ImgNegativa", WINDOW_AUTOSIZE);
    cvtColor(imagen,imgGO,COLOR_BGR2GRAY);
    cvtColor(imagenTriangulo,imgGT,COLOR_BGR2GRAY);    
    absdiff(imgGO,imgGT,resta);

    int pixel;
    int cont=0;
    int tope=0;
    int m=0;
    int n=0;
    Mat copia = imagen.clone();
    Mat copia2 = imagen.clone();
    
    for(int i=0;i<resta.rows;i++){
        for(int j=0;j<resta.cols;j++){
            pixel = resta.at<uchar>(i,j);
            Vec3b pixel2 = imgGO.at<Vec3b>(i,j);
            Vec3b pixelNegativo = Vec3b(255-pixel2[0],255-pixel2[1],255-pixel2[2]);
            copia2.at<Vec3b>(i,j)=pixelNegativo;            
            if(pixel>0){
                m=j;
                for(m;m<resta.cols;m++){
                    if(resta.at<uchar>(i,m)>0){
                        tope=m;
                    }
                }
                    n=j;
                    for(n; n<tope;n++){
                        resta.at<uchar>(i,n)=255;
                        Vec3b pixel2 = imagen.at<Vec3b>(i,j);
                        Vec3b pixelNegativo = Vec3b(255-pixel2[0],255-pixel2[1],255-pixel2[2]);
                        copia.at<Vec3b>(i,n)=pixelNegativo;  
                    }
                
            }
        }
    }

    resize(imagen,imagen,Size(800,600));
    resize(imagenTriangulo,imagenTriangulo,Size(800,600));
    resize(copia,copia,Size(800,600));
    resize(copia2,copia2,Size(800,600));
    imshow("Imagen",imagen);
    imshow("ImagenT",imagenTriangulo);
    imshow("Final",copia);    
    imshow("ImgNegativa",copia2);
    waitKey();
    destroyAllWindows();
}