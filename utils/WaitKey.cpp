#include "WaitKey.h"

#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#include <conio.h>
#include <windows.h>
#else
#endif

#include <atomic>
#include <chrono>
#include <future>

#include <cstdio>

static int ReadKey(std::atomic_bool& stop) {
  int ret = 0;
  while (!stop && ret == 0) {
    ret = _kbhit();
  }

  if (ret != 0) {
    ret = _getch();
  }

  return ret;
}

int WaitKey(int delay) {
  fflush(stdin);

  std::atomic_bool stop(false);
  auto ret = std::async(std::launch::async, &ReadKey, std::ref(stop));

  ret.wait_for(std::chrono::milliseconds(delay));
  stop = true;

  return ret.get();
}