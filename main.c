#include <ncurses.h>
#include <stdbool.h>

int main() {
  initscr();
  noecho();
  curs_set(2);
  keypad(stdscr, TRUE);

  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);

  int y = max_y / 2, x = max_x / 2;
  bool drawing = false;
  bool erasing = false;

  border(0, 0, 0, 0, 0, 0, 0, 0);
  mvprintw(0, 2, "Drawpot");
  mvprintw(max_y - 1, 1,
           " hjkl = move | w/e/b = jump (draws if active) | SPACE = Toggle "
           "draw | x = "
           "erase | q = quit ");
  move(y, x);
  refresh();

  int ch;
  while ((ch = getch()) != 'q') {
    int steps = 0; // for drawing multiple points
    int dx = 0, dy = 0;

    switch (ch) {
    // Basic movement
    case KEY_LEFT:
    case 'h':
      dx = -1;
      steps = 2;
      break;
    case KEY_RIGHT:
    case 'l':
      dx = 1;
      steps = 2;
      break;
    case KEY_UP:
    case 'k':
      dy = -1;
      steps = 2;
      break;
    case KEY_DOWN:
    case 'j':
      dy = 1;
      steps = 2;
      break;
    case 'w':
      dx = 1;
      steps = 5;
      break; // jump right
    case 'b':
      dx = -1;
      steps = 5;
      break; // jump left
    case 'd':
      dy = 1;
      steps = 3;
      break; // jump down
    case 'u':
      dy = -1;
      steps = 3;
      break; // jump down
    case ' ':
      drawing = !drawing;
      erasing = false;
      break;
    case 'x':
      erasing = !erasing;
      drawing = false;
      break;
    }

    // Move with multiple steps
    for (int i = 0; i < steps; i++) {
      x += dx;
      y += dy;

      // Boundary check
      if (x < 1)
        x = 1;
      if (x > max_x - 2)
        x = max_x - 2;
      if (y < 1)
        y = 1;
      if (y > max_y - 2)
        y = max_y - 2;

      // Draw trail if active
      if (drawing) {
        mvaddch(y, x, '*');
        mvprintw(0, 2, "Drawing");
      } else if (erasing) {
        mvaddch(y, x, ' ');
        mvprintw(0, 2, "Erasing");
      } else {
        mvprintw(0, 2, "Drawpot");
      }
    }

    move(y, x);
    refresh();
  }

  endwin();
  return 0;
}
