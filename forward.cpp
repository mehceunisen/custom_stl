
template <typename _Tp>
struct __type_deducer {
  static constexpr int value = 0;
};

template <typename _Tp>
struct __type_deducer<_Tp&> {
  static constexpr int value = 1;
};


int main() {
  int x = 0;
  
  return ::__type_deducer<int>::value;


}
