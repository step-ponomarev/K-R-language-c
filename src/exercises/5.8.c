#include "../lib/asserts.h"

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

int day_of_year(unsigned int year, unsigned int month, unsigned int day) {
  if (month < 1 || month > 12) {
    return -1;
  }

  const int leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  if (day > daytab[leap][month]) {
    return -1;
  }

  for (int i = 1; i < month; i++) {
    day += daytab[leap][i];
  }

  return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
  const int leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  char *days = daytab[leap];
  days++;

  while (yearday > 0) {
    yearday -= *days++;
  }
  yearday += *(days - 1);

  *pday = yearday;
  *pmonth = days - daytab[leap];
}

int main() {
  assertEquals("Check 29.04.25", 119, day_of_year(2025, 4, 29));
  assertEquals("Check 29.04.24", 120, day_of_year(2024, 4, 29));
  assertEquals("Check 32.04.25", -1, day_of_year(2025, 4, 32));
  assertEquals("Check 29.13.25", -1, day_of_year(2025, 13, 32));

  int mday;
  int month;
  month_day(2025, 119, &month, &mday);
  assertEquals("Check 119 2025 month day", 29, mday);
  assertEquals("Check 119 2025 month", 5, month);

  return 0;
}
