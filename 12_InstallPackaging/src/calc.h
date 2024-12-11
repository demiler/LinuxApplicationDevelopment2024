#ifndef CALC_AVG_APP_H
#define CALC_AVG_APP_H

/** Calculates average of sum of all the numbers in the array
  *
  * @param n Number of elements in array
  * @param numbers Array itself containing all the integer numbers
  * @returns results of very complex calculations
  */

long long int average_sum(int n, int *numbers);

/** Calculates average of multiplication of all the numbers in the array.
  * Uses strong optimizations for 0 elements in the array.
  *
  * @param n Number of elements in array
  * @param numbers Array itself containing all the integer numbers
  * @returns results of even more complex calculations
  */
long long int average_mul(int n, int *numbers);

#endif
