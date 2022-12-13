#define CNFG_IMPLEMENTATION
#define CNFGOGL
#define HAS_XSHAPE
#define HAS_XINERAMA

#include <stdbool.h>
#include <time.h>
#include "include/rawdraw_sf.h"

#define BLINKTIME   15
#define MOUSE_OFFSET 0
#define SIN(x) sin(x * 3.141592653589 / 180)
#define COS(x) cos(x * 3.141592653589 / 180)

int __dso_handle;
//states
bool blinking = false;
typedef enum {
    closed,AEI,O,Ee,RW,QW,BMP,L,FV,ChJSH,TH
} mouthstate;

mouthstate mouth = closed;
int mx, my, oldmx, oldmy;

void rotate(float a[][2], int n, int x_pivot, int y_pivot,
            int angle)
{
    int i = 0;
    while (i < n) {
        // Shifting the pivot point to the origin
        // and the given points accordingly
        int x_shifted = a[i][0] - x_pivot;
        int y_shifted = a[i][1] - y_pivot;
        
        // Calculating the rotated point co-ordinates
        // and shifting it back
        a[i][0] = x_pivot
            + (x_shifted * COS(angle)
               - y_shifted * SIN(angle));
        a[i][1] = y_pivot
            + (x_shifted * SIN(angle)
               + y_shifted * COS(angle));
        //printf("(%f, %f) ", a[i][0], a[i][1]);
        i++;
    }
}



void DrawMouthA( int x, int y ) {
    
    RDPoint lips[4]={{x+27,y+70},{x+69,y+70},{x+60,y+87},{x+37,y+87}};
    RDPoint hole[4]={{x+32,y+72},{x+64,y+72},{x+58,y+84},{x+37,y+84}};
    
    CNFGColor(0x644e4eff);
    CNFGTackPoly(lips, 4);
    
    CNFGColor(0x000000ff);
    CNFGTackPoly(hole,4);
    
    CNFGColor(0xffffffff);
    CNFGTackRectangle(x+38,y+73,x+58,y+75);//teeth
    
    CNFGColor(0xff0000ff);
    CNFGTackRectangle(x+42,y+80,x+54,y+83);//tongue
}

void DrawMouthO( int x, int y ) {
    int xo= x + 50;
    int yo= y + 77;
    int lipr = 15;
    int r = 12;
    int nPoints = 20;
    
    RDPoint lips[nPoints];
    RDPoint hole[nPoints];
    
    for(int i = 0;  i < nPoints; i++){
        lips[i].x = xo + ( lipr * cosf(i / (float)(nPoints - 1) * 2.0f * 3.14159f));
        lips[i].y = yo + ( lipr * sinf(i / (float)(nPoints - 1) * 2.0f * 3.14159f));
        
        hole[i].x = xo + ( r * cosf(i / (float)(nPoints - 1) * 2.0f * 3.14159f));
        hole[i].y = yo + ( r * sinf(i / (float)(nPoints - 1) * 2.0f * 3.14159f));
    }
    
    CNFGColor(0x644e4eff);
    CNFGTackPoly(lips, nPoints);
    
    CNFGColor(0x000000ff);
    CNFGTackPoly(hole,nPoints);
}

void DrawMouthE( int x, int y ) {
    
    RDPoint lips[4]={{x+27,y+70},{x+69,y+70},{x+60,y+87},{x+37,y+87}};
    RDPoint hole[4]={{x+32,y+72},{x+64,y+72},{x+58,y+84},{x+37,y+84}};
    
    CNFGColor(0x644e4eff);
    CNFGTackPoly(lips, 4);
    
    CNFGColor(0x000000ff);
    CNFGTackPoly(hole,4);
    
    CNFGColor(0xffffffff);
    CNFGTackRectangle(x+38,y+73,x+58,y+75);//teeth
    
    CNFGColor(0xff0000ff);
    CNFGTackRectangle(x+42,y+77,x+54,y+82);//tongue
    
    CNFGColor(0xffffffff);
    CNFGTackRectangle(x+40,y+80,x+56,y+83);//bottom teeth
}

void DrawMouthRW( int x, int y ) {
    
    RDPoint lips[6]={{x+23,y+81},{x+40,y+70},{x+60,y+70},{x+77,y+81},{x+60,y+86},{x+38,y+86}};
    RDPoint hole[6]={{x+29,y+79},{x+40,y+74},{x+59,y+74},{x+70,y+79},{x+59,y+81},{x+40,y+81}};
    
    CNFGColor(0x644e4eff);
    CNFGTackPoly(lips, 6);
    
    CNFGColor(0x000000ff);
    CNFGTackPoly(hole,6);
    
    CNFGColor(0xffffffff);
    CNFGTackRectangle(x+36,y+75,x+63,y+76);//teeth
}

void DrawMouthQW( int x, int y ) {
    int xo = x + 50;
    int yo = y + 77;
    int lipr = 10;
    int r = 7;
    int nPoints = 20;
    
    RDPoint lips[nPoints];
    RDPoint hole[nPoints];
    
    for(int i = 0;  i < nPoints; i++){
        lips[i].x = xo + ( lipr * cosf(i / (float)(nPoints - 1) * 2.0f * 3.14159f));
        lips[i].y = yo + ( lipr * sinf(i / (float)(nPoints - 1) * 2.0f * 3.14159f));
        
        hole[i].x = xo + ( r * cosf(i / (float)(nPoints - 1) * 2.0f * 3.14159f));
        hole[i].y = yo + ( r * sinf(i / (float)(nPoints - 1) * 2.0f * 3.14159f));
    }
    
    CNFGColor(0x644e4eff);
    CNFGTackPoly(lips, nPoints);
    
    CNFGColor(0x000000ff);
    CNFGTackPoly(hole,nPoints);
}

void DrawMouthClosed( int x, int y ) {
    CNFGColor(0x644e4eff);
    CNFGTackRectangle(x+37,y+75,x+62,y+77);//lips
    CNFGTackSegment(x+38,y+78,x+61,y+78);
    CNFGColor(0x000000ff);
    CNFGTackSegment(x+38,y+76,x+61,y+76);
}


void DrawMouth(int x, int y){
    switch(mouth){
        case closed: 
        {
            DrawMouthClosed(x,y);
            break;
        }
        case AEI:
        {
            DrawMouthA(x,y);
            break;
        }
        case O:
        {
            DrawMouthO(x,y);
            break;
        }
        case Ee:
        {
            DrawMouthE(x,y);
            break;
        }
        case RW:
        {
            DrawMouthRW(x,y);
            break;
        }
        case QW:
        {
            DrawMouthQW(x,y);
            break;
        }
    }
}

void DrawPupil(int xcen, int ycen) {
    CNFGColor(0xffffffff);
    CNFGTackRectangle(xcen,ycen,xcen + 23, ycen + 12);
    CNFGColor(0x000000ff);
    CNFGTackRectangle(xcen + 8, ycen + 3, xcen + 15, ycen + 8  );
}

void DrawPupils( int x, int y ) {
    DrawPupil(x + 17, y + 34);
    DrawPupil(x + 59, y + 34);
}
void DrawShoulder(int x,int y){
    float xo = (float)x;
    float yo = (float)y;
    
    float r= 45.0f;
    int nPoints = 20;
    float shoulder[nPoints][2];
    RDPoint rdShoulder[nPoints];
    
    
    for(int i = 0;  i < nPoints; i++){
        shoulder[i][0] = xo + ( r * cosf(i / (float)(nPoints - 1) * 2.0f * 3.14159f));
        shoulder[i][1] = yo + ( r * sinf(i / (float)(nPoints - 1) * 2.0f * 3.14159f));
    }
    for(int index = 0; index < nPoints; index++){
        rdShoulder[index].x = (short)shoulder[index][0];
        rdShoulder[index].y = (short)shoulder[index][1];
    }
    CNFGColor(0x2a0f0eff);
    CNFGTackPoly(rdShoulder, nPoints);
    
}

void DrawHand(int x, int y){
    float xo = (float)x;
    float yo = (float)y;
    
    float r= 29.0f;
    int nPoints = 20;
    float hand[nPoints][2];
    RDPoint rdHand[nPoints];
    
    
    for(int i = 0;  i < nPoints; i++){
        hand[i][0] = xo + ( r * cosf(i / (float)(nPoints - 1) * 2.0f * 3.14159f));
        hand[i][1] = yo + ( r * sinf(i / (float)(nPoints - 1) * 2.0f * 3.14159f));
    }
    for(int index = 0; index < nPoints; index++){
        rdHand[index].x = (short)hand[index][0];
        rdHand[index].y = (short)hand[index][1];
    }
    CNFGColor(0xe5b577ff);
    CNFGTackPoly(rdHand, nPoints);
    CNFGColor(0xffffffff);
    
}

void DrawForearm(int x, int y) {
    float forearm[][2]={{x-28,y},{x+28,y},{x+20,y+80},{x-20,y+80}};
    
    if(my > oldmy){
        rotate(forearm, 4, x, y, 12);
    } else if(my < oldmy) {
        rotate(forearm, 4, x, y, -12);
    } else if(mx > oldmx) {
        rotate(forearm, 4, x, y, -15);
    } else if(mx < oldmx) {
        rotate(forearm, 4, x, y, 15);
    } 
    
    RDPoint rdforearm[4];
    for(int i = 0; i<4;i++){
        rdforearm[i].x = forearm[i][0];
        rdforearm[i].y = forearm[i][1];
    }
    CNFGColor(0xe5b577ff);
    CNFGTackPoly(rdforearm,4);
    DrawHand(rdforearm[3].x+20, rdforearm[3].y);
}

void DrawElbow(int x,int y){
    float xo = (float)x;
    float yo = (float)y;
    
    float r= 29.0f;
    int nPoints = 20;
    float elbow[nPoints][2];
    RDPoint rdElbow[nPoints];
    
    
    for(int i = 0;  i < nPoints; i++){
        elbow[i][0] = xo + ( r * cosf(i / (float)(nPoints - 1) * 2.0f * 3.14159f));
        elbow[i][1] = yo + ( r * sinf(i / (float)(nPoints - 1) * 2.0f * 3.14159f));
    }
    for(int index = 0; index < nPoints; index++){
        rdElbow[index].x = (short)elbow[index][0];
        rdElbow[index].y = (short)elbow[index][1];
    }
    CNFGColor(0xe5b577ff);
    CNFGTackPoly(rdElbow, nPoints);
    DrawForearm(x, y);
}

void DrawRUpperarm(int x,int y){
    DrawShoulder(x,y);
    float upperRarm[][2]={{x+15,y-42},{x+80,y-25},{x+80,y+25},{x+4,y+42}};
    if(my > oldmy){
        rotate(upperRarm, 4, x, y, 32);
    } else if(my < oldmy) {
        rotate(upperRarm, 4, x, y, 58);
    } else {
        rotate(upperRarm, 4, x, y, 45);
    }
    
    RDPoint rbicep[4];
    for(int i = 0; i<4;i++){
        rbicep[i].x = upperRarm[i][0];
        rbicep[i].y = upperRarm[i][1];
    }
    CNFGColor(0xe5b577ff);
    CNFGTackPoly(rbicep,4);
    
    DrawElbow(rbicep[1].x-16, rbicep[1].y+17);
}

void DrawLUpperarm(int x,int y){
    DrawShoulder(x,y);
    float upperLarm[][2]={{x-15,y-42},{x-80,y-25},{x-80,y+25},{x-4,y+42}};
    if(my > oldmy){
        rotate(upperLarm, 4, x, y, -32);
    } else if(my < oldmy) {
        rotate(upperLarm, 4, x, y, -58);
    } else {
        rotate(upperLarm, 4, x, y, -45);
    }
    
    RDPoint lbicep[4];
    for(int i = 0; i<4;i++){
        lbicep[i].x = upperLarm[i][0];
        lbicep[i].y = upperLarm[i][1];
    }
    CNFGColor(0xe5b577ff);
    CNFGTackPoly(lbicep,4);
    
    DrawElbow(lbicep[1].x+16, lbicep[1].y+17);
}

void DrawChin(int x, int y){
    float chin[][2] =  {{x,y},{x+65,y},{x+68,y+100},{x+2,y+100}};
    if(my > oldmy){
        rotate(chin, 4, x, y,- 12);
    } else if(my < oldmy) {
        rotate(chin, 4, x, y, 12);
    } else if(mx > oldmx) {
        rotate(chin, 4, x, y, 15);
    } else if(mx < oldmx) {
        rotate(chin, 4, x, y, -15);
    } 
    
    RDPoint rdChin[4];
    for(int i = 0; i<4;i++){
        rdChin[i].x = chin[i][0];
        rdChin[i].y = chin[i][1];
    }
    //RDPoint thigh[4] = {{x,y},{x+70,y},{x+60,y+80},{x+10,y+80}};
    CNFGColor(0x0b1766ff);
    CNFGTackPoly(rdChin, 4);
    
    //DrawKnee(rdThigh[3].x+35,rdThigh[3].y);
    
}

void DrawKnee(int x, int y){
    float xo = (float)x;
    float yo = (float)y;
    
    float r= 34.0f;
    int nPoints = 20;;
    float knee[nPoints][2];
    RDPoint rdKnee[nPoints];
    
    
    for(int i = 0;  i < nPoints; i++){
        knee[i][0] = xo + ( r * cosf(i / (float)(nPoints - 1) * 2.0f * 3.14159f));
        knee[i][1] = yo + ( r * sinf(i / (float)(nPoints - 1) * 2.0f * 3.14159f));
    }
    for(int index = 0; index < nPoints; index++){
        rdKnee[index].x = (short)knee[index][0];
        rdKnee[index].y = (short)knee[index][1];
    }
    CNFGColor(0x0b1766ff);
    CNFGTackPoly(rdKnee, nPoints);
    DrawChin(x-30, y);
}

void DrawLThigh(int x, int y){
    float thigh[][2] =  {{x,y},{x+70,y},{x+68,y+100},{x+2,y+100}};
    if(my > oldmy){
        rotate(thigh, 4, x, y, 12);
    } else if(my < oldmy) {
        rotate(thigh, 4, x, y, -12);
    } else if(mx > oldmx) {
        rotate(thigh, 4, x, y, -15);
    } else if(mx < oldmx) {
        rotate(thigh, 4, x, y, 15);
    } 
    
    RDPoint rdThigh[4];
    for(int i = 0; i<4;i++){
        rdThigh[i].x = thigh[i][0];
        rdThigh[i].y = thigh[i][1];
    }
    //RDPoint thigh[4] = {{x,y},{x+70,y},{x+60,y+80},{x+10,y+80}};
    CNFGColor(0x0b1766ff);
    CNFGTackPoly(rdThigh, 4);
    
    DrawKnee(rdThigh[3].x+35,rdThigh[3].y);
    
}

void DrawRThigh(int x, int y){
    float thigh[][2] =  {{x,y},{x+70,y},{x+68,y+100},{x+2,y+100}};
    if(my > oldmy){
        rotate(thigh, 4, x, y, -12);
    } else if(my < oldmy) {
        rotate(thigh, 4, x, y, 12);
    } else if(mx > oldmx) {
        rotate(thigh, 4, x, y, -15);
    } else if(mx < oldmx) {
        rotate(thigh, 4, x, y, 15);
    } 
    
    RDPoint rdThigh[4];
    for(int i = 0; i<4;i++){
        rdThigh[i].x = thigh[i][0];
        rdThigh[i].y = thigh[i][1];
    }
    //RDPoint thigh[4] = {{x,y},{x+70,y},{x+60,y+80},{x+10,y+80}};
    CNFGColor(0x0b1766ff);
    CNFGTackPoly(rdThigh, 4);
    DrawKnee(rdThigh[3].x+35,rdThigh[3].y);
}


void DrawPackage(int x, int y){
    float xo = (float)x;
    float yo = (float)y;
    
    float r= 29.0f;
    int nPoints = 20;
    float package[nPoints][2];
    RDPoint rdpackage[nPoints];
    
    
    for(int i = 0;  i < nPoints; i++){
        package[i][0] = xo + ( r * cosf(i / (float)(nPoints - 1) * 2.0f * 3.14159f));
        package[i][1] = yo + ( r * sinf(i / (float)(nPoints - 1) * 2.0f * 3.14159f));
    }
    for(int index = 0; index < nPoints; index++){
        rdpackage[index].x = (short)package[index][0];
        rdpackage[index].y = (short)package[index][1];
    }
    CNFGColor(0x14227aff);
    CNFGTackPoly(rdpackage, nPoints);
}

void DrawLLeg(int x,int y){
    DrawLThigh(x,y);
    //DrawKnee(x,y);
    //Drawshin();
    //DrawFoot(); 
}

void DrawRLeg(int x,int y){
    DrawRThigh(x,y);
}

void DrawGroin(int x, int y){
    RDPoint rdgroin[4] = {{x,y},{x+150,y},{x+150,y+55},{x,y+55}};
    CNFGColor(0x14227aff);
    CNFGTackPoly(rdgroin, 4);
    DrawPackage(x+75,y+65);
}

void DrawTorso(int x, int y) {
    //DrawGroin(x,y);
    
    //DrawLUpperarm(x,y);
    int cx = x + 50;
    int cy = y + 90;
    CNFGColor(0x2c0f0eff);//dark maroon
    
    float ftorso[][2] = {{cx,cy},{cx+100,cy+10},{cx+75,cy+200},{cx-75,cy+200},{cx-100,cy+10}};
    if(mx > oldmx+5){
        rotate(ftorso, 5, cx, cy,  3);
    } else if(mx < oldmx-5) {
        rotate(ftorso, 5, cx, cy, -3);
    }
    RDPoint torso[5] = {
        {(short)ftorso[0][0],(short)ftorso[0][1]},
        {(short)ftorso[1][0],(short)ftorso[1][1]},
        {(short)ftorso[2][0],(short)ftorso[2][1]},
        {(short)ftorso[3][0],(short)ftorso[3][1]},
        {(short)ftorso[4][0],(short)ftorso[4][1]}
    };
    CNFGTackPoly(torso,5);
    DrawRUpperarm(ftorso[1][0]-5, ftorso[1][1]+38);
    DrawLUpperarm(ftorso[4][0]+5, ftorso[4][1]+38);
    DrawLLeg(ftorso[3][0], ftorso[3][1]+45);
    DrawRLeg(ftorso[2][0]-70, ftorso[2][1]+45);
    DrawGroin(ftorso[3][0], ftorso[3][1]);
    
}


void DrawFigure( int x, int y, size_t tick ) {
    DrawTorso(x,y);
    srand(tick);
    for(int r = 0; r<115; r++) {
        int numx = (rand() % 100);
        int numy = (rand() % 100);
        CNFGColor(0xffffffff);
        CNFGTackPixel(x + numx, y + numy);
        
    }
    srand(tick+2);
    for(int r = 0; r<150; r++) {
        int numx = (rand() % 100);
        int numy = (rand() % 100);
        CNFGColor(0xff0000ff);
        CNFGTackPixel(x + numx, y + numy);
    }
    
    CNFGColor(0x00000000);
    RDPoint uplef[3] = {{x,y},{x+25,y},{x,y+30}}; 
    RDPoint uprig[3] = {{x+75,y},{x+100,y},{x+100,y+30}}; 
    RDPoint botlef[3] = {{x,y + 75},{x,y + 100},{x + 25,y+100}}; 
    RDPoint botrig[3] = {{x + 75,y + 100},{x+100,y + 75},{x + 100,y+100}};
    CNFGTackPoly( uplef, 3 );
    CNFGTackPoly( uprig, 3 );
    CNFGTackPoly( botlef, 3 );
    CNFGTackPoly( botrig, 3 );
    CNFGTackRectangle(x + 15,y+30,x+43,y+45 );
    CNFGTackRectangle(x + 57,y+30,x+85,y+45 );
    if(!blinking)  DrawPupils( x, y );
    DrawMouth(x,y);     
    //CNFGColor(0xffffffff);
    //CNFGTackPixel(x +  numx, y + numy);
}
void HandleKey( int keycode, int bDown ) {
    if( keycode == 65307 ) exit( 0 );
    if( keycode == 97 ) mouth = AEI;
    if( keycode == 111 ) mouth = O;
    if( keycode == 101 ) mouth = Ee;
    if( keycode == 114 ) mouth = RW;
    if( keycode == 113 ) mouth = QW;
    if( keycode == 99 ) mouth = closed;
    printf( "Key: %d -> %d\n", keycode, bDown );
}
void HandleButton( int x, int y, int button, int bDown ) {
    if ( button == 1) blinking = true;
}
void HandleMotion( int x, int y, int mask ) {
    mx = x + MOUSE_OFFSET;
    my = y + MOUSE_OFFSET;
    
} 
void HandleDestroy() { }

int main(void)
{ 
    //HideMouseCursor();
    size_t tick; 
    CNFGSetup( "GhostDancer", 1024, 768 );
    int blinkcount = 0;
    char **buf;
    int buflen;
    while(CNFGHandleInput())
    {
        tick++;
        CNFGBGColor = 0xff; //Black Background
        short w, h;
        CNFGClearFrame();
        CNFGGetDimensions( &w, &h );
        
        if(blinking) blinkcount++;
        if (blinkcount > BLINKTIME) {
            blinking = false;
            blinkcount = 0;
        }
        
        DrawFigure(mx,my,tick);
        oldmx = mx;
        oldmy = my;
        
        //Display the image and wait for time to display next frame.
        CNFGSwapBuffers();
        
        //usleep(100000);
    }
    
    
}

