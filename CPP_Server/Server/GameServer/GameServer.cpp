#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>

// [Lock 기초]
// atomic도 좋은 방법이지만, 일반적인 상황에서는 lock을 걸어서 접근한다. 

vector<int32> v;		
// 앞에서 나오 예시를 해결하자 -- lock 사용 -- mutex 헤더 필요

// Mutual Exclusive (상호배타적)
// 내가 먼저 이 lock을 획득했으면 다른 누군가는 절대 동시에 등시에 등장할 수 없다. 나만 사용할거야! 
mutex m;		// 좌물쇠라고 보면 됨. 

void Push()
{
	for (int32 i = 0; i < 10000; ++i)
	{
		// 좌물쇠 잠그기 (내가 이 데이터 건들동안 다른 애가 접근할 수 없도록, 순차적으로 접근하도록 하는 잠금장치)
		m.lock();

		// 단 lock을 너무 많이 써서 좋지는 않다. 경합이 너무 심해져서 여기서 한번에 한명만 통과를 할 수 있어서 실질적으로 이 코드는 싱글스레드로 동작하는 개념으로 볼 수 있음. 
		// 조금 느리게 동작할 수 있음. 
		v.push_back(i);

		// 좌물쇠 풀기
		m.unlock();
	}
}

int main()
{
	std::thread t1(Push);
	std::thread t2(Push);

	t1.join();
	t2.join();

	cout << v.size() << endl;
}
