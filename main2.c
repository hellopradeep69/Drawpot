#include <ncurses.h>
#include <stdio.h>

int main() {

  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);

  int max_x, max_y;
  getmaxyx(stdscr, max_y, max_x);

  int y = max_y / 2, x = max_x / 2;
  bool drawing = false, erasing = false;

  printf("%d, %d\n", y, x);

  border(0, 0, 0, 0, 0, 0, 0, 0);

  const char *title = "Drawpit";
  //
  // addch('*' | A_BOLD);
  //
  // getch();
}
