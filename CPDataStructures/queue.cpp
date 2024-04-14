#include"iostream"
#include"algorithm"
// using namespace std;

namespace CP {

  template <class T>
  class queue {
  protected:
    size_t mCap;
    size_t mSize;
    size_t mFront;
    T* mData;

    // private constructor
    queue(size_t capacity) : mCap(capacity), mSize(0), mFront(0), mData(mCap ? new T[mCap] : nullptr) {}

    void expand(size_t capacity) {
      queue temp(capacity);
      for (size_t i = 0; i < mSize; i++)
        temp.push(std::move(mData[(mFront + i) % mCap]));
      swap(*this, temp);
    }
    void ensureCapacity(size_t capacity) {
      if (mCap < capacity)
        expand(std::max(mCap << 1, capacity));
    }

  public:
    // (default) constructor
    queue() : queue(1) {}

    // copy constructor
    queue(const queue& x) : mCap(x.mCap), mSize(x.mSize), mFront(x.mFront), mData(new T[mCap]) {
      std::copy(x.mData, x.mData + mCap, mData);
    }

    // move constructor
    queue(queue&& x) : mCap(0), mSize(0), mFront(0), mData(nullptr) {
      *this = std::move(x);
    }

    // destructor
    ~queue() {
      delete[] mData;
    }

    // ------------ assignment -----------

    // copy assignment
    queue& operator=(const queue& x) {
      return *this = queue(x);
    }

    // move assignment
    queue& operator=(queue&& x) {
      swap(*this, x);
      return  *this;
    }

    friend void swap(queue& lhs, queue& rhs) {
      using std::swap;
      swap(lhs.mCap, rhs.mCap);
      swap(lhs.mSize, rhs.mSize);
      swap(lhs.mFront, rhs.mFront);
      swap(lhs.mData, rhs.mData);
    }

    // ------------ capacity function -----------
    bool empty() const {
      return mSize == 0;
    }
    size_t size() const {
      return mSize;
    }

    // -------------- access ----------------
    const T& front() {
      return mData[mFront];
    }
    const T& back() {
      return mData[(mFront + mSize - 1) % mCap];
    }

    // -------------- modifier ---------------
    void push(const T& element) {
      ensureCapacity(mSize + 1);
      mData[(mFront + mSize) % mCap] = element;
      ++mSize;
    }
    void push(T&& element) {
      ensureCapacity(mSize + 1);
      mData[(mFront + mSize) % mCap] = std::move(element);
      ++mSize;
    }
    void pop() {
      --mSize;
      mFront = (mFront + 1) % mCap;
    }

    // ------------- extra (unlike STL) ------------
    void print(std::ostream& str = std::cout) const {
      str << "Queue Data: [";
      for (size_t i = 0; i < mSize; i++)
        str << mData[(mFront + i) % mCap] << " ";
      str << "], Size: " << mSize << "\n";
    }
  };
}



using Queue = CP::queue<int>;
Queue rotate(const Queue& q, size_t n) {
  Queue result(q);
  n %= q.size();
  for (n %= q.size(); n; n--) {
    result.push(result.front());
    result.pop();
  }
  return result;
}

int main() {
  using std::cout;
  Queue q1;
  cout << "Size: " << q1.size() << "\n";
  for (int i = 0; i < 10; i++) {
    int val = 1 << i;
    q1.push(val);
    cout << "Push: " << val << " (Size: " << q1.size() << ")\n";
  }

  cout << "\n-----------------------------------\n\n";

  q1.print();
  Queue q2 = q1;

  cout << "Size: " << q2.size() << "\n";
  while (!q1.empty()) {
    int val = q1.front();
    q1.pop();
    cout << "Pop: " << val << " (Size: " << q1.size() << ")\n";
  }

  cout << "\n-----------------------------------\n\n";

  CP::queue<Queue> ctnr;
  ctnr.push(q2);
  ctnr.push(rotate(q2, 103));

  while (!ctnr.empty())
    ctnr.front().print(), ctnr.pop();
}