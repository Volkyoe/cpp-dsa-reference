#include"algorithm"
#include"iostream"
using std::cout;

template <class T = int>
class dumb_array {
private:
  size_t mSize;
  T* mArray;

public:
  // (default) constructor
  dumb_array(size_t size = 0) : mSize(size), mArray(mSize ? new T[mSize] : nullptr) {
    cout << "In dumb_array(size_t = " << mSize << ").\n";
  }

  // copy constructor
  dumb_array(const dumb_array& other) : mSize(other.mSize), mArray(mSize ? new T[mSize] : nullptr) {
    cout << "In dumb_array(const dumb_array&).\t COPY ctor (mSize: " << mSize << ")\n";
    std::copy(other.mArray, other.mArray + mSize, mArray);
  }

  // move constructor
  dumb_array(dumb_array&& other) noexcept : mSize(0), mArray(nullptr) {
    cout << "In dumb_array(dumb_array&&).\t\t MOVE ctor (mSize: " << mSize << ")\n";
    swap(*this, other);
  }

  // destructor
  ~dumb_array() {
    cout << "In ~dumb_array().\n";
    delete[] mArray;
  }

  // copy assignment
  dumb_array& operator=(const dumb_array& other) {
    cout << "In operator=(const dumb_array&).\t COPY assign.\n";
    return *this = dumb_array(other);
  }

  // move assignment
  dumb_array& operator=(dumb_array&& other) noexcept {
    cout << "In operator=(dumb_array&&).\t\t MOVE assign.\n";
    swap(*this, other);
    return *this;
  }

  friend void swap(dumb_array& lhs, dumb_array& rhs) noexcept {
    using std::swap; // enable ADL
    swap(lhs.mSize, rhs.mSize);
    swap(lhs.mArray, rhs.mArray);
  }

  size_t size() const { return mSize; }
};

dumb_array<> f(dumb_array<> a) {
  cout << "f()\n";
  return a;
}
int main() {
  dumb_array a1(5), a2;
  cout << "--------------------------\n";
  cout << f(a1).size() << "\n";
  cout << "--------------------------\n";
  a2 = std::move(a1);
  cout << "--------------------------\n";
  a1 = a2;
  cout << "--------------------------\n";
}