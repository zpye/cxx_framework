#include "WaitKey.h"

#include <atomic>
#include <chrono>
#include <future>

#include <cstdio>

#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)

#include <conio.h>
#include <windows.h>

static int ReadKey(std::atomic_bool& stop) {
  int ret = 0;
  while (!stop && ret == 0) {
    ret = _kbhit();
  }

  if (ret != 0) {
    ret = _getch();
  } else {
    ret = EOF;
  }

  return ret;
}

#else

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

// https://gist.github.com/vsajip/1864660
int _kbhit(int& ch) {
  struct termios oldt;
  tcgetattr(STDIN_FILENO, &oldt);

  struct termios newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  fcntl(STDIN_FILENO, F_SETFL, oldf);
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  if (ch != EOF) {
    return 1;
  }

  return 0;
}

static int ReadKey(std::atomic_bool& stop) {
  int ret = 0;
  int ch = EOF;
  while (!stop && ret == 0) {
    ret = _kbhit(ch);
  }

  return ch;
}

#endif

int WaitKey(int delay) {
  fflush(stdin);

  std::atomic_bool stop(false);
  auto ret = std::async(std::launch::async, &ReadKey, std::ref(stop));

  if (delay > 0) {
    ret.wait_for(std::chrono::milliseconds(delay));
  } else {
    ret.wait();
  }

  stop = true;

  return ret.get();
}