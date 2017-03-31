//import Serial comunication library:
import processing.serial.*;
import java.awt.event.KeyEvent;
import java.io.IOException;

private PLabBridge pBridge;

private String received = null;

void bindPLabBridge (PLabBridge bridge) {

  pBridge = bridge;
  
  bridge.subscribeMessages (new PLabRecv() {
    public void receive (String string) {
    }
  });
  size(bridge.getWidth(), bridge.getHeight());
}

void btWrite(String string) {
  if (pBridge != null) {
    pBridge.send(string);
  }
}

//
//  Minimal Processing GUI library.
//  PLab 2015
//
//  Dag Svanæs, IDI, NTNU.
// 

int[] white = {242, 246, 247}; // clouds white
int[] black = {0,0,0};
int[] red = {231, 76, 60};
int[] green = {46, 204, 113};
int[] blue = {0,0,255};
int[] yellow = {255,255,0};
int[] gray = {128,128,128};

boolean inside(int x,int y, int x0,int y0,int w,int h) {
  return (((x >= x0) && (x < (x0+w))) && 
      ((y >= y0) && (y < (y0+h))));
}

boolean mouseInside(int[] rect) {
  return inside(mouseX, mouseY, rect[0],rect[1],rect[2],rect[3]);
}

void drawButton(int[] xywh, String buttonText) {
    boolean mousePressedInButton = mouseInside(xywh) && mousePressed;
    stroke(0);
    if (mousePressedInButton) {
      fill(0); }
    else {
      fill(242, 246, 247); 
    } 
    rect(xywh[0],xywh[1],xywh[2],xywh[3],10);
    if (mousePressedInButton) {
      fill(242, 246, 247); }
    else {
      fill(0); 
    }   
    int tSize = xywh[3] * 3 / 5;
    textSize(tSize);
    textAlign(CENTER, CENTER);
    text(buttonText,xywh[0]+xywh[2]/2,xywh[1]+xywh[3]/2-2);
}

void drawText(int[] xywh, String buttonText) {
    stroke(0);
    fill(255);  
    rect(xywh[0],xywh[1],xywh[2],xywh[3]);
    fill(0);  
    int tSize = xywh[3] * 3 / 5;
    textSize(tSize);
    textAlign(LEFT, CENTER);
    text(buttonText,xywh[0]+2,xywh[1]+xywh[3]/2-2);
}
  
void drawRectangle(int[] xywh, int[] drawColor) {
    stroke(0);
    fill(drawColor[0],drawColor[1],drawColor[2]);  
    rect(xywh[0],xywh[1],xywh[2],xywh[3]);
}

void drawCircle(int[] xyr, int[] drawColor) {
    stroke(0);
    fill(drawColor[0],drawColor[1],drawColor[2]);  
    ellipseMode(RADIUS);
    ellipse(xyr[0],xyr[1],xyr[2],xyr[2]);
}


//---------------------------------

int[] tactical = {80,10,200,25};
String buttonString1 = "Tactical mode";

int[] Chill = {80,40,200,25};
String buttonString2 = "Chill mode";

int[] suicide = {80,100,200,25};
String buttonString3 = "Suicide mode"; 


// War mode:
int[] color1 = red;
int[] color2 = null;

int[] circleXYR1 = {100, 185, 7};
int[] circleColor1 = red;

int[] circleXYR2 = {130, 185, 7};
int[] circleColor2 = white;

int[] war = {80,200,200,50};
String buttonString4 = "War mode"; 

boolean bluetoothActive = false;

void setup() {
  
  // GUI
  size(375,620);
  background(236, 240, 241);   // Background color is gray (128,128,128).
  stroke(0);                    // Stroke color is black (0,0,0)
}

void btRead(String string) {
  println("Received: " + string);
}

void draw() {    // Called for every fram
    drawButton(tactical, buttonString1);
    drawButton(Chill, buttonString2);
    drawButton(suicide, buttonString3);
    drawButton(war, buttonString4);
    
    drawCircle(circleXYR1, circleColor1);
    drawCircle(circleXYR2, circleColor2);
 }

void mousePressed() {
  if (mouseInside(war)) {
    if (circleColor1 == white && circleColor2 == green) {
      circleColor1 = red;
      circleColor2 = white;
    }
    else {
      circleColor1 = white;
      circleColor2 = green;
      btWrite("w");
    }
  }
  else if (mouseInside(suicide)) {
    btWrite("s");
  }
  else if (mouseInside(Chill)) {
    btWrite("c");
  }
  else if (mouseInside(tactical)) {
    btWrite("t");
  }  
}

void mouseReleased() {
}