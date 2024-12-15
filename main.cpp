/**
 * @Title	벗어 나야 할 C++ 뉴비의 습관
 * @brief	31가지 C++ 뉴비 들이 버려야 하는 습관 31가지 예제
 * @URL		https://www.youtube.com/watch?v=i_wDa2AS_8w&list=PLJ_usHaf3fgM5vOBPY-hXAjUy6SbgE-KG
 */

#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <array>
#include <bit>
#include <unordered_map>

#include <thread>

#include <algorithm>

/**
 * @no.1
 * @brief	using namespace std
 * @desc	namespace의 선언은 global 하게 하며, 헤더에 있으면 종속성이 생기므로, 헤더에 선언하지 말자
 *			또한 사용하는 부분만 선언해서 사용하자
 */

using namespace std;
//using std::string, std::cout, std::endl; // Over C++17

void using_namespace_std()
{
	string s{ "hello, world!" };
	std::cout << s << std::endl;
}

/**
 * @no.2
 * @brief	using std endl in a loop
 * @desc	std endl은 출력 버퍼를 flush(시간을 많이 먹음) 하므로 루프 안에서는 사용하지 않는다.
 */
void print_range(int start, int end)
{
	// Time issue
	for (auto i = start; i != end; ++i)
	{
		//cout << i << endl;
		cout << i << '\n';
	}
}

/**
 * @no.3
 * @brief	index based for when range-for fit better
 * @desc	인덱스를 사용하는 것 보다 range base를 사용하는 것이 좋다.
 */
//void train_model(const std::vector<int>& data, auto & model)
//{
//	/* 
//	for (std::size_t i = 0; i < data.size(); ++i)
//	{
//		model.update(data[i]);
//	}
//	*/
//
//	for (const auto& x : data)
//	{
//		model.update(x);
//	}
//}

/**
 * @no.4
 * @brief	rewriting std algorithms
 * @desc	무언가를 할때 std 알고리즘을 사용하는 것이 좋다.
 */
void know_your_algorithms()
{
	const std::vector<int> data = { -1,-3,-5,8,15,-1 };
	const auto is_positive = [](const auto& x) {return x > 0; };
	auto first_pos_it = std::find_if(data.cbegin(), data.cend(), is_positive);
}

/**
 * @no.5
 * @brief	using C array over std array
 * @desc	C 스타일의 배열 보다 스탠다드 array를 사용하는 것이 좋다.
 */
void using_c_array()
{
	const int n = 256;
	//int arr[n] = { 0, };
	std::array<int, n> arr{};
}

/**
 * @no.6
 * @brief	any use of reinterpret cast
 * @desc	C 스타일의 배열 보다 스탠다드 array를 사용하는 것이 좋다.
 */
void any_use_of_reinterpret_cast()
{
	long long x = 0;
	auto xp = reinterpret_cast<char*> (x);
	auto x2 = reinterpret_cast<long long>(xp);
}


// Over C++20
template<typename T>
void print_bytes1(const T& input)
{
	auto* bytes = reinterpret_cast<const std::byte*>(&input);
}

template<typename T>
void print_bytes2(const T& input)
{
	using bytearray = std::array<std::byte, sizeof(T)>;
	const auto& bytes = std::bit_cast<bytearray, T>(input);
}

// 다음 방법을 응용하여 만든 bit field 사용법 법
typedef struct bitfield
{
	unsigned int a1 : 8;
	unsigned int a2 : 16;
	unsigned int a3 : 3;
	unsigned int a4 : 5;
};

template<typename T, typename U>
void print_bytes3(const T& input)
{
	const auto& bytes = std::bit_cast<U, T>(input);
}

/**
 * @no.7	
 * @brief	casting away const
 * @desc	const_cast를 사용하여 const 속성을 제거하는 것은 좋지 않다.
 */
const std::string& more_frequent(const std::unordered_map<std::string, int>& word_counts
	, const std::string& word1
	, const std::string& word2)
{
	// auto& counts = const_cast<std::unordered_map<std::string, int>&>(word_counts);
	// return counts[word1] > counts[word2] ? word1 : word2;

	return word_counts.at(word1) > word_counts.at(word2) ? word1 : word2;
}

/**
 * @no.8
 * @brief	
 */

 /**
  * @no.9
  * @brief	Ignoring const-correctness
  * @desc	인자의 변화가 없을 때는 항상 const 키워드로 선언해 주자
  */
void print_vec_one_per_line(const std::vector<int> & arr)
{
	for (const auto & x : arr)
	{
		cout << x << '\n';
	}
}

/**
 * @no.10
 * @brief	Not knowing string literal lifetime
 * @desc	다음은 프로그램이 종료될 때까지 아래 문자열을 메모리에 남아 있는다.
 *			따라서 아래와 같이 지역변수 처럼 리턴해도 괜찮다.
 */
const char* string_literal_lifetime()
{
	return "string literals";
}

/**
 * @no.11
 * @brief	not using structured bindings
 * @desc	first, second를 사용하는 바인딩을 사용하지 말고 직접 이름을 사용하도록 하자
 *			일반 구조체도 가능하다.
 */
void loop_map_items()
{
	std::unordered_map<std::string, std::string> colors = {
		{"Red",		"#FF0000"},
		{"Green",	"#00FF00"},
		{"Blue",	"#0000FF"}
	};

	// Over C++17
	for (const auto& [name, hex] : colors)
	{
		std::cout << "name : " << name << ", hex : " << hex << '\n';
	}
}

/**
 * @no.12
 * @brief	out-params instead of returning a struct
 * @desc	인자에 결과값을 받을 다수의 out 인자를 넣지 말고, 구조체를 만들어서 리턴 시켜라
 */
struct values
{
	int x, y;
};

values get_values_return_struct(const int n)
{
	return { n, n + 1 };
}

void use_value()
{
	// Over C++17
	auto [x, y] = get_values_return_struct(3);
}

/**
 * @no.13
 * @brief	not using constexpr
 * @desc	컴파일 시간에 계산되는 constexpr 키워드를 사용하자
 */
int sum_of_1_to_n(const int n)
{
	return n * (n + 1) / 2;
}

void used_sum()
{
	const int limit = 1000;
	auto triangle_n = sum_of_1_to_n(limit);
}

/**
 * @no.14
 * @brief	forgetting to mark destructor virtual
 * @desc	소멸자에 virtual 키워드를 붙이자
 *			워낙 유명한 것이니 설명은 생략한다.
 */
class BaseWithNonvirtualDestructor
{
public:
	void foo()
	{
		std::cout << "do foo\n";
	}

	virtual ~BaseWithNonvirtualDestructor()
	{
		std::cout << "called base destructor\n";
	}
};

/**
 * @no.15
 * @brief	thinking class memebers init in order of init list
 * @desc	생성자에서 8초기화는 초기화 리스트의 선언 된 순서가 아닌 클래스의 멤버 선언 순서로 초기화 된다.
 *			따라서 영향성이 있는 멤버 변수들을 초기화 할떄 조심해야 한다.
 */
class View
{
public:
	//View(char* start, std::size_t size) : m_start{ start }, m_end { m_start + size } 에러
	View(char* start, std::size_t size) : m_start{ start }, m_end{ start + size }
	{

	}
private:
	char* m_end;
	char* m_start;
};

/**
 * @no.16
 * @breif	Not Knowing about default vs value intialization
 * @desc	변수 선언 시 쓰레기 값이 들어간다. {}을 사용하면 0으로 초기화 된다.
 */
void default_vs_value_intialization()
{
	// default initialize (value => garbage)
	int x1;
	int* x2 = new int;

	// value initialization (value => 0 | 보장됨)
	int y1{};
	int* y2 = new int{};
	int* y3 = new int();
}

/**
 * @no.17
 * @brief	MAGIC NUMBERS	
 * @desc	const 변수의 이름을 잘 정하자. 컴파일러가 잘 최적화 해줄 것이다.
 */
float energy(float m)
{
	constexpr float SPEED_OF_LIGHT = 299792458.0;
	return m * SPEED_OF_LIGHT * SPEED_OF_LIGHT;
}

/**
 * @no.18
 * @brief	Modifying a container while looping over it
 * @desc	루프 문에서 컨테이너에 요소를 추가/삭제 할때 주의 해야 한다.
 */
void modify_while_iterating()
{
	std::vector<int> v{ 1,2,3,4 };
	// resize & move element to a new location
	// end pointer가 같은지 확인할 수 없다.
	for (auto x : v)
	{
		v.push_back(x);
	}

	// 다음과 같이 iterator를 직접 사용하면 문제가 명확히 보인다.
	for (auto it = v.begin(), end = v.end(); it != end; ++it)
	{
		v.push_back(*it);
	}

	// 다음과 같이 구현해야 문제를 해결 할 수 있다.
	const std::size_t size = v.size();
	for (std::size_t i = 0; i < size; ++i)
	{
		v.push_back(v[i]);
	}

	for (auto x : v)
	{
		std::cout << x;
	}
	std::cout << '\n';
}

/**
 * @no.19
 * @brief	returning std move of a local
 * @desc	이런 리턴 방식은 하지 않는 것을 권고한다.
 */
std::vector<int> make_vector(const int n)
{
	std::vector<int> v{ 1,2,3,4,5 };

	// return value optimization
	//return v;

	return std::move(v);
}

/**
 * @no.20
 * @brief	thinking std move moves something
 * @desc	move는 결국 right value로 변환하는 것이다.
 */

 /**
  * @no.21
  * @brief	thinking evaluation order is left to right
  * @desc	find함수가 먼저 실행 되면서 다음과 같은 결과가 도출된다.
  *			i have heard it works evenonlyyou don'eve in it
  *			하지만 C++17 이상 부터는 기대값과 동일하게 출력된다.
  */
void function_evaluation_order_not_guaranteed()
{
	std::string s = "but i have heard it works even if you don't believe in it\n";
	s.replace(0, 4, "")
		.replace(s.find("even"), 4, "only")
		.replace(s.find("don't"), 6, "");
	std::cout << s;
	std::cout << "exp : but i have heard it works even if you don't believe in it\n";
}

//int a();
//int b();
//int c();
//int g(int, int, int);
void function_evaluation_order_not_guaranteed2()
{
	// 함수가 a, b, c 순서대로 왼쪽부터 오른쪽 까지 실행 된다는 보장이 없다.
	// 따라서 a, b, c 함수 간에 영향성이 있으면 문제가 발생 할 수 있다.
	//g(a(), b(), c());
}

/**
 * @no.23
 * @brief	unnecessary heap allocation
 * @desc	불필요한 동적 할당은 지양한다. 지역변수를 쓰자!
 */
void unnecessary_heap_allocation1()
{
	// heap allocation
	int* number1 = new int(30);
	delete(number1);

	// stack allocation
	int number2{30};
}

/**
 * @no.24
 * @brief	Not using unique ptr and shared ptr
 * @desc	스마트 포인터를 사용하자
 */
void unnecessary_heap_allocation2()
{
	std::unique_ptr<int> iptr = std::make_unique<int>(30);
}

/**
 * @no.25
 * @brief	any use of new and delete
 * @desc	아래와 같이 생성자에서 동적할당을 하고 소멸자에서 delete를 하는 행동을 멤버변수로 스마트 포인터를 두어 해결하라.
 *			클래스가 오브젝트의 소유권을 생각하지 마라. 그것은 별개의 일이다.
 */
struct SomeResource {};

class widget 
{
public:
	widget() : m_uptr(std::make_unique<SomeResource>()) {};

private:
	//SomeResource* meta;
	std::unique_ptr<SomeResource> m_uptr;
};

/**
 * @no.26
 * @brief	any manual resource management
 * @desc	파일 읽기/쓰기와 같이 기능을 하는 오브젝트는 수동으로 생성/삭제가 아닌 RAII를 사용하여 직접하도록 하여야 한다.
 */
void read_from_a_file(char* name)
{
	std::ifstream input{ name }; // RAII
	// 자동으로 스코프에서 나가면 삭제된다.
}

/**
 * @no.27
 * @brief	Thinking raw pointers are bad
 * @desc	포인터가 소유권을 따지지 않는 상황에서는 스마트 포인터를 사용하는 것 보다는 raw 포인터를 사용하는 것이 좋다.
 */

 /**
  * @no.28
  * @brief	using shared ptr when unique ptr would do
  * @desc	unique_ptr에서 shared로 move하는 것은 쉽지만, shared_ptr에서 unique_ptr로 이동하는 것은 문제가 발생할 수 있다.
  *			따라서 unique_ptr이 사용될 수 있으면 최대한 unique_ptr를 사용하자
  */

  /**
   * @no.29
   * @brief	Thinking shared ptr is thread-safe
   * @desc	
   */
struct Resource
{
	int x{0};
};

void worker(std::shared_ptr<Resource> noisy)
{
	for (int i = 0; i < 50000; ++i)
	{
		noisy->x++;
	}
}

void share_ptr_is_NOT_threadsafe()
{
	auto r = std::make_shared<Resource>();
	
	std::thread t1(worker, r);
	std::thread t2(worker, r);

	t1.join();
	t2.join();

	std::cout << r->x << '\n';
}

/**
 * @no.30
 * @brief	Mixing up const ptr vs ptr to const
 */
void const_ponter_vs_pointer_to_const()
{
	int x = 0;

	const int* ptr1 = &x;	// 포인터 주소값은 변경 가능하지만, 포인터가 가르키는 주소에 있는 내부 값은 변경 불가능
	int const* ptr2 = &x;	// x의 값을 변경할 수 없다. (*ptr2의 값을 변경할 수 없음)
	int* const ptr3 = &x;	// 포인터 주소값은 변경 불가능하지만, 포인터가 가르키는 주소에 있는 내부 값은 변경 가능
}

/**
 * @no.31
 * @brief	ignoring compiler warning
 */

int main(void)
{
	share_ptr_is_NOT_threadsafe();
	return 0;
}