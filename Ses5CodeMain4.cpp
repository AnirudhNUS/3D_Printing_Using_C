#include "ses5headers.h"

int main ()
{
    double x0,y0,e0;

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
    
    // e0 = make_stick_row(e0);

    // e0 = make_base(e0);

    e0 = make_pegs(e0);

    cout<<"\n\nThe final e0 value is: "<<e0<<endl;

    //Reading Bottom File
    read_bottom_file();

}