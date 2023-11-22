#include "ses4headers.h"

int main ()
{
    double x0,y0,xc,yc,s,e0,radeq, a_ax,b_ax;    // xy coordinates and extrusion value and x and y increment for array
    int nsides, checkbed;

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
    //while(checkbed == 0)
    //{
        cout<<"\nEnter number of sides of the polygon: ";
        cin>>nsides;
        cout<<"\nEnter the x and y coordinates of the polygon center: ";
        cin>>xc>>yc;
        cout<<"\nEnter side length of the polygon: ";
        cin>>s;
        radeq = s/(2*sin(pi/nsides));
        cout<<"\n equivalent radius is: "<<radeq<<endl;
        checkbed = check_bounds(xc,yc,radeq);
        cout<<"\n checkbed is: "<<checkbed<<endl;
    //}
    
    e0 = make_polygon(nsides,xc,yc,s,e0);


    checkbed = 0;
    //while(checkbed == 0)
    //{
        cout<<"\nEnter the x and y coordinates of the center of the circle: ";
        cin>>xc>>yc;
        cout<<"\nEnter the radius of the circle: ";
        cin>>s;
        checkbed = check_bounds(xc,yc,s);
        cout<<"\n checkbed is: "<<checkbed<<endl;
    //}

    e0 = make_circle(xc,yc,s,e0);

    cout<<"\n\nThe final e0 value is: "<<e0<<endl;

    checkbed = 0;
    //while(checkbed == 0)
    //{
        cout<<"\nEnter the x and y coordinates of the center of the ellipse: ";
        cin>>xc>>yc;
        cout<<"\nEnter the major and minor axes of the ellipse: ";
        cin>>a_ax>>b_ax;
        radeq = a_ax;
        if(b_ax>a_ax)
            radeq = b_ax;
        checkbed = check_bounds(xc,yc,radeq);   // just use the longer axis
        cout<<"\n checkbed is: "<<checkbed<<endl;
    //}

    e0 = make_ellipse(xc,yc,a_ax,b_ax,e0);

    //Reading Bottom File
    read_bottom_file();

}