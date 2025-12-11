#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#define ctrl(x) ((x) & 0x1f)

int main() {

  // screen | var
  int my, mx;

  // mouse loc | var
  int sx, sy;

  // startup
  initscr();
  noecho();
  curs_set(2);
  keypad(stdscr, TRUE);

  clear();
  refresh();
  nonl();

  // screenmax
  getmaxyx(stdscr, sy, sx);
  // printf("%d,%d\n", sx, sy);

  border(0, 0, 0, 0, 0, 0, 0, 0);
  mvprintw(0, 2, "Drawpot");

  // cursor pos
  wmove(stdscr, (sy / 2), (sx / 2));

  // key
  while (1) {
    int ch = getch();
    // cursor loc
    getyx(stdscr, my, mx);

    switch (ch) {
      // drawing
    case 'H':
      mvaddstr(my, mx - 2, "*"); // whats wrong here?
      break;
    case 'J':
      mvaddstr(my + 1, mx - 1, "*");
      break;
    case 'K':
      mvaddstr(my - 1, mx - 1, "*");
      break;
    case 'L':
      mvaddstr(my, mx + 1, "*");
      break;
      // move
    case 'h':
      move(my, mx - 2); // same problem
      break;
    case 'j':
      move(my + 1, mx);
      break;
    case 'k':
      move(my - 1, mx);
      break;
    case 'l':
      move(my, mx + 2);
      break;
      // erasing
    case ctrl('h'):
      mvaddstr(my, mx - 2, " ");
      break;
    case ctrl('j'):
      mvaddstr(my + 1, mx - 1, " ");
      break;
    case ctrl('k'):
      mvaddstr(my - 1, mx - 1, " ");
      break;
    case ctrl('l'):
      mvaddstr(my, mx + 1, " ");
      break;
      // quit
    case 'q':
      endwin();
      exit(1);
    }
  }

  getch();
  endwin();
}
