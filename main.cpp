/**
 * @Title 벗어 나야 할 C++ 뉴비의 습관
 * @brief 31가지 C++ 뉴비 들이 버려야 하는 습관 31가지 예제
 * @URL https://www.youtube.com/watch?v=i_wDa2AS_8w&list=PLJ_usHaf3fgM5vOBPY-hXAjUy6SbgE-KG
 */

#include <iostream>
#include <string>
#include <vector>
#include <array>
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
void train_model(const std::vector<int>& data, auto& model)
{
	/* 
	for (std::size_t i = 0; i < data.size(); ++i)
	{
		model.update(data[i]);
	}
	*/

	for (const auto& x : data)
	{
		model.update(x);
	}
}

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
 * @brief 16번
 * @ Not Knowing about default vs value intialization
 */
void default_vs_value_intialization()
{
	// default initialize (value => garbage)
	int x1;
	int* x2 = new int;

	// value initialization (value => 0 | garentee)
	int y1{};
	int* y2 = new int{};
	int* y3 = new int();
}

int main(void)
{
	return 0;
}
