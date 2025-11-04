#include <ncurses.h>
#include <stdbool.h>
#include <string.h>

#define MAX_POINTS 10000 // simple fixed-size canvas (for demo)

typedef struct {
  int y, x;
} Point;

int main() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);

  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);

  int y = max_y / 2, x = max_x / 2;
  bool drawing = false, erasing = false;

  Point canvas[MAX_POINTS];
  int canvas_size = 0;

  const char *title = "Drawpit";

  while (1) {
    clear();

    // Draw title centered
    mvprintw(0, (max_x - (int)strlen(title)) / 2, "%s", title);

    // Draw all points
    for (int i = 0; i < canvas_size; i++) {
      mvaddch(canvas[i].y, canvas[i].x, '*');
    }

    // Choose cursor char
    char cursor_char = '@';
    if (drawing)
      cursor_char = '#';
    else if (erasing)
      cursor_char = 'X';

    mvaddch(y, x, cursor_char);
    refresh();

    int ch = getch();

    if (ch == 'q')
      break;              // Quit
    else if (ch == ' ') { // Toggle drawing
      drawing = !drawing;
      erasing = false;
      if (drawing && canvas_size < MAX_POINTS)
        canvas[canvas_size++] = (Point){y, x};
    } else if (ch == 'x') { // Toggle erasing
      erasing = !erasing;
      drawing = false;
      // remove current point
      for (int i = 0; i < canvas_size; i++) {
        if (canvas[i].y == y && canvas[i].x == x) {
          for (int j = i; j < canvas_size - 1; j++)
            canvas[j] = canvas[j + 1];
          canvas_size--;
          break;
        }
      }
    } else if (ch == 'c') { // Clear canvas
      canvas_size = 0;
    } else if (ch == 'h' && x > 0)
      x--;
    else if (ch == 'l' && x < max_x - 1)
      x++;
    else if (ch == 'k' && y > 1)
      y--;
    else if (ch == 'j' && y < max_y - 1)
      y++;

    // Drawing or erasing as you move
    if (drawing && canvas_size < MAX_POINTS) {
      canvas[canvas_size++] = (Point){y, x};
    }
    if (erasing) {
      for (int i = 0; i < canvas_size; i++) {
        if (canvas[i].y == y && canvas[i].x == x) {
          for (int j = i; j < canvas_size - 1; j++)
            canvas[j] = canvas[j + 1];
          canvas_size--;
          break;
        }
      }
    }
  }

  endwin();
  return 0;
}
