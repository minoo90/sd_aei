//#include <QCoreApplication>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <bitset>
#include <math.h>

int GenerateCodeFromPassword(std::string);
int SumOfDigits ( int);
unsigned char rotate ( unsigned char, int);
unsigned char rotateRevers( unsigned char, int);
void showImages ( int , ...);
IplImage* stage2 ( IplImage* , std::string );
IplImage* stage2Reverse ( IplImage* , std::string );
IplImage* cycling(IplImage* ) ;
void cycleRight(IplImage* ,IplImage* ,int );
void cycleLeft(IplImage* ,IplImage* ,int );
IplImage* upShift(IplImage* );
IplImage* downShift(IplImage* );
IplImage* rightShift(IplImage* ) ;
IplImage* leftShift(IplImage* );
IplImage* leftDiagonal_Randomization(IplImage* );
IplImage* rightDiagonal_Randomization(IplImage* );
IplImage* stage4 ( IplImage* , std::string );
IplImage* stage4Reverse ( IplImage* , std::string );
int findDivdeInModulo ( int, int );
void createSeftInvertibleMatrix(int [][2] ,int [][4]);
IplImage* positionalManipulating( IplImage * );
void multiply (uchar[][4], uchar[][4] );
IplImage* extendedHillCipher ( IplImage*  );
IplImage* stage3 ( IplImage* , std::string );
IplImage* stage3Reverse ( IplImage* , std::string );
IplImage* encrypt ( IplImage* , std::string );
IplImage* decrypt ( IplImage* , std::string );
void transpose (uchar[][4] );
void createKeyMatrix(std::string );

int blocksize = 4;
int modulo = 256;
int key [][4] = {
    {55,250,148,12},
    {106,171,44,172},
    {28,125,201,6},
    {53,86,150,85}
};

void test()
{
    int n = 4;
    IplImage* img = cvCreateImage( cvSize(n,n) ,IPL_DEPTH_8U ,1 );
    uchar* ptr = (uchar*)(img->imageData);

    for(int i = 0 ; i< n*n ; i++)
    {
        ptr[i] = i+1;
    }

    for( int i =0 ; i < n*n ;i++)
    {
        if ( i % n == 0 )
            std::cout<<std::endl;
        std::cout << std::setw(4) <<(int) ptr[i];
    }
    std::cout<<std::endl << "\n after cycling: "<< std::endl;

    IplImage* img1 = extendedHillCipher(img);
    IplImage* img2 = extendedHillCipher(img1);

    ptr = (uchar*)(img2->imageData);
    for( int i =0 ; i < n*n ;i++)
    {
        if ( i % n == 0 )
            std::cout<<std::endl;
        std::cout << std::setw(4) <<(int) ptr[i];
    }
    std::cout<<std::endl;

}

void test2 ()
{
    uchar ch = 150;
    uchar ch2 = rotate(ch,2);
    uchar ch3 = rotateRevers(ch2,2);

    std::bitset<8> x(ch);
    std::bitset<8> y(ch2);
    std::bitset<8> z(ch3);
    std::cout<< x<< "   "<<  y <<"   "<<  z << std::endl ;
}

int main (int argc, char *argv[])
{
//        test();
//        return 0;
    std::cout << ( 7 / 4 ) * 4 << std::endl;
    std::string password = "sumer2013";
    //    int code = GenerateCodeFromPassword(password);
    //    std::cout << "   code = " << code << " Lr = "<< password.length() % 7 << std::endl;

    IplImage* img = cvLoadImage(argv[1],CV_LOAD_IMAGE_COLOR);
    std::cout << " image size = " <<  img->width << "*" << img->height << "\n password = " << password << std::endl;
    IplImage * temp = cvCreateImage(cvSize((int)pow(2,floor(log2(img->width))),(int)pow(2,floor(log2(img->height)))),img->depth,img->nChannels);
    cvResize(img,temp);
    std::cout << " temp size = " <<  temp->width << "*" << temp->height << std::endl;
    IplImage* grayImage = cvCreateImage(cvGetSize(temp),IPL_DEPTH_8U,1);
    cvCvtColor(temp,grayImage,CV_BGR2GRAY);
    //    std::cout << " channel sequence for img1 = " << img->channelSeq << "  img2 = " << grayImage->channelSeq << std::endl;


    IplImage* encryptedImage = encrypt(grayImage,password);
    IplImage* decryptedImage = decrypt(encryptedImage,password);
    showImages( 3 ,grayImage ,encryptedImage ,decryptedImage );
    cvSaveImage("encrypted.jpg",encryptedImage);
}

IplImage* encrypt ( IplImage* input , std::string password)
{
    IplImage* stage2Image = stage2(input,password);
    IplImage* stage3Image = stage3(stage2Image,password);
    IplImage* stage4Image = stage4(stage3Image,password);
    return stage4Image;
}

IplImage* decrypt ( IplImage* input , std::string password)
{
    IplImage* stage4Image = stage4Reverse(input,password);
    IplImage* stage3Image = stage3Reverse(stage4Image,password);
    IplImage* stage2Image = stage2Reverse(stage3Image,password);
    return stage2Image;
}

IplImage* stage2 ( IplImage* input , std::string password)
{
    IplImage* output = cvCreateImage(cvGetSize(input),input->depth,input->nChannels);
    cvCopy(input,output);

    if ( password.length()%7 == 0)
        std::cout<< " exception : Lr = 0  then whole byte must reversed "<< std::endl;

    for (int i = 0; i < input->height; ++i)
    {
        uchar* ptrInput = (uchar *)( input->imageData + i * input->widthStep) ;
        uchar* ptrOutput = (uchar *)(output->imageData + i * output->widthStep) ;
        for( int j = 0 ; j < input->width; j++)
        {
            ptrOutput[j] = rotate(ptrInput[j],password.length());
        }
    }
    return output;
}
IplImage* stage2Reverse ( IplImage* input , std::string password)
{
    IplImage* output = cvCreateImage(cvGetSize(input),input->depth,input->nChannels);
    cvCopy(input,output);

    if ( password.length()%7 == 0)
        std::cout<< " exception : Lr = 0  then whole byte must reversed "<< std::endl;

    for (int i = 0; i < input->height; ++i)
    {
        uchar* ptrInput = (uchar *)( input->imageData + i * input->widthStep) ;
        uchar* ptrOutput = (uchar *)(output->imageData + i * output->widthStep) ;
        for( int j = 0 ; j < input->width; j++)
        {
            ptrOutput[j] = rotateRevers(ptrInput[j],password.length());
        }
    }
    return output;
}

unsigned char rotate ( unsigned char x, int n)
{
    std::bitset < 8 > output(x);
    std::bitset < 8 > xbitset(x);
    n = n % 7 ;
    output =  output << n ;
    if ( n == 0 )               // whole byte must reversed
    {
        n = 8;
    }
    for(int i = 0 ; i< n ;i++)
    {
        if ( xbitset[8-i-1] == 0)
            output[i] = 0;
        else
            output[i] = 1;
    }
    unsigned long i = output.to_ulong();
    return (unsigned char)( i );
}
unsigned char rotateRevers ( unsigned char x, int n)
{
    std::bitset < 8 > output(x);
    std::bitset < 8 > xbitset(x);
    n = n % 7 ;
    output =  output >> n ;
    if ( n == 0 )               // whole byte must reversed
    {
        n = 8;
    }
    for(int i = 0 ; i< n ;i++)
    {
        if ( xbitset[i] == 0)
            output[8-i-1] = 0;
        else
            output[8-i-1] = 1;
    }
    unsigned long i = output.to_ulong();
    return (unsigned char)( i );
}

int GenerateCodeFromPassword(std::string str)
{
    int N = 0;
    for ( uint i = 0 ; i< str.length(); i++)
    {
        N += pow(2,i+1) * (int) str[i];
    }
    return SumOfDigits(N);
}

int SumOfDigits ( int N)
{
    int code = 0;
    while ( N > 0 )
    {
        code+= N %10;
        N = N / 10;
    }
    return code;
}
void showImages ( int count , ...)
{
    va_list arguments;
    va_start(arguments, count); //Requires the last fixed parameter (to get the address)
    char name[10]  = "Image0";
    IplImage * tempImage;
    for(int j=0; j<count; j++)
    {
        tempImage = va_arg(arguments,IplImage*) ;
        name[5]++;
        cvNamedWindow((char*) name );
        cvShowImage( name, tempImage );
    }
    cvWaitKey( 0 );
    cvReleaseImage( &tempImage);
    while(name[5] != '0')
    {
        cvDestroyWindow( name );
        name[5]--;
    }

    va_end(arguments);
}

IplImage* cycling(IplImage* input) // assume that input image in N*N
{
    IplImage* output = cvCreateImage(cvGetSize(input),input->depth,input->nChannels);
    //    scvCopy(input,output);

    for(int i = 0 ; i < blocksize / 2 ; i++)
    {
        if ( i % 2 == 0)
            cycleRight(input,output,i);
        else
            cycleLeft(input,output,i);
    }
    return output;
}
IplImage* cyclingReverse(IplImage* input) // assume that input image in N*N
{
    IplImage* output = cvCreateImage(cvGetSize(input),input->depth,input->nChannels);
    //    scvCopy(input,output);

    for(int i = 0 ; i < blocksize / 2 ; i++)
    {
        if ( i % 2 == 1)
            cycleRight(input,output,i);
        else
            cycleLeft(input,output,i);
    }
    return output;
}

void cycleRight(IplImage* input,IplImage* output, int n)
{
    if ( n >= blocksize / 2 )
    {
        std::cout<< " n is bigger than blocksize / 2 ; so cycleRight could not to be applyed " << std::endl;
        return;
    }
    for ( int i = 0 ; i < input->height ; i += blocksize)
    {
        for ( int j = 0 ; j < input->width ; j+= blocksize)
        {
            uchar* ptrInput = ( uchar * ) ( input->imageData + i * input->widthStep + j);
            uchar* ptrOutput = ( uchar * ) ( output->imageData + i * output->widthStep + j);
            ptrInput += n * input->widthStep + n ;
            ptrOutput += n * output->widthStep + n ;

            for ( int k = 1 ; k < blocksize - 2 * n; k++)
            {
                ptrOutput[k] = ptrInput[k - 1];
            }
            for ( int k = 0 ; k < blocksize - 2 * n - 1 ; k++ )
            {
                ptrOutput[(k+1) * output->widthStep + blocksize- 2 * n-1] = ptrInput[k * input->widthStep + blocksize-2 * n-1];
                ptrOutput[ k * output->widthStep ] = ptrInput[(k+1) * input->widthStep];
            }

            for ( int k = 0 ; k < blocksize - 2 * n - 1 ; k++ )
            {
                ptrOutput[(blocksize - 2 * n - 1) * output->widthStep + k] = ptrInput[(blocksize - 2 * n - 1) * input->widthStep + k+1];
            }
        }
    }
}

void cycleLeft(IplImage* input,IplImage* output, int n)
{

    if ( n >= blocksize / 2 )
    {
        std::cout<< " n is bigger than blocksize / 2 ; so cycleLeft could not to be applyed " << std::endl;
        return;
    }
    for ( int i = 0 ; i < input->height ; i += blocksize)
    {
        for ( int j = 0 ; j < input->width ; j+= blocksize)
        {
            uchar* ptrInput = ( uchar * ) ( input->imageData + i * input->widthStep + j);
            uchar* ptrOutput = ( uchar * ) ( output->imageData + i * output->widthStep + j);
            ptrInput += n * input->widthStep + n ;
            ptrOutput += n * output->widthStep + n ;

            for ( int k = 1 ; k < blocksize - 2 * n; k++)
            {
                ptrOutput[k - 1] = ptrInput[k];
            }
            for ( int k = 0 ; k < blocksize - 2 * n - 1 ; k++ )
            {
                ptrOutput[k * output->widthStep + blocksize- 2 * n-1] = ptrInput[(k + 1) * input->widthStep + blocksize-2 * n-1];
                ptrOutput[ (k+1) * output->widthStep ] = ptrInput[k * input->widthStep];
            }

            for ( int k = 0 ; k < blocksize - 2 * n - 1 ; k++ )
            {
                ptrOutput[(blocksize - 2 * n - 1) * output->widthStep + k + 1] = ptrInput[(blocksize - 2 * n - 1) * input->widthStep + k];
            }
        }
    }
}

IplImage* upShift(IplImage* input) // assume that input image in N*N
{
    IplImage* output = cvCreateImage(cvGetSize(input),input->depth,input->nChannels);
    //    cvCopy(input,output);

    for ( int i = 0 ; i < input->height ; i++)
    {
        uchar* ptrInput ;
        uchar* ptrOutput = (uchar *)( output->imageData + i * output->widthStep ) ;

        if( i % blocksize != blocksize - 1)
            ptrInput = (uchar *)( input->imageData +( i + 1 ) * input->widthStep ) ;
        else
            ptrInput = (uchar *)( input->imageData +( ( i / blocksize) * blocksize) * input->widthStep ) ;

        for ( int j = 0 ; j < input->width ; j++)
        {
            ptrOutput[j] = ptrInput[j];
        }

    }
    return output;
}

IplImage* downShift(IplImage* input) // assume that input image in N*N
{
    IplImage* output = cvCreateImage(cvGetSize(input),input->depth,input->nChannels);
    //    cvCopy(input,output);


    for ( int i = 0 ; i < input->height ; i++)
    {
        uchar* ptrInput ;
        uchar* ptrOutput = (uchar *)( output->imageData + i * output->widthStep ) ;

        if( i % blocksize != 0)
            ptrInput = (uchar *)( input->imageData +( i - 1 ) * input->widthStep ) ;
        else
            ptrInput = (uchar *)( input->imageData +( ( i + blocksize - 1) * input->widthStep )) ;

        for ( int j = 0 ; j < input->width ; j++)
        {
            ptrOutput[j] = ptrInput[j];
        }
        //        std::cout << i << "  " << (int) ptrInput[0]  <<  std::endl;
    }
    return output;
}
IplImage* rightShift(IplImage* input) // assume that input image in N*N
{
    IplImage* output = cvCreateImage(cvGetSize(input),input->depth,input->nChannels);

    uchar* ptrInput = (uchar *)( input->imageData ) ;
    uchar* ptrOutput = (uchar *)( output->imageData ) ;
    for ( int i = 0 ; i < input->height ; i++)
    {
        for ( int j = 0 ; j < input->width ; j++)
        {
            if ( j % blocksize == 0 )
                ptrOutput[j] = ptrInput[j + blocksize - 1];
            else
                ptrOutput[j] = ptrInput[j - 1];
        }
        ptrInput += input->widthStep;
        ptrOutput += output->widthStep;
    }
    return output;
}

IplImage* leftShift(IplImage* input) // assume that input image in N*N
{
    IplImage* output = cvCreateImage(cvGetSize(input),input->depth,input->nChannels);

    uchar* ptrInput = (uchar *)( input->imageData ) ;
    uchar* ptrOutput = (uchar *)( output->imageData ) ;
    for ( int i = 0 ; i < input->height ; i++)
    {
        for ( int j = 0 ; j < input->width ; j++)
        {
            if ( j % blocksize == blocksize - 1 )
                ptrOutput[j] = ptrInput[( j / blocksize) * blocksize];
            else
                ptrOutput[j] = ptrInput[j + 1];
        }
        ptrInput += input->widthStep;
        ptrOutput += output->widthStep;
    }
    return output;
}

IplImage* leftDiagonal_Randomization(IplImage* input) // assume that input image in N*N
{
    IplImage* output = cvCreateImage(cvGetSize(input),input->depth,input->nChannels);
    cvCopy(input,output);

    uchar* ptrInput ;
    uchar* ptrOutput ;
    for ( int i = 0 ; i < input->height ; i += blocksize)
    {
        for ( int j = 0 ; j < input->width ; j++ )
        {
            if ( j % blocksize == 0 )
            {
                ptrInput = (uchar *)( input->imageData + ( i + 1) * input->widthStep ) ;
                ptrOutput = (uchar *)( output->imageData + i * output->widthStep ) ;
                ptrOutput[j] = ptrInput[j+1];
                ptrInput += input->widthStep;
                ptrOutput += output->widthStep;
            }
            else if ( j % blocksize == blocksize - 1 )
            {
                ptrInput = (uchar *)( input->imageData +  i * input->widthStep ) ;
                ptrOutput[j] = ptrInput[ ( j / blocksize) * blocksize];
            }
            else
            {
                ptrOutput[j] = ptrInput[j+1];
                ptrInput += input->widthStep;
                ptrOutput += output->widthStep;
            }
        }
    }
    return output;
}

IplImage* rightDiagonal_Randomization(IplImage* input) // assume that input image in N*N
{
    IplImage* output = cvCreateImage(cvGetSize(input),input->depth,input->nChannels);
    cvCopy(input,output);

    uchar* ptrInput ;
    uchar* ptrOutput ;
    for ( int i = 0 ; i < input->height ; i += blocksize)
    {
        for ( int j = input->width - 1 ; j >= 0 ; j--)
        {
            if ( j % blocksize == blocksize - 1)
            {
                ptrInput = (uchar *)( input->imageData + ( i + blocksize - 1 ) * input->widthStep ) ;
                ptrOutput = (uchar *)( output->imageData + i * output->widthStep ) ;

                ptrOutput[j] = ptrInput[j - blocksize + 1];
                ptrOutput+= output->widthStep ;
                ptrInput = (uchar *)( input->imageData + i * input->widthStep ) ;
            }
            else
            {
                //                std::cout << j << " ," << j + 1 << std::endl;
                ptrOutput[j] = ptrInput[ j + 1 ] ;

                ptrInput += input->widthStep;
                ptrOutput += output->widthStep;
            }
        }
    }
    return output;
}

IplImage* stage4 ( IplImage* input , std::string password )
{
    int code = GenerateCodeFromPassword(password);
    IplImage * temp = cycling(input);
    temp = upShift(temp);
    temp = rightShift(temp);
    temp = leftDiagonal_Randomization(temp);
    for ( int i = 0 ; i < code ; i++)
        temp = cycling(temp);
    temp = downShift(temp);
    temp = leftShift(temp);
    temp = rightShift(temp);
    return temp;
}

IplImage* stage4Reverse ( IplImage* input , std::string password )
{
    int code = GenerateCodeFromPassword(password);
    IplImage * temp = leftShift(input);
    temp = rightShift(temp);
    temp = upShift(temp);
    for ( int i = 0 ; i < code ; i++)
        temp = cyclingReverse(temp);
    for ( int i = 0 ; i < blocksize - 1 ; i++)
        temp = leftDiagonal_Randomization(temp);
    temp = leftShift(temp);
    temp = downShift(temp);
    temp = cyclingReverse(temp);
    return temp ;
}

void createSeftInvertibleMatrix(int input[][2] ,int output[][4])
{
    int n = 2;
    for(int i = 0 ; i < n ; i++)
    {
        for ( int j = 0 ; j < n ; j++)
        {
            output[i][j] =  modulo -(modulo + input[i][j] % modulo ) % modulo;
            output[i+n][j+n] = (modulo + input[i][j] % modulo ) % modulo;
        }
    }
    int k = 3;
    for ( int i = 0 ; i < n ; i++)
    {
        for ( int j = 0 ; j < n ; j++)
        {
            if ( i != j)
            {
                output[i][j+n] = ( k * (modulo + input[i][j] % modulo ) % modulo ) % modulo;
                output[i+n][j] = findDivdeInModulo( modulo - (modulo + input[i][j] % modulo ) % modulo , k);   // check to have divde
            }
            else
            {
                output[i][j+n] = ( k * (1 + (modulo + input[i][j] % modulo ) % modulo ) ) % modulo;
                output[i+n][j] = findDivdeInModulo( 1 + modulo - (modulo + input[i][j] % modulo ) % modulo , k);
            }
        }
    }
}
int findDivdeInModulo ( int x, int d )
{
    for ( int i = 1 ; i < modulo ; i++)
    {
        if ( x == ( d * i ) % modulo)
        {
            return i ;
        }
    }
    std::cout << "\n find " << x << " / " << d << " int modulo " << modulo<< " = " ;
    std::cout << " not found :( " << std::endl;
    return 0;
}

IplImage* positionalManipulating( IplImage * input )
{
    IplImage * temp = cvCreateImage(cvGetSize(input),input->depth,input->nChannels);
    int n = log2(input->height);
    for ( int i = 0 ; i < input->height ; i++)
    {
        std::bitset <15> rev ( i );
        for ( int j = 0 ;  j < n/2 ; j++)
        {
            //            std::cout << "rev[" << j << "] = " << rev[j] << " rev[" << n-j-1 << "] = " << rev[n-j-1] << std::endl;
            if ( rev[j] != rev[n-j-1])
            {
                rev[j] = rev[n-j-1] ;
                rev[n-j-1] = ! rev[j];
            }
            else
            {
            }
        }
        int row = rev.to_ulong();
        //        std::cout << " row " << i << " changed with " << row << "   n = " << n << std::endl;
        uchar* ptrSource = (uchar*)(input->imageData + i * input->widthStep);
        uchar* ptrDestination = (uchar*)( temp->imageData + row * temp->widthStep);
        for( int j = 0 ; j < input->width ; j++)
        {
            ptrDestination[j] = ptrSource[j];
        }
    }

    IplImage * output = cvCreateImage(cvGetSize(temp),temp->depth,temp->nChannels);
    n = log2(temp->width);
    for ( int i = 0 ; i < temp->width ; i++)
    {
        std::bitset <15> rev ( i );
        for ( int j = 0 ;  j < n/2 ; j++)
        {
            //            std::cout << "rev[" << j << "] = " << rev[j] << " rev[" << n-j-1 << "] = " << rev[n-j-1] << std::endl;
            if ( rev[j] != rev[n-j-1])
            {
                rev[j] = rev[n-j-1] ;
                rev[n-j-1] = ! rev[j];
            }
            else
            {
            }
        }
        int column = rev.to_ulong();
        //        std::cout << " column " << i << " changed with " << column  << "   n = " << n << std::endl;
        uchar* ptrSource = (uchar*)(temp->imageData );
        uchar* ptrDestination = (uchar*)( output->imageData );
        for( int j = 0 ; j < temp->height ; j++)
        {
            ptrDestination[column] = ptrSource[i];
            ptrSource += temp->widthStep;
            ptrDestination += output->widthStep;
        }
    }
    return output;

}

void print (uchar a [4][4] )
{
    for ( int i = 0 ; i < 4 ; i++)
    {
        for ( int j = 0 ; j < 4 ; j++)
        {
            std::cout <<(int) a[i][j] << "  ";
        }
        std::cout<<std::endl;
    }
    std::cout << std::endl << std::endl;
}

IplImage* extendedHillCipher ( IplImage* input )
{
    IplImage* output = cvCreateImage(cvGetSize(input),input->depth,input->nChannels);

    uchar array1 [4][4];
    uchar array2 [4][4];
    uchar array3 [4][4];

    for ( int i = 0 ; i < input->height ; i+= blocksize)
    {
        uchar * ptrInput = (uchar * ) ( input->imageData + i * input->widthStep);
        uchar * ptrOutput = (uchar * ) ( output->imageData + i * output->widthStep);
        for ( int j = 0 ; j < input->width ; j+= blocksize)
        {
            for ( int m = 0 ; m < blocksize ; m++)
            {
                for ( int n = 0 ; n < blocksize ; n++)
                {
                    array1[m][n] = ptrInput[m*input->widthStep + j + n ] ;

                }
            }
            transpose(array1);
            multiply ( array1 , array2);
            transpose(array2);
            multiply(array2,array3);

            for ( int m = 0 ; m < blocksize ; m++)
            {
                for ( int n = 0 ; n < blocksize ; n++)
                {
                    ptrOutput[m*input->widthStep + j + n ] = array3[m][n];
                }
            }
        }
    }

    return output;
}

void transpose ( uchar array[][4])
{
    for ( int i = 0 ; i < blocksize ; i++)
    {
        for ( int j = i+1 ; j < blocksize ; j++)
        {
            uchar temp = array[i][j];
            array[i][j] = array[j][i];
            array[j][i] = temp;
        }
    }
}

void multiply ( uchar input [4][4], uchar output [4][4] )
{
    for( int i = 0 ; i < blocksize ; i++)
    {
        for ( int j = 0 ; j < blocksize ;j++)
        {
            uchar sum = 0 ;
            for ( int k = 0 ; k < blocksize ; k++)
            {
                sum += ( key[i][k] * input[k][j]) ;
            }
            output [i][j] = sum % modulo ;
        }
    }
}

IplImage* stage3 ( IplImage* input , std::string password)
{
    createKeyMatrix(password);
    //    create key matrix ; invertible matrix
    IplImage* temp = positionalManipulating( input);
    IplImage* output = extendedHillCipher(temp);

    return output;
}
IplImage* stage3Reverse( IplImage* input , std::string password)
{
    createKeyMatrix(password);
    //    create key matrix ; invertible matrix
    IplImage* temp = extendedHillCipher( input);
    IplImage* output = positionalManipulating(temp);

    return output;
}
void createKeyMatrix(std::string password)
{
    int pass [2][2]  = {{140,130},{13,230}};
    for ( int i = 0 ; i < password.length(); i++)
    {
        if ( i % blocksize == 0)
        {
            pass[0][0] += (int) password[i];
            pass[0][0] = pass[0][0] % modulo;
        }
        else if ( i % blocksize == 1)
        {
            pass[0][1] += (int) password[i];
            pass[0][1] = pass[0][1] % modulo;
        }
        else if ( i % blocksize == 2)
        {
            pass[1][0] += (int) password[i];
            pass[1][0] = pass[1][0] % modulo;
        }
        else
        {
            pass[1][1] += (int) password[i];
            pass[1][1] = pass[1][1] % modulo;
        }
    }
    createSeftInvertibleMatrix(pass,key);
}
