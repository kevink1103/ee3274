#include <Arduino.h>

bool isAllNumbers(String base) {
  // Check if the whole string is composed of numbers
  for (int i=0; i<base.length(); i++) {
    if (isAlpha(base.charAt(i)))
      return false;
  }
  return true;
}

String getOnlyNum(String base) {
  String result = "";
  for (int i=0; i<base.length(); i++) {
    if (isDigit(base.charAt(i))) {
      result += base.charAt(i);
    }
  }
  return result;
}

bool areSimilarStrings(String a, String b) {
  if (a.length() == 0) {
    return false;
  }
  int count = 0;
  for (int i=0; i<a.length(); i++) {
      if (a.charAt(i) == b.charAt(i))
          count++;
  }
  if (count >= (a.length() / 2))
      return true;
  return false;
}
