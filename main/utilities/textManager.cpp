#include <Arduino.h>

bool areSimilarStrings(String a, String b) {
    int count = 0;
    for (int i=0; i<a.length(); i++) {
        if (a.charAt(i) == b.charAt(i))
            count++;
    }
    if (count >= (a.length() / 2))
        return true;
    return false;
}