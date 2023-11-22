#include "ses4headers.h"

int main ()
{
    double x0,y0,xc,yc,s,e0,radeq,a_ax,b_ax,w;    
    int nsides, checkbed, ch;
    char cont;

    cout<<"Enter the name of the file: ";
    cin>>line;
    gcodeSes4 = line + ".gcode";

    // Reading Top File   
    read_top_file();

    // write middle section of code
    
    e0 = 0;
    x0 = 10;
    y0 = 10;
    z = 0.2;   // current z value

    fileMain.open(gcodeSes4, ios::app);
    fileMain<<"\nG1 F1200 X"<<x0<<" Y"<<y0<<" E"<<e0<<" \n";  // setting original position and speed
    fileMain.close();

    checkbed = 0;
    cont = 'y';

    while(cont == 'y')
    {
        cout<<"\nWhat shape would you like to fill?";
        cout<<"\n1. Circle \n2. Ellipse \n3. Polygon \nEnter the choice number: ";
        cin>>ch;
        
        if (ch == 1)
            e0 = fill_circ(e0);

        if (ch == 2)
            e0 = fill_ellipse(e0);
        
        if (ch == 3)
            e0 = fill_polygon(e0);

        cout<<"\nWould you like to continue? (y/n) ";
        cin>>cont;
    }


    cout<<"\n\nThe final e0 value is: "<<e0<<endl;

    //Reading Bottom File
    read_bottom_file();

}