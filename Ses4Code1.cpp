#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

string gcodeSes4;   // Filename to write the gcode in
string line;        // read and write lines
fstream fileRead;   // File to read top and bottom
fstream fileMain;   // File to write into
const double pi = 3.14159;
const double er = 0.013161;

void read_top_file()
{
    fileRead.open("top_filler.txt", ios::in);
    fileMain.open(gcodeSes4, ios::out);   // truncate for the top fill
    cout<<"Reading from top filler file\n";
    while (getline(fileRead,line))
    {
            fileMain<<line<<endl;
            cout<<line<<endl;
    }
    fileRead.close(); 
    cout<<"\nTop filler file finished\n";

    fileMain.close();
}

void read_bottom_file()
{
    fileRead.open("bottom_filler.txt", ios::in);
    fileMain.open(gcodeSes4, ios::app);   // append to add bottom
    
    cout<<"\nReading from bottom filler file\n";
    fileMain<<endl;    // give some extra space

    while (getline(fileRead,line))
    {
        fileMain<<line<<endl;
        cout<<line<<endl;
    }
    fileRead.close(); 
    cout<<"\nBottom filler file finished";

    fileMain.close();
}

double make_polygon(int numsides, double xcen, double ycen, double side, double e)
{
    // function to make a regular polygon at given center xcen,ycen number of sides and side lenght
    // need the initial extrusion position and the final extrusion position needs to be returned
    double r, theta, ang, x, y;  // r = circum radius along which all points are. xy coordinates are for writing it on 
    theta = pi/numsides;     // theta = (360/numsides)/2 = 180/numsides or pi/numsides in radians
    r = side/(2*sin(theta));   // circumradius

    cout<<"\nMaking Polygon\n";

    fileMain.open(gcodeSes4, ios::app);   // append to add the polygon
    
    x = xcen + r;
    y = ycen;
    fileMain<<"\nG1 X"<<x<<" Y"<<y<<" E"<<e;   // go to the starting point
    cout<<"\nG1 X"<<x<<" Y"<<y<<" E"<<e;   

    for(int i = 1; i<=numsides; i++)
    {
        ang = (i*2*pi)/numsides;  // angle for current point. ends at 2*pi (0 again)
        x = xcen + r*cos(ang);
        y = ycen + r*sin(ang);
        e = e + side*er;        // add to extrusion value

        fileMain<<"\nG1 X"<<x<<" Y"<<y<<" E"<<e;   // writing all the points
        cout<<"\nG1 X"<<x<<" Y"<<y<<" E"<<e;   
    }

    fileMain.close();

    return e;    // return the e value
}

int main ()
{
    double x0,y0,xc,yc,s,e0;    // xy coordinates and extrusion value and x and y increment for array
    int nsides;

    cout<<"Enter the name of the file: ";
    cin>>line;
    gcodeSes4 = line + ".gcode";

    // Reading Top File   
    read_top_file();

    // write middle section of code
    
    e0 = 0;
    x0 = 10;
    y0 = 10;

    fileMain.open(gcodeSes4, ios::app);
    fileMain<<"\nG1 F1200 X"<<x0<<" Y"<<y0<<" E"<<e0<<" \n";  // setting original position and speed
    fileMain.close();

    cout<<"\nEnter number of sides of the polygon: ";
    cin>>nsides;
    cout<<"\nEnter the x and y coordinates of the polygon center: ";
    cin>>xc>>yc;
    cout<<"\nEnter side length of the polygon: ";
    cin>>s;

    e0 = make_polygon(nsides,xc,yc,s,e0);

    cout<<"\nThe final e0 value is: "<<e0;

    //Reading Bottom File
    read_bottom_file();

}