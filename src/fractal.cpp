#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

vector<int> converge(double, double, double, double);
vector<int> mandelbrot(double, double);

int width = 800;
int height = 450;
double center_x = 0;
double center_y = 0;
double zoom = 1;
Mat mdlbrot(height, width, CV_8UC3, Scalar(0,0,0));



void CallBackFunc(int event, int ii, int jj, int flags, void* userdata)
{

    int width = 800;
    int height = 450;

    Mat julia(height, width, CV_8UC3, Scalar(0,0,0));

    namedWindow( "Display window", WINDOW_AUTOSIZE );

    if  ( event == EVENT_LBUTTONDOWN )
    {
    //---------------------------------------------------

        double x = 2*(2.*ii-width)/width;  //x
        double y = -(16/9)*(2.*jj-height)/height;
        
        // zoom *2
        y = center_y + y/zoom ;
        x = center_x + x/zoom ;
        
        cout<<x<<"..."<<y<<endl;


        for(int i=0; i<julia.rows; i++){
            for(int j=0; j<julia.cols; j++){

                double s = -1*(2.*i-julia.rows)/julia.rows;
                double t = 2*(2.*j-julia.cols)/julia.cols;

                vector<int> values = converge(t,s,x,y);
                //cout<<value<<endl;


                Vec3b color = julia.at<Vec3b>(i,j); // get color-pixel
                color[0]=values[0];
                color[1]=values[1];
                color[2]=values[2];
                julia.at<Vec3b>(i,j) = color;
            }
        }
        imshow( "Display window", julia );
        waitKey(0);
        //--------------------------------------------------
    }

    if  ( event == EVENT_RBUTTONDOWN )
    {
    //---------------------------------------------------

		// window coordinates
        double x = 2*(2.*ii-width)/width; 
        double y = -(16/9)*(2.*jj-height)/height;
        
        // true coordinates
        x = x/zoom + center_x; 
		y = y/zoom + center_y;
		
		// new zoom value
		zoom = zoom*2;

        for(int i=0; i<mdlbrot.rows; i++){
            for(int j=0; j<mdlbrot.cols; j++){

				double t = 2*(2.*j-mdlbrot.cols)/mdlbrot.cols ;//x
                double s = -(16/9)*(2.*i-mdlbrot.rows)/mdlbrot.rows;//y

                // zoom *2
                s = y + s/zoom ;
                t = x + t/zoom ;


                vector<int> values = mandelbrot(t,s);


                Vec3b color = mdlbrot.at<Vec3b>(i,j); // get color-pixel
                color[0]=values[0];
                color[1]=values[1];
                color[2]=values[2];
                mdlbrot.at<Vec3b>(i,j) = color;
            }
        }
        center_x = x;
        center_y = y;
        
        imshow( "mouse window", mdlbrot );
        waitKey(0);
        //--------------------------------------------------
    }

}

int main(int argc, char *argv[])
{

    if (argc<3) return -1; // need 2 args
    double x = atof(argv[1]);
    double y = atof(argv[2]);
    

    for(int i=0; i<mdlbrot.rows; i++){
        for(int j=0; j<mdlbrot.cols; j++){

			double t = 2*(2.*j-mdlbrot.cols)/mdlbrot.cols ;//x
            double s = -(16/9)*(2.*i-mdlbrot.rows)/mdlbrot.rows;//y

            vector<int> values = mandelbrot(t,s);
            //cout<<value<<endl;


            Vec3b color = mdlbrot.at<Vec3b>(i,j); // get color-pixel
            color[0]=values[0];
            color[1]=values[1];
            color[2]=values[2];
            mdlbrot.at<Vec3b>(i,j) = color;
        }
    }

    namedWindow( "mouse window", WINDOW_AUTOSIZE );
    imshow( "mouse window", mdlbrot );
    setMouseCallback("mouse window", CallBackFunc, NULL);
    

    waitKey(0);
    return 0;


}



vector<int> converge(double s, double t, double x, double y){

    double sn = s;
    double tn = t;

    double d1 = (sn)*(sn);
    double d2 = (tn)*(tn);

    int i = 0;

    int j = 0;
    int k = 0;

    while(true){

        double zn = sn*sn - tn*tn + x;
        double wn = 2*sn*tn + y;

        d1 = (zn)*(zn);
        d2 = (wn)*(wn);

        if(d1+d2>100) break;
        if(i>254) break; //-->inside d1+d2 small
        i++;

        if(d2<10 ) k++;
        if(d1<10 ) j++;


        sn = zn;
        tn = wn;
    }


    vector<int> values(3);
    values[0]=i;
    values[1]=j;
    values[2]=k;

    return values;
}

vector<int> mandelbrot(double s, double t){

    double sn = s;
    double tn = t;

    double d1 = (sn)*(sn);
    double d2 = (tn)*(tn);

    int i = 0;

    int j = 0;
    int k = 0;

    while(true){

        double zn = sn*sn - tn*tn + s;
        double wn = 2*sn*tn + t;

        d1 = (zn)*(zn);
        d2 = (wn)*(wn);

        if(d1+d2>100) break;
        if(i>254) break; //-->inside d1+d2 small
        i++;

        if(d2<10 ) k++;
        if(d1<10 ) j++;


        sn = zn;
        tn = wn;
    }


    vector<int> values(3);
    values[0]=i;
    values[1]=j;
    values[2]=k;

    return values;
}

