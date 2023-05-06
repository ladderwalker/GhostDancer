#define CNFG_IMPLEMENTATION
//#define CNFGOGL
#define HAS_XSHAPE
#define HAS_XINERAMA

#include <X11/Xlib.h>

#include <X11/extensions/Xfixes.h>
#include <stdbool.h>
#include <time.h>
#include "include/rawdraw_sf.h"

#define BLINKTIME   15
#define MOUSE_OFFSET 0
#define SIN(x) sin(x * 3.141592653589 / 180)
#define COS(x) cos(x * 3.141592653589 / 180)

//int __dso_handle;
//states
bool blinking = false;
bool eyesclosed;
typedef enum {
    closed,AEI,O,Ee,RW,QW,BMP,L,FV,ChJSH,TH
} mouthstate;

mouthstate mouth = closed;
int mx, my, oldmx, oldmy;
float scale;
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
    
    RDPoint lips[4]={{x+27 * scale,y+70 * scale},{x+69 * scale,y+70 * scale},{x+60 * scale,y+87 * scale},{x+37 * scale, y+87 * scale}};
    RDPoint hole[4]={{x+32 * scale,y+72 * scale},{x+64 * scale,y+72 * scale},{x+58 * scale,y+84 * scale},{x+37 * scale,y+84 * scale}};
    
    CNFGColor(0x644e4eff);
    CNFGTackPoly(lips, 4);
    
    CNFGColor(0x000000ff);
    CNFGTackPoly(hole,4);
    
    CNFGColor(0xffffffff);
    CNFGTackRectangle(x+38 * scale,y+73 * scale,x+58 * scale,y+75 * scale);//teeth
    
    CNFGColor(0xff0000ff);
    CNFGTackRectangle(x+42 * scale,y+80 * scale,x+54 * scale,y+83 * scale);//tongue
}

void DrawMouthO( int x, int y ) {
    int xo= x + 50 * scale;
    int yo= y + 77 * scale;
    int lipr = 15 * scale;
    int r = 12 * scale;
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
    
    RDPoint lips[4]={{x+27 * scale,y+70 * scale},{x+69 * scale,y+70 * scale},{x+60 * scale,y+87 * scale},{x+37 * scale,y+87 * scale}};
    RDPoint hole[4]={{x+32 * scale,y+72 * scale},{x+64 * scale,y+72 * scale}, {x+58 * scale, y+84 * scale},{x+37 * scale,y+84 * scale}};
    
    CNFGColor(0x644e4eff);
    CNFGTackPoly(lips, 4);
    
    CNFGColor(0x000000ff);
    CNFGTackPoly(hole,4);
    
    CNFGColor(0xffffffff);
    CNFGTackRectangle(x+38 * scale,y+73 * scale,x+58 * scale,y+75 * scale);//teeth
    
    CNFGColor(0xff0000ff);
    CNFGTackRectangle(x+42 * scale,y+77 * scale,x+54 * scale,y+82 * scale);//tongue
    
    CNFGColor(0xffffffff);
    CNFGTackRectangle(x+40 * scale,y+80 * scale,x+56 * scale,y+83 * scale);//bottom teeth
}

void DrawMouthRW( int x, int y ) {
    
    RDPoint lips[6]={{x+23 * scale, y+81 * scale}, {x+40 * scale, y+70 * scale}, {x+60 * scale, y+70 * scale}, {x+77 * scale,y+81 * scale},{x+60 * scale,y+86 * scale},{x+38 * scale,y+86 * scale}};
    RDPoint hole[6]={{x+29 * scale,y+79 * scale}, {x+40 * scale,y+74 * scale}, {x+59 * scale,y+74 * scale},{x+70 * scale,y+79 * scale},{x+59 * scale,y+81 * scale},{x+40 * scale,y+81 * scale}};
    
    CNFGColor(0x644e4eff);
    CNFGTackPoly(lips, 6);
    
    CNFGColor(0x000000ff);
    CNFGTackPoly(hole,6);
    
    CNFGColor(0xffffffff);
    CNFGTackRectangle(x+36 * scale,y+75 * scale,x+63 * scale,y+76 * scale);//teeth
}

void DrawMouthQW( int x, int y ) {
    int xo = x + 50 * scale;
    int yo = y + 77 * scale;
    int lipr = 10 * scale;
    int r = 7 * scale;
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
    CNFGTackRectangle(x+37 * scale,y+75 * scale,x+62 * scale,y+77 * scale);//lips
    //CNFGTackSegment(x+38 * scale,y+78 * scale,x+61 * scale,y+78 * scale);
    CNFGColor(0x000000ff);
    CNFGTackSegment(x+38 * scale,y+76 * scale,x+61 * scale,y+76 * scale);
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
    CNFGTackRectangle(xcen,ycen,xcen + 23 * scale, ycen + 12 * scale);
    CNFGColor(0x000000ff);
    CNFGTackRectangle(xcen + 8 * scale, ycen + 3 * scale, xcen + 15 * scale, ycen + 8 * scale );
}

void DrawPupils( int x, int y ) {
    DrawPupil(x + 17 * scale, y + 34 * scale);
    DrawPupil(x + 59 * scale, y + 34 * scale);
}
void DrawShoulder(int x,int y){
    float xo = (float)x;
    float yo = (float)y;
    
    float r= 45.0f * scale;
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
    
    float r= 29.0f * scale;
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
    float forearm[][2]={{x-28 * scale,y},{x+28 * scale,y},{x+20 * scale,y+80 * scale},{x-20 * scale,y+80 * scale}};
    
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
    DrawHand(rdforearm[3].x+20 * scale, rdforearm[3].y);
}

void DrawElbow(int x,int y){
    float xo = (float)x;
    float yo = (float)y;
    
    float r= 29.0f * scale;
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
    float upperRarm[][2]={{x+15 * scale,y-42 * scale},{x+80 * scale,y-25 * scale},{x+80 * scale,y+25 * scale},{x+4 * scale,y+42 * scale}};
    if(my > oldmy){
        rotate(upperRarm, 4, x, y, 32);
    } else if(my < oldmy) {
        rotate(upperRarm, 4, x, y, 78);
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
    
    DrawElbow(rbicep[1].x-16 * scale, rbicep[1].y+17 * scale);
}

void DrawLUpperarm(int x,int y){
    DrawShoulder(x,y);
    float upperLarm[][2]={{x-15 * scale,y-42 * scale},{x-80 * scale,y-25 * scale},{x-80 * scale,y+25 * scale},{x-4 * scale,y+42 * scale}};
    if(my > oldmy){
        rotate(upperLarm, 4, x, y, -32);
    } else if(my < oldmy) {
        rotate(upperLarm, 4, x, y, -78);
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
    
    DrawElbow(lbicep[1].x+16 * scale, lbicep[1].y+17 * scale);
}

void DrawChin(int x, int y){
    float chin[][2] =  {{x,y},{x+65 * scale,y},{x+68 * scale,y+100 * scale},{x+2 * scale,y+100 * scale}};
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
    
    float r = 34.0f * scale;
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
    DrawChin(x-30 * scale, y);
}

void DrawLThigh(int x, int y){
    float thigh[][2] =  {{x,y},{x+70 * scale,y},{x+68 * scale,y+100 * scale},{x+2 * scale,y+100 * scale}};
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
    
    DrawKnee(rdThigh[3].x+35 * scale,rdThigh[3].y);
    
}

void DrawRThigh(int x, int y){
    float thigh[][2] =  {{x,y},{x+70 * scale,y},{x+68 * scale,y+100 * scale},{x+2 * scale,y+100 * scale}};
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
    DrawKnee(rdThigh[3].x+35 * scale,rdThigh[3].y);
}


void DrawPackage(int x, int y){
    float xo = (float)x;
    float yo = (float)y;
    
    float r= 29.0f * scale;
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
    RDPoint rdgroin[4] = {{x,y},{x+150 * scale,y},{x+150 * scale,y+55 * scale},{x,y+55 * scale}};
    CNFGColor(0x14227aff);
    CNFGTackPoly(rdgroin, 4);
    DrawPackage(x+75 * scale,y+65 * scale);
}

void DrawTorso(int x, int y) {
    //DrawGroin(x,y);
    
    //DrawLUpperarm(x,y);
    int cx = x + 50 * scale;
    int cy = y + 90 * scale;
    CNFGColor(0x2c0f0eff);//dark maroon
    
    float ftorso[][2] = {{cx,cy},{cx+100 * scale,cy+10 * scale},{cx+75 * scale,cy+200 * scale},{cx-75 * scale,cy+200 * scale},{cx-100 * scale,cy+10 * scale}};
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
    DrawRUpperarm(ftorso[1][0]-5 * scale, ftorso[1][1]+38 * scale);
    DrawLUpperarm(ftorso[4][0]+5 * scale, ftorso[4][1]+38 * scale);
    DrawLLeg(ftorso[3][0], ftorso[3][1]+45 * scale);
    DrawRLeg(ftorso[2][0]-70 * scale, ftorso[2][1]+45 * scale);
    DrawGroin(ftorso[3][0], ftorso[3][1]);
    
}


void DrawFigure( int x, int y, size_t tick ) {
    DrawTorso(x,y);
    srand(tick);
    float headsize = 100 * scale; 
    for(int r = 0; r<115 * scale; r++) {
        int numx = (rand() % (int)headsize);
        int numy = (rand() % (int)headsize);
        CNFGColor(0xffffffff);
        CNFGTackPixel(x + numx, y + numy);
        
    }
    srand(tick+2);
    for(int r = 0; r<150 * scale; r++) {
        
        int numx = (rand() % (int)headsize);
        int numy = (rand() % (int)headsize);
        CNFGColor(0xff0000ff);
        CNFGTackPixel(x + numx, y + numy);
    }
    
    CNFGColor(0x00000000);
    RDPoint uplef[3] = {{x,y},{x+25* scale,y},{x,y+30* scale}}; 
    RDPoint uprig[3] = {{x+75* scale,y},{x+100* scale,y},{x+100* scale,y+30* scale}}; 
    RDPoint botlef[3] = {{x,y + 75* scale},{x,y + 100* scale},{x + 25* scale,y+100* scale}}; 
    RDPoint botrig[3] = {{x + 75,y + 100},{x+100,y + 75},{x + 100,y+100}};
    CNFGTackPoly( uplef, 3 );
    CNFGTackPoly( uprig, 3 );
    CNFGTackPoly( botlef, 3 );
    CNFGTackPoly( botrig, 3 );
    CNFGTackRectangle(x + 15* scale,y+30* scale,x+43* scale,y+45 * scale );
    CNFGTackRectangle(x + 57 * scale,y+30 * scale,x+85 * scale,y+45 * scale );
    if(!eyesclosed)  DrawPupils( x, y );
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
    if ( button == 1) {
        eyesclosed = true;
        printf("%d\n",eyesclosed);
    }
    if ( button == 3) {
        eyesclosed = false;
    }
    if ( button == 4) {
        scale *= 1.1f;
    }
    if ( button == 5) {
        scale *= 0.9f;
    }
    
}
void HandleMotion( int x, int y, int mask ) {
    mx = x + MOUSE_OFFSET;
    my = y + MOUSE_OFFSET;
    
} 
void HandleDestroy() { }

int main(void)
{ 
    
    
    scale = 1.0f;
    eyesclosed = false;
    
    size_t tick,tick2;
    tick =  0;
    tick2 = 0;
    CNFGSetup( "GhostDancer", 1024, 768 );
    //CNFGSetupFullscreen( "GhostDancer", 0 );
    int blinkcount = 0;
    char **buf;
    int buflen;
    float fOffset;
    XFixesHideCursor(CNFGDisplay, CNFGWindow);
    while(CNFGHandleInput())
    {
        fOffset = 50 * scale;
        int offset = (int)fOffset;
        tick++;
        tick2++;
        if(tick2 > 500) {
            
            blinking = true;
            tick2 = 0;
        }
        
        CNFGBGColor = 0xff; //Black Background
        short w, h;
        CNFGClearFrame();
        CNFGGetDimensions( &w, &h );
        
        if(blinking) {
            eyesclosed = true;
            blinkcount++;
        }
        if (blinkcount > BLINKTIME) {
            blinking = false;
            eyesclosed = false;
            blinkcount = 0;
        }
        
        DrawFigure(mx - offset,my - offset,tick);
        oldmx = mx;
        oldmy = my;
        
        //Display the image and wait for time to display next frame.
        CNFGSwapBuffers();
        
        //usleep(100000);
    }
    
    
}

