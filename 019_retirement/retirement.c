#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double showMoney(int startAge, retire_info stage, double amount) {
  // printf("Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, amount);
  for (int i = 0; i < stage.months; i++) {
    int age = startAge / 12;
    int month = startAge % 12;
    printf("Age %3d month %2d you have $%.2lf\n", age, month, amount);
    amount += stage.contribution + amount * stage.rate_of_return / 12;
    startAge++;
  }
  return amount;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  //  printf("Age %3d month %2d you have $%.2lf\n", startAge / 12, startAge % 12, initial);
  double amount = showMoney(startAge, working, initial);
  showMoney(startAge + working.months, retired, amount);
}

int main(void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045;
  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01;
  int startAge = 327;
  double initial = 21345;
  retirement(startAge, initial, working, retired);
  return 1;
}
