#include "util.h"

void time_function(const std::function<void()> &func) {

  auto start_timer = std::chrono::high_resolution_clock::now();

  func();

  auto end_timer = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
      end_timer - start_timer);

  std::cout << duration.count() << "us" << std::endl;
}
