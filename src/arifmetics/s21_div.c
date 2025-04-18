#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  init(result);
  if (is_zero(value_2)) return 3;
  if (is_zero(value_1)) {
    *result = value_1;
    return 0;
  }
  int main_sign = 0;
  if (get_sign(value_1) ^ get_sign(value_2)) main_sign = 1;
  big_decimal val1;
  init_big(&val1);
  big_decimal val2;
  init_big(&val2);
  big_decimal res;
  init_big(&res);
  from_dec_to_big(value_1, &val1);
  from_dec_to_big(value_2, &val2);
  res.scale = get_scale(value_1) - get_scale(value_2);
  simple_div_big(val1, val2, &res);
  int out = 0;
  if (res.scale < 0) {
    if (main_sign == 1)
      out = 2;
    else
      out = 1;
  } else {
    out = from_big_to_dec(res, result);
    if (out == 1 && main_sign == 1) out = 2;
    set_sign(result, main_sign);
    if (is_zero(*result)) {
      set_scale(result, 0);
    }
  }
  return out;
}
