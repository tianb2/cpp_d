#include <cstddef>
#include <cstdio>
#include <iterator>

void sp(const char *title) { printf("------%s------\n", title); }

int main() {
  printf("hello me\n");
  int a = 1;
  printf("Ten %d, Twenty %d, Thirty %d\n", 10, 20, 30);

  sp("integer types");
  // integer types
  unsigned short n1 = 0b10101010;
  printf("n1=%hu\n", n1);

  int n2 = 0123;
  printf("n2=%d\n", n2);

  int n3 = 011;
  printf("n3=%d\n", n3);

  unsigned long long d = 0xFFFFFFFFFF;
  printf("n4=%llu\n", d);

  sp("floating points");
  // floating-point types
  float f1 = 0.1F;
  double f2 = 0.2;
  long double f3 = 0.3L;
  double f4 = 1e3; // base 10

  printf("f4=%lf, %le, %lg\n", f4, f4, f4);

  // sizeof returns the size in bytes

  size_t size_c = sizeof(char);
  printf("char: %zu\n", size_c);
  printf("char a: %zu\n", sizeof('a'));

  // array initialization
  int my_array[100];
  printf("size of 100 int array: %zu\n", sizeof(my_array));

  int a2[] = {1, 2, 3, 4};
  printf("size of a2 array: %zu\n", sizeof(a2));

  printf("size of size_t? %zu\n", sizeof(size_t));

  // some for loops

  unsigned long values[] = {10, 50, 20, 40, 0};
  size_t n_elements = sizeof(values) / sizeof(unsigned long);
  for (size_t i = 0; i < n_elements; i++)
    printf("%zu => %lu \n", i, values[i]);

  sp("--");
  for (unsigned long value : values) {
    printf("%lu \n", value);
  }

  // c-style strings
  // or the null-terminated strings
  char s1[] = "abc";
  printf("size of %s is %zu\n", s1, std::size(s1));

  // print unicode is complicated
  // see wprintf in <cwchar>

  char s2[27];
  for (int i = 0; i < 26; i++) {
    s2[i] = i + 97;
  }
  s2[26] = 0; // NULL
  sp("");
  printf("s2 is %s\n", s2);

  // user-defined types
  // enums, classes, unions

  enum class Color {
    Red,
    Blue,
    Green,
  };

  // enum or scoped enum
  // avoid the un-scoped one by default
  Color color = Color::Blue;

  // switch
  // remember to 'break'
  // {} after each case is highly recommended
  switch (color) {
  case Color::Blue: {
    printf("blue\n");
    break;
  }
  case Color::Red: {
    printf("red\n");
    break;
  }
  case Color::Green: {
    printf("green\n");
    break;
  }
  default: {
    printf("unknown\n");
  }
  }

  // classes
  // plain-old-data classes, POD?
  // as a general rule, you should order memebers from
  // largest to smallest within POD elements
  struct Book {
    char name[256];
    int year;
    int pages;
    bool hardcover;
  };
  Book book;
  book.pages = 271;

  sp("");

  // unions
  // that puts all of its memebers in the same place
  // should be rarely used
  union Variant {
    char sring[10];
    int integer;
    double floating_point;
  };
  Variant v;
  v.integer = 42;
  printf("v.integer %d\n", v.integer);
  v.floating_point = 1.23;
  printf("v.floating_point %f\n", v.floating_point);
  /*printf("v.integer %d\n", v.integer); -- not good*/

  sp("some");
  // class with methods
  struct SomeClass {
    void add_year() { year++; }
    int year;
  };

  SomeClass some;
  some.year = 2017;
  some.add_year();
  printf("year: %d\n", some.year);

  // struct members are public by default
  struct AnotherClass {
    void add_year() { year++; }
    bool set_year(int new_year) {
      if (new_year < 2019)
        return false;
      year = new_year;
      return true;
    }
    int get_year() { return year; }

  private:
    int year;
  };

  sp("another");

  AnotherClass another;
  bool ok = another.set_year(2020);
  printf("year=%d, ok=%d\n", another.get_year(), ok);

  // class members are private by default
  // there is absolutely no difference between struct and class
  // aside from the default access control
  // I prefer using struct keywords because i like having the public
  // members listed first. but there are all kinds of conventions in the wild
  // cultivate a style and stick to it.

  class SomeClass2 {
    int year;

  public:
    void add_year() { year++; }

    int get_year() { return year; }
  };

  sp("constructors");

  // you see the year can be initialized like an uninitialized variables
  // class invariant: a feature of a class that is always true e.g. year >= 2019
  // adding constructors to enforce it from the beginning

  struct OkClass {
    OkClass() {
      year = 2019;
    }

    OkClass(int year_in) {
      if (!set_year(year_in)) {
        year = 2019;
      }
    }

    void add_year() { year++; }
    bool set_year(int new_year) {
      if (new_year < 2019)
        return false;
      year = new_year;
      return true;
    }
    int get_year() { return year; }

  private:
    int year;
  };

  OkClass ok1 = OkClass();
  printf("ok1, year %d\n", ok1.get_year());
  OkClass ok2 = OkClass{2020}; // the conjuration is called an initialization
  printf("ok2, year %d\n", ok2.get_year());
  OkClass ok3 = OkClass{2018};
  printf("ok3, year %d\n", ok3.get_year());

  sp("initialization");

  return 0;
}
