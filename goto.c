//
//  gotopaint : an ncurses drawing tool with a pathological c coding standard.
//  homepage  : https://github.com/tangentstorm/gotopaint
//  license   : MIT/x11 style. see LICENSE.MIT for datails.
//
#include <ncurses.h>
int main() {
  MEVENT event; int ch;
INIT:
  initscr(); noecho(); cbreak(); keypad(stdscr, TRUE); start_color();
  mousemask( BUTTON1_PRESSED | REPORT_MOUSE_POSITION, NULL );
  init_pair( 8, COLOR_BLACK,   COLOR_BLACK );
  init_pair( 1, COLOR_RED,     COLOR_BLACK );
  init_pair( 2, COLOR_GREEN,   COLOR_BLACK );
  init_pair( 3, COLOR_YELLOW,  COLOR_BLACK );
  init_pair( 4, COLOR_BLUE,    COLOR_BLACK );
  init_pair( 5, COLOR_MAGENTA, COLOR_BLACK );
  init_pair( 6, COLOR_CYAN,    COLOR_BLACK );
  init_pair( 7, COLOR_WHITE,   COLOR_BLACK );
  attron( COLOR_PAIR( 7 )); // light gray by default
TOP:
  ch = getch();
  if (ch == 27)        goto END; // escape key
  if (ch == KEY_MOUSE) goto MOUSE;
  0?: ch == 'k' ? attron( COLOR_PAIR( 8 ))
    : ch == 'r' ? attron( COLOR_PAIR( 1 ))
    : ch == 'g' ? attron( COLOR_PAIR( 2 ))
    : ch == 'y' ? attron( COLOR_PAIR( 3 ))
    : ch == 'b' ? attron( COLOR_PAIR( 4 ))
    : ch == 'm' ? attron( COLOR_PAIR( 5 ))
    : ch == 'c' ? attron( COLOR_PAIR( 6 ))
    : ch == 'w' ? attron( COLOR_PAIR( 7 ))
    : ch == 'K' ? attron( COLOR_PAIR( 8 )), attron( A_BOLD )
    : ch == 'R' ? attron( COLOR_PAIR( 1 )), attron( A_BOLD )
    : ch == 'G' ? attron( COLOR_PAIR( 2 )), attron( A_BOLD )
    : ch == 'Y' ? attron( COLOR_PAIR( 3 )), attron( A_BOLD )
    : ch == 'B' ? attron( COLOR_PAIR( 4 )), attron( A_BOLD )
    : ch == 'M' ? attron( COLOR_PAIR( 5 )), attron( A_BOLD )
    : ch == 'C' ? attron( COLOR_PAIR( 6 )), attron( A_BOLD )
    : ch == 'W' ? attron( COLOR_PAIR( 7 )), attron( A_BOLD )
    : 0; goto TOP;
MOUSE:
  if (getmouse(&event) != OK)         goto TOP;
  attron( A_REVERSE );
  mvprintw(0, 0, "(%2i,%2i)", event.x, event.y);
  if (event.bstate &        REPORT_MOUSE_POSITION    )mvprintw(0, 10, "report mouse movement                      ");
  if (event.bstate &        BUTTON1_PRESSED          )mvprintw(0, 10, "mouse button 1 down                        ");
  if (event.bstate &        BUTTON1_RELEASED         )mvprintw(0, 10, "mouse button 1 up                          ");
  if (event.bstate &        BUTTON1_CLICKED          )mvprintw(0, 10, "mouse button 1 clicked                     ");
  if (event.bstate &        BUTTON1_DOUBLE_CLICKED   )mvprintw(0, 10, "mouse button 1 double clicked              ");
  if (event.bstate &        BUTTON1_TRIPLE_CLICKED   )mvprintw(0, 10, "mouse button 1 triple clicked              ");
  if (event.bstate &        BUTTON2_PRESSED          )mvprintw(0, 10, "mouse button 2 down                        ");
  if (event.bstate &        BUTTON2_RELEASED         )mvprintw(0, 10, "mouse button 2 up                          ");
  if (event.bstate &        BUTTON2_CLICKED          )mvprintw(0, 10, "mouse button 2 clicked                     ");
  if (event.bstate &        BUTTON2_DOUBLE_CLICKED   )mvprintw(0, 10, "mouse button 2 double clicked              ");
  if (event.bstate &        BUTTON2_TRIPLE_CLICKED   )mvprintw(0, 10, "mouse button 2 triple clicked              ");
  if (event.bstate &        BUTTON3_PRESSED          )mvprintw(0, 10, "mouse button 3 down                        ");
  if (event.bstate &        BUTTON3_RELEASED         )mvprintw(0, 10, "mouse button 3 up                          ");
  if (event.bstate &        BUTTON3_CLICKED          )mvprintw(0, 10, "mouse button 3 clicked                     ");
  if (event.bstate &        BUTTON3_DOUBLE_CLICKED   )mvprintw(0, 10, "mouse button 3 double clicked              ");
  if (event.bstate &        BUTTON3_TRIPLE_CLICKED   )mvprintw(0, 10, "mouse button 3 triple clicked              ");
  if (event.bstate &        BUTTON4_PRESSED          )mvprintw(0, 10, "mouse button 4 down                        ");
  if (event.bstate &        BUTTON4_RELEASED         )mvprintw(0, 10, "mouse button 4 up                          ");
  if (event.bstate &        BUTTON4_CLICKED          )mvprintw(0, 10, "mouse button 4 clicked                     ");
  if (event.bstate &        BUTTON4_DOUBLE_CLICKED   )mvprintw(0, 10, "mouse button 4 double clicked              ");
  if (event.bstate &        BUTTON4_TRIPLE_CLICKED   )mvprintw(0, 10, "mouse button 4 triple clicked              ");
  if (event.bstate &        BUTTON_SHIFT             )mvprintw(0, 10, "shift was down during button state change  ");
  if (event.bstate &        BUTTON_CTRL              )mvprintw(0, 10, "control was down during button state change");
  if (event.bstate &        BUTTON_ALT               )mvprintw(0, 10, "alt was down during button state change    ");
  attroff( A_REVERSE );
//  if (event.bstate & BUTTON2_PRESSED) goto ERASE;
//  if (event.bstate & BUTTON1_PRESSED) 
  goto DRAW;
  goto TOP;
DRAW:
  mvprintw(event.y, event.x, "%s", "#");
  goto REFRESH;
ERASE:
  mvprintw(event.y, event.x, "%s", " ");
  goto REFRESH;
REFRESH:
  refresh();
  goto TOP;
END:
  endwin();
  return 0; }
