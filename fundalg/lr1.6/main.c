#include "actions.h"

int main(int argc, char *argv[]) {

  UserInput input;
  StatusCode status = InputParse(&input, argv, argc);

  if (status != OK) {
    PrintErrors(status);
    return status;
  }

  double answer = 0.0;

  switch (input.option) {
  case 'a':
    status = forA(&input, &answer);
    break;

  case 'b':
    status = forB(&input, &answer);
    break;

  case 'c':
    status = forC(&input, &answer);
    break;

  case 'd':
    status = forD(&input, &answer);
    break;

  default:
    break;
  }

  if (status != OK) {
    PrintErrors(status);
    return status;
  }

  printf("%.12f\n", answer);

  return OK;
}
