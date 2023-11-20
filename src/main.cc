#include "Controller/controller.h"
#include "Model/model.h"
#include "View/view.h"

int main() {
  std::locale::global(std::locale("C"));
  Model model;
  Controller controller(&model);
  View view(&controller);
  view.StartEventLoop();

  return 0;
}