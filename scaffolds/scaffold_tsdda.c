#include "../index/TSDDA.h"
#include <stdio.h>

int main() {
  TStoixeiouDDA s1, s2, s3;

  TSDDA_setValue(&s1, (TStoixeiouDDA){.key = 0, .arrayIndex = 10});
  TSDDA_setValue(&s2, (TStoixeiouDDA){.key = 1, .arrayIndex = 11});
  TSDDA_setValue(&s3, (TStoixeiouDDA){.key = 0, .arrayIndex = 12});

  printf("\n----------------------------\n");
  printf("s1: key = %d, arrayIndex = %d\n", s1.key, s1.arrayIndex);
  printf("s2: key = %d, arrayIndex = %d\n", s2.key, s2.arrayIndex);
  printf("s3: key = %d, arrayIndex = %d\n", s3.key, s3.arrayIndex);
  printf("----------------------------\n");

  TSDDA_setIndex(&s1.arrayIndex, 20);
  TSDDA_setIndex(&s2.arrayIndex, 21);
  TSDDA_setIndex(&s3.arrayIndex, 22);

  printf("\n----------------------------\n");
  printf("s1: key = %d, arrayIndex = %d\n", s1.key, s1.arrayIndex);
  printf("s2: key = %d, arrayIndex = %d\n", s2.key, s2.arrayIndex);
  printf("s3: key = %d, arrayIndex = %d\n", s3.key, s3.arrayIndex);
  printf("----------------------------\n");

  printf("\n----------------------------\n");
  printf(
      "s1.key = %d == s2.key = %d : %d\n", s1.key, s2.key, TSDDA_equal(s1, s2));
  printf(
      "s1.key = %d == s3.key = %d : %d\n", s1.key, s3.key, TSDDA_equal(s1, s3));
  printf(
      "s2.key = %d == s3.key = %d : %d\n", s2.key, s3.key, TSDDA_equal(s2, s3));

  printf("----------------------------\n");
  printf("s1.key = %d < s2.key = %d : %d\n",
         s1.key,
         s2.key,
         TSDDA_smaller(s1, s2));
  printf("s1.key = %d < s3.key = %d : %d\n",
         s1.key,
         s3.key,
         TSDDA_smaller(s1, s3));
  printf("s2.key = %d < s3.key = %d : %d\n",
         s2.key,
         s3.key,
         TSDDA_smaller(s2, s3));

  printf("----------------------------\n");
  printf("s1.key = %d > s2.key = %d : %d\n",
         s1.key,
         s2.key,
         TSDDA_greater(s1, s2));
  printf("s1.key = %d > s3.key = %d : %d\n",
         s1.key,
         s3.key,
         TSDDA_greater(s1, s3));
  printf("s2.key = %d > s3.key = %d : %d\n",
         s2.key,
         s3.key,
         TSDDA_greater(s2, s3));

  printf("----------------------------\n");
  printf("s1.key = %d <= s2.key = %d : %d\n",
         s1.key,
         s2.key,
         TSDDA_smaller_or_equal(s1, s2));
  printf("s1.key = %d <= s3.key = %d : %d\n",
         s1.key,
         s3.key,
         TSDDA_smaller_or_equal(s1, s3));
  printf("s1.key = %d <= s2.key = %d : %d\n",
         s1.key,
         s2.key,
         TSDDA_smaller_or_equal(s1, s2));

  printf("----------------------------\n");
  printf("s1.key = %d >= s2.key = %d : %d\n",
         s1.key,
         s2.key,
         TSDDA_greater_or_equal(s1, s2));
  printf("s1.key = %d >= s3.key = %d : %d\n",
         s1.key,
         s3.key,
         TSDDA_greater_or_equal(s1, s3));
  printf("s1.key = %d >= s2.key = %d : %d\n",
         s1.key,
         s2.key,
         TSDDA_greater_or_equal(s1, s2));

  printf("----------------------------\n");
  printf("s1.key = %d != s2.key = %d : %d\n",
         s1.key,
         s2.key,
         TSDDA_not_equal(s1, s2));
  printf("s1.key = %d != s3.key = %d : %d\n",
         s1.key,
         s3.key,
         TSDDA_not_equal(s1, s3));
  printf("s2.key = %d != s3.key = %d : %d\n",
         s2.key,
         s3.key,
         TSDDA_not_equal(s2, s3));
  printf("----------------------------\n");

  return 0;
}