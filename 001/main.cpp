#include <cstddef>
#include <cstdint>
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
    OkClass() { year = 2019; }

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
  // palatable narrative of c++ initialization

  // init to 0
  int aa = 0;  // literal, ok
  int bb{};    // brace, ok
  int cc = {}; // equal and brace, ok
  int dd;      // maybe not ok
  printf("aa=%d, bb=%d, cc=%d, dd=%d\n", aa, bb, cc, dd);

  // braced intialization is always working

  // init to an arbitrary value
  // all these 4 ways produce identical code
  int ee = 42;   // equals
  int ff{42};    // braced initialization
  int gg = {42}; // equals-plus-braces initialization
  int hh(42);    // parentheses
  printf("ee=%d, ff=%d, gg=%d, hh=%d\n", ee, ff, gg, hh);

  // init PODs
  struct PodStruct {
    uint64_t a;
    char b[256];
    bool c;
  };

  PodStruct p1{};    // all fields zeroed
  PodStruct p2 = {}; // identical

  PodStruct p3{42, "Hello"}; // c zeroed
  PodStruct p4 = {
      42, "Hello"}; // identical
                    // the equals-plus-braces initialization works identical

  // you can only omit fields from right to left
  /*PodStruct p5{42, true}; // try to omit fields b but this won't work */
  /*printf("p5, a=%llu, b=%s, c=%d\n", p5.a, p5.b, p5.c);*/

  // init arrays
  int arr1[]{1, 2, 3};  // array of length 3; [1, 2, 3]
  int arr2[5]{};        // array of length 5; [0,0,0,0,0]
  int arr3[5]{1, 2, 3}; // array of length 5; [1,2,3,0,0]
  int arr4[5];          // array of length 5; uninitialized values

  // init fully featured classes
  // unlike fundamental types and PODs, fully featured classes are always
  // initialized.
  // in other words, one of a fully featured class's constructors always
  // called during initialization.
  // which constructor is called depends on the arguments given during
  // initialization.

  sp("init fully featured classes");
  struct A {
    A() { printf("(no arg)\n"); }

    A(char x) { printf("(char: %c)\n", x); }

    A(int x) { printf("(int: %d)\n", x); }

    A(float x) { printf("(float: %f)\n", x); }
  };

  A b1;
  A b2{'c'};
  A b3{65537};
  A b4{6.02e23f};
  A b5('g');    // also works
  A b6 = {'l'}; // also works, invoke the expected constructor
  A b7{};       // also works as b1
  // A b8(); // nope, wont' work. this is parsed as a function declaration

  // narrowing conversions
  float ff1{1};
  float ff2{2};
  int res1(ff1 / ff2); // potentially nasty narrowing without warning
  /*int res2{ff1 / ff2}; // narrowing with warning (or compiler error) won't compile here */
  int res2{static_cast<int>(ff1 / ff2)}; // narrowing with warning (or compiler error)

  printf("res2 %d\n", res2);

  // init class members
  struct Classs {
    bool a = true; // equals init
    int b{1}; // braced init
    char s[8] = {"x-rated"};  // braces-plus-equals init, need to specify length explicitly for members
  };

  Classs ccc;
  printf("a=%d, b=%d, s=%s\n", ccc.a, ccc.b, ccc.s);

  // general rule: use the braced init (uniform initialization) everywhere by default
  // except for certain classes in stdlib

  // destructors
  // almost never called explicitly
  // for actions include releasing file handles, flushing network sockets, and freeing dynamic objects.
  // compiler will generate one that does nothing if you don't specify one

  struct Clazz {
    Clazz() {
      printf("Clazz init\n");
    }
    ~Clazz() {
      printf("Clazz destructor called\n");
    }
  };
  Clazz z;
  return 0;
}
