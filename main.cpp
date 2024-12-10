/**
 * @Title	벗어 나야 할 C++ 뉴비의 습관
 * @brief	31가지 C++ 뉴비 들이 버려야 하는 습관 31가지 예제
 * @URL		https://www.youtube.com/watch?v=i_wDa2AS_8w&list=PLJ_usHaf3fgM5vOBPY-hXAjUy6SbgE-KG
 */

#include <iostream>

#include <string>
#include <vector>
#include <array>
#include <bit>
#include <unordered_map>

#include <algorithm>

/**
 * @no.1
 * @brief	using namespace std
 * @desc	namespace의 선언은 global 하게 하며, 헤더에 있으면 종속성이 생기므로, 헤더에 선언하지 말자
 *			또한 사용하는 부분만 선언해서 사용하자
 */

//using namespace std;
using std::string, std::cout, std::endl;

void using_namespace_std()
{
	string s{ "hello, world!" };
	cout << s << endl;
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
 * @brief	thinking class members init in order of init list
 * @desc	생성자에서 초기화는 초기화 리스트의 선언 된 순서가 아닌 클래스의 멤버 선언 순서로 초기화 된다.
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
 * @brief 16번
 * @ Not Knowing about default vs value intialization
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

int main(void)
{
	use_value();
	return 0;
}