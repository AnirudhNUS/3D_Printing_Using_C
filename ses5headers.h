#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

string gcodeSes4;   // Filename to write the gcode in
string line;        // read and write lines
fstream fileRead;   // File to read top and bottom
fstream fileMain;   // File to write into
const double pi = 3.14159265;
const double er = 0.01504143;
double z;      // current z height dependent on th layer

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

int check_bounds(double xcen, double ycen, double rad_eq)    // checks if it is within the bounds of the print bed
{       // rad_eq is the equivalent radius regardless of the kind of shape.
    // note: the boundaries for Ultimaker S5 printer are:
    // x (10,320) since bed size is 330   AND  y (10,230) since bed size is 240   
    double xup, yup, xd, yd;
    int is_ok = 0;
    xup = xcen + rad_eq;
    yup = ycen + rad_eq;
    xd = xcen - rad_eq;
    yd = ycen - rad_eq;

    if (xup>320)
        cout<<"\nThe x value exceeds boundary\n";
    else if (yup>230)
        cout<<"\nThe y value exceeds boundary\n";
    else if (xd<10)
        cout<<"\nThe x value gets too low\n";
    else if (yd<10)
        cout<<"\nThe y value gets too low\n";
    else
    {
        cout<<"\nThe print is within boundaries\n";
        is_ok = 1;
    }
    
    return is_ok;

}

double dist_calc(double oldp[2], double newp[2])    // points old x1,y1 and new x2,y2
{
    double dist, xgap, ygap;
    xgap = newp[0] - oldp[0];
    ygap = newp[1] - oldp[1];
    dist = sqrt((xgap*xgap) + (ygap*ygap));    // dist = sqrt(dx^2 + dy^2)

    return dist;
}

struct rect
{
    // variables
    double c[2], l, b, pts[4][2], dis[4];    
    // c = bottom left corner   lb length and breadth   pts are the 4 vertices in order

    // functions

    void set_vertices()
    {   // start from 2nd point since c[] is already bottom left corner
        pts[0][0] = c[0] + l;
        pts[0][1] = c[1];           // point 1 (10 bottom right)
        dis[0] = l;
        
        pts[1][0] = c[0] + l;
        pts[1][1] = c[1] + b;       // point 2 (11 top right)
        dis[1] = b;
        
        pts[2][0] = c[0];
        pts[2][1] = c[1] + b;       // point 3 (01 top left)
        dis[2] = l;
        
        pts[3][0] = c[0];
        pts[3][1] = c[1];           // point 4 (00 bottom left)
        dis[3] = b;
        // use these 4 points to make rectangle easily using loop
    }
};


double make_rect(rect a, double e)
{
    // function to make a rectangle from a rectangle structure variable
    // need the initial extrusion position and the final extrusion position needs to be returned
    double x, y, zraise;  // xy coordinates are for writing it on
    // zraise is the z height we raise to when doing the moves   

    // cout<<"\nMaking Rectangle\n";

    fileMain.open(gcodeSes4, ios::app);   // append to add the polygon
    
    x = a.c[0];
    y = a.c[1];
    zraise = z + 2; // raise 2mm up from the current level
    fileMain<<"\nG1 F1000 Z"<<zraise;   // raise for move
    fileMain<<"\nG1 F1500 X"<<x<<" Y"<<y<<" E"<<e;   // go to the starting point with fast move
    fileMain<<"\nG1 F1200 Z"<<z;   // back to current level and ready for printing speed
    
    // cout<<"\nG1 X"<<x<<" Y"<<y<<" E"<<e;  

    a.set_vertices();   // set vertices and distances to the 4 values 

    for(int i = 0; i<4; i++)
    {
        x = a.pts[i][0];
        y = a.pts[i][1];
        e = e + a.dis[i]*er;   // add the corresponding distance to it

        fileMain<<"\nG1 X"<<x<<" Y"<<y<<" E"<<e;   // writing all the points
        //cout<<"\nG1 X"<<x<<" Y"<<y<<" E"<<e;   
    }
    
    fileMain<<endl;     // leave gap after completion

    fileMain.close();

    return e;    // return the e value
}


double fill_rect(rect orig, double w, double e)  // w is the width used (typically 0.2mm)
{   
    rect a;
    int num;
    double ratio, d, xc, yc;

    ratio = orig.b/(2*w);    // since along the shorter length, we can go 2 times
    
    num = floor(ratio);   // max number of loops

    a = orig;

    for(int i=0;i<num;i++)
    {
        e = make_rect(a,e);
        // cout<<"\nE value after "<<i<<"th rectangle: "<<e;
        a.b = a.b - (2*w);
        a.l = a.l - (2*w);  // reduce length and breadth by 2 thicknesses
        a.c[0] = a.c[0] + w;
        a.c[1] = a.c[1] + w;   // add w to both centers

        // cout<<"\nLength and Breadth after "<<i<<"th rectangle: "<<a.l<<" and "<<a.b<<endl;
    }
    
    if(a.b>(w/2))
    {
        cout<<"\nMaking the inner point\n";
        d = (a.b*a.l)/w;  // effective area
        cout<<"\nEffective length is: "<<d<<endl;
        e = e + d*er;    // amount to purge in the center

        fileMain.open(gcodeSes4, ios::app);   // append to add the center point

        xc = a.c[0] + (orig.l-a.l)/2 + w;   // left start point
        yc = a.c[1] + orig.b/2;         // mid area

        fileMain<<"\nG1 X"<<xc<<" Y"<<yc;   // go to left point
        xc = xc + a.l - 2*w;   // end point
        fileMain<<"\nG1 X"<<xc<<" Y"<<yc<<" E"<<e;  // go to end point

        fileMain<<endl;  // leave gap after completion
        fileMain.close();
    }

    return e;    // return the e value
}


double make_stick_row(double e)  // make a row of n sticks
{
    int n, i, j, layers;
    double yd, h, w;
    // cout<<"\nHow many sticks do you want to make? ";
    // cin>>n;
    // rect *a = new rect[n];
    // cout<<"\nEnter length and breadth: ";
    // cin>>a[0].l>>a[0].b;
    // cout<<"\nEnter the coordinates of the bottom left corner of the first stick: ";
    // cin>>a[0].c[0]>>a[0].c[1];
    // cout<<"\nEnter y axis distance: ";
    // cin>>yd;

    string name1 = "stick_row_info.txt";
    cout<<"\nTaking information from text file "<<name1<<endl;

    fileRead.open(name1, ios::in);

    getline(fileRead,line);   // first line removed
    fileRead>>n;
    cout<<"\nThe number of sticks is: "<<n;
    rect *a = new rect[n];

    fileRead>>a[0].l>>a[0].b>>a[0].c[0]>>a[0].c[1]>>yd>>h>>w;

    //cout<<"\nAll info is:\n"<<n<<a[0].l<<a[0].b<<a[0].c[0]<<a[0].c[1]<<yd<<h<<w<<endl;

    fileRead.close();

    for(i=1;i<n;i++)
    {
        a[i].c[0] = a[i-1].c[0];
        a[i].c[1] = a[i-1].c[1] + yd;
        a[i].b = a[i-1].b;
        a[i].l = a[i-1].l;
    }

    // cout<<"\nEnter the stick height and layer height: ";
    // cin>>h>>w;
    layers = floor(h/w); // number of layers is height divided by layer height (or print width) w

    for(i=0;i<layers;i++)
    {
        z = i*w + w;   // current layer height starting from w
        cout<<"\nZ value: "<<z;
        for(j=0;j<n;j++)
        {
            e = fill_rect(a[j],w,e);
            cout<<"\nRectangle number "<<(j+1)<<" in layer "<<(i+1);
            cout<<"\nCoordinates: ("<<a[j].c[0]<<","<<a[j].c[1]<<")";
        }
    }
    
    delete [] a;   // ensure to delete a every time to use different values

    return e;
}


double mk_hole(rect id, rect od, double w, double e)  // w is the width used (typically 0.2mm)
{   // id = inner dimensions    //od = outer dimensions
    rect a;
    int i,j,num;
    double ratio, dif;
    dif = od.l-id.l;
    ratio = dif/(2*w);
    num = floor(ratio); // number of loops to be made 

    a = od;

    for(i=0;i<num;i++)
    {
        //cout<<"\nRectangle dims: \nL: "<<a.l<<"\nB: "<<a.b<<"\nCorner (x,y): ("<<a.c[0]<<","<<a.c[1]<<")";
        e = make_rect(a,e);
        a.l = a.l -(2*w);
        a.b = a.b -(2*w);
        a.c[0] = a.c[0] + w;
        a.c[1] = a.c[1] + w;
    }

    return e;
}

double make_base(double e)  // make the abacus foundation
{
    int n, i, j, layers;
    double w, h;   // layer height(w), height of the base (h)

    // cout<<"\nEnter length and breadth of inner hole: ";
    // cin>>id.l>>id.b;
    // cout<<"\nEnter length of outer dimension: ";
    // cin>>od.l;
    // cout<<"\nEnter the bottom left corner of the outer dimension: ";
    // cin>>od.c[0]>>od.c[1];

    string name1 = "base_info.txt";
    cout<<"\nTaking information from text file "<<name1<<endl;

    fileRead.open(name1, ios::in);

    getline(fileRead,line);   // first line removed
    fileRead>>n;
    cout<<"\nThe number of pegs is: "<<n;
    
    rect *id = new rect[n];
    rect *od = new rect[n];

    fileRead>>id[0].l>>id[0].b>>od[0].l>>od[0].c[0]>>od[0].c[1]>>w>>h;

    layers = floor(h/w);
    cout<<"\nNumber of layers is: "<<layers;

    fileRead.close();

    od[0].b = id[0].b + (od[0].l-id[0].l);     // same dimensions added to both l n b each time
    id[0].c[0] = od[0].c[0] + (od[0].l-id[0].l)/2;
    id[0].c[1] = od[0].c[1] + (od[0].b-id[0].b)/2;   // hole will be half of the length differences away

    cout<<"\nSet id, od number 0";

    for(i=1;i<n;i++)
    {
        od[i] = od[i-1];
        id[i] = id[i-1];
        // length l and breadth b copied exactly for all
        od[i].c[0] = od[i-1].c[0] + od[i-1].l + w;
        id[i].c[0] = od[i].c[0] + (od[i].l-id[i].l)/2;    // x dimension of hole changing
        // id[i].c[1] = od[i].c[1] + (od[i].b-id[i].b)/2;   // y dimension remains the same
        cout<<"\nSet id,od number "<<i;
    }

    for(i=0;i<layers;i++)
    {
        z = (i+1)*w;
        cout<<"\n\nLayer "<<i<<endl;
        for(j=0;j<n;j++)
        {
            e = mk_hole(id[j],od[j],w,e);
            cout<<"\nHole "<<j;
        }
    }

    return e;
}


double make_pegs(double e)  // make a 2d array of pegs
{
    int n, m, i, j, k, layers;
    double w, h, xdist, ydist, curve;   // layer height(w), height of the base (h)
    // xdist n ydist are for the horizontal and vertical distanc ein the array
    // curve tells us how much the peg bulges out 

    string name1 = "pegs_info.txt";
    cout<<"\nTaking information from text file "<<name1<<endl;

    fileRead.open(name1, ios::in);

    getline(fileRead,line);   // first line removed
    fileRead>>n>>m;
    cout<<"\nThe number of Rows is: "<<n<<"\nThe number of Columns is: "<<m;
    
    rect** id = new rect*[n];
    rect** od = new rect*[n];
    rect vari, varo;

    fileRead>>vari.l>>vari.b>>varo.l>>varo.c[0]>>varo.c[1]>>xdist>>ydist>>w>>h>>curve;

    double dif;
    dif = varo.l-vari.l;
    varo.b = vari.b + dif; 
    vari.c[0] = varo.c[0] + dif/2;
    vari.c[1] = varo.c[1] + dif/2;   // making vari and varo complete
    
    layers = floor(h/w);
    cout<<"\nNumber of layers is: "<<layers;

    fileRead.close();

    for(i=0;i<n;i++)
    {
        id[i] = new rect[m];
        od[i] = new rect[m];
    }   // completing the 2D array dynamic declaration

    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            id[i][j] = vari;
            od[i][j] = varo;  // initialize all values

            od[i][j].c[0] = varo.c[0] + (j*xdist);  // vertical columns marked by m x-spacings
            od[i][j].c[1] = varo.c[1] + (i*ydist);  // horizontal rows marked by n y-spacings
            
            id[i][j].c[0] = od[i][j].c[0] + dif/2;
            id[i][j].c[1] = od[i][j].c[1] + dif/2;  // id is just added dif/2 to all od
        }
    }

    cout<<"\nInitialization done. Starting print.\n";

    double length[2], breadth[2], temp;     
    // length out and in and breadth out and in     2 centers for the in and out
    int lb2 = layers/2;
    cout<<"\nlb2 = "<<lb2;

    for(k=0;k<layers;k++)
    {
        z = (k+1)*w;
        cout<<"\n\nLayer "<<k<<endl;
        temp = ((lb2-k)*(lb2-k)*curve)/(lb2*lb2);
        length[0] = varo.l - temp;
        breadth[0] = varo.b - temp;   // subtract to make outer walls curve in
        length[1] = vari.l + temp;
        breadth[1] = vari.b + temp;     // add to make inner walls curve out

        for(i=0;i<n;i++)
        {
            for(j=0;j<m;j++)
            {
                od[i][j].l = length[0];
                od[i][j].b = breadth[0];
                id[i][j].l = length[1];
                id[i][j].b = breadth[1];        // adjusting the dims for all

                od[i][j].c[0] += temp/2;   
                od[i][j].c[1] += temp/2;   // add temp to move start point inward
                // inner dimensions self adjust due to the hole function

                e = mk_hole(id[i][j],od[i][j],w,e);

                od[i][j].c[0] -= temp/2;   
                od[i][j].c[1] -= temp/2;   // revert back after print

                cout<<"\nHole ( "<<i<<", "<<j<<" )";
            }
        }
    }

    return e;

}