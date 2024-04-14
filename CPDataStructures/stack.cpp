#include"iostream"
#include"algorithm"
// using namespace std;

namespace CP {

  template <class T>
  class stack {
  protected:
    size_t mCap;
    size_t mSize;
    T* mData;

    // private constructor
    stack(size_t capacity) : mCap(capacity), mSize(0), mData(mCap ? new T[mCap] : nullptr) {}

    void expand(size_t capacity) {
      stack temp(capacity);
      for (size_t i = 0; i < mSize; i++)
        temp.push(std::move(mData[i]));
      swap(*this, temp);
    }
    void ensureCapacity(size_t capacity) {
      if (mCap < capacity)
        expand(std::max(mCap << 1, capacity));
    }

  public:
    // (default) constructor
    stack() : stack(1) {}

    // copy constructor
    stack(const stack& x) : mCap(x.mCap), mSize(x.mSize), mData(new T[mCap]) {
      std::copy(x.mData, x.mData + mSize, mData);
    }

    // move constructor
    stack(stack&& x) : mCap(0), mSize(0), mData(nullptr) {
      *this = std::move(x);
    }

    // destructor
    ~stack() {
      delete[] mData;
    }

    // ------------ assignment -----------

    // copy assignment
    stack& operator=(const stack& x) {
      return *this = stack(x);
    }

    // move assignment
    stack& operator=(stack&& x) {
      swap(*this, x);
      return  *this;
    }

    friend void swap(stack& lhs, stack& rhs) {
      using std::swap;
      swap(lhs.mCap, rhs.mCap);
      swap(lhs.mSize, rhs.mSize);
      swap(lhs.mData, rhs.mData);
    }

    // ------------ capacity function -----------
    bool empty() const { return mSize == 0; }
    size_t size() const { return mSize; }

    // -------------- access ----------------
    const T& top() { return mData[mSize - 1]; }

    // -------------- modifier ----------------
    void push(const T& element) {
      ensureCapacity(mSize + 1);
      mData[mSize++] = element;
    }

    void push(T&& element) {
      ensureCapacity(mSize + 1);
      mData[mSize++] = std::move(element);
    }

    void pop() {
      --mSize;
    }

    // ------------- extra (unlike STL) ------------
    void print(std::ostream& str = std::cout) const {
      str << "Stack Data: [";
      for (size_t i = 0; i < mSize; i++)
        str << mData[i] << " ";
      str << "], Size: " << mSize << "\n";
    }

  };

}



using Stack = CP::stack<int>;
Stack reverse(Stack s) {
  Stack result;
  while (!s.empty()) result.push(s.top()), s.pop();
  return result;
}

int main() {
  using std::cout;
  Stack s1;
  cout << "Size: " << s1.size() << "\n";
  for (int i = 0; i < 10; i++) {
    int val = 1 << i;
    s1.push(val);
    cout << "Push: " << val << " (Size: " << s1.size() << ")\n";
  }

  cout << "\n-----------------------------------\n\n";

  s1.print();
  Stack s2 = s1;

  cout << "Size: " << s1.size() << "\n";
  while (!s1.empty()) {
    int val = s1.top();
    s1.pop();
    cout << "Pop: " << val << " (Size: " << s1.size() << ")\n";
  }

  cout << "\n-----------------------------------\n\n";

  CP::stack<Stack> vec;
  vec.push(s2);
  vec.push(reverse(s2));

  while (!vec.empty())
    vec.top().print(), vec.pop();
}