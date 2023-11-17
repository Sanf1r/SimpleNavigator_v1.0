#include "./controller.h"
#include "./view.h"

int main() {
  std::locale::global(std::locale("C"));
  Model model;
  Controller controller(&model);
  View view(&controller);
  view.startEventLoop();

  return 0;
}