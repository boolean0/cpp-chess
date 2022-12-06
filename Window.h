#ifndef WINDOW_H
#define WINDOW_H

#if VIEW >= 1
  #include <X11/Xlib.h>
#include <iostream>
#include <string>
#include <map>

class Xwindow {

  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];
  unsigned long customColours[10];
  Pixmap i;

  std::map<char, Pixmap> WoW;
  std::map<char, Pixmap> WoB;
  std::map<char, Pixmap> BoW;
  std::map<char, Pixmap> BoB;

  void initializeSprites();

 public:
  Xwindow(int width=500, int height=500);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.
  Xwindow(const Xwindow&) = delete;
  Xwindow &operator=(const Xwindow&) = delete;

  // Available colours.
  enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown};
  enum {customWhite=0, customBlack};
  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);
  void fillRectangleCustom(int x, int y, int width, int height, int colour=0);
  // Draws a string
  void drawString(int x, int y, std::string msg);
  void drawPiece(char p, bool isWhitePiece, bool isWhiteSquare, int row, int col);
};
#endif
#endif
