/**
 * @Title ���� ���� �� C++ ������ ����
 * @brief 31���� C++ ���� ���� ������ �ϴ� ���� 31���� ����
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
 * @desc	namespace�� ������ global �ϰ� �ϸ�, ����� ������ ���Ӽ��� ����Ƿ�, ����� �������� ����
 *			���� ����ϴ� �κи� �����ؼ� �������
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
 * @desc	std endl�� ��� ���۸� flush(�ð��� ���� ����) �ϹǷ� ���� �ȿ����� ������� �ʴ´�.
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
 * @desc	�ε����� ����ϴ� �� ���� range base�� ����ϴ� ���� ����.
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
 * @desc	���𰡸� �Ҷ� std �˰����� ����ϴ� ���� ����.
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
 * @desc	C ��Ÿ���� �迭 ���� ���Ĵٵ� array�� ����ϴ� ���� ����.
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
 * @desc	C ��Ÿ���� �迭 ���� ���Ĵٵ� array�� ����ϴ� ���� ����.
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

// ���� ����� �����Ͽ� ���� bit field ���� ��
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
 * @brief 16��
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
