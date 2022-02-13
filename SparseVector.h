#pragma once

#include <map>


namespace js {

	//#define __TEST_
#define __TEST_ADD
	typedef unsigned int KEY;
	typedef float DATA;

	class SparseVector {
	private:
		std::map<KEY, DATA> m;

	public:
		SparseVector& operator+(const SparseVector& a) {			
			for (auto iter = a.m.begin(); iter != a.m.end(); ++iter) {
#ifdef __TEST_ADD
				const DATA comparisonData = m[iter->first];
#endif
				this->m[iter->first] += iter->second;
#ifdef __TEST_ADD
				if (comparisonData != 0.0f && iter->second != 0.0f) {
					printf_s("test(add): [%d]: this= %.0f + param: %.0f = %.0f\n", iter->first, comparisonData, iter->second, m[iter->first]);
				}
#endif
			}
			return *this;
		}

		// FIXME: find�� 2���̳� ��µ�, �������� ������?
		std::map<KEY, DATA>::iterator find(KEY key) {
			auto iter = m.find(key);
			if (iter == m.end()) {
				return m.insert({ key, 0.0f }).first;
			}
			return iter;
		}

		void print() const {
			for (auto iter = m.begin(); iter != m.end(); ++iter) {
				printf_s("[%d]: %f \t", iter->first, iter->second);
			}
			printf_s("\n");
		}

		void printDataValid() const {
			for (auto iter = m.begin(); iter != m.end(); ++iter) {
				if (iter->second == 0.0f) continue;
				printf_s("[%d]: %.0f \t", iter->first, iter->second);
			}
			printf_s("\n");
		}

		// ���Ƿ� sparse vector�� ������ ���� ��
		// �Ű� ������ UI ������ ���������� ���ص��� �ʴ� ��� �߸��� �Ű� ���� �߰� ����̴�.
		// size: ���� vector �� ������, 0���� Ŀ�� �Ѵ�.
		// percentToCreateFloat: ����� Ȯ���� ���ڸ� �����. 0~1 ���̷� �Է� �ؾ� �Ѵ�, 
		// 0.1 = 10% �� Ȯ���� ������ �����Ѵ�.
		void generate(const unsigned int size = 20, const float percentToCreateFloat = 1.0f) {
			m.clear();

#ifdef __TEST_
			printf_s("size: %d \ngen: { ", size);
#endif
			for (unsigned int i = 0; i < size; ++i) {
				// WEIGHT ���� 1 Ȯ���� ���ڸ� �Է�
				unsigned int percent = static_cast<unsigned int>(std::max(std::min(percentToCreateFloat, 0.0f), 1.0f) * 100.0f);
				unsigned int number = rand() % percent + 1;
				m[i] = number > 0 ? static_cast<float>(number - 1) : 0;
#ifdef __TEST_
				if (i % 10 == 0) printf_s("\n");
				printf_s("%.0f, ", m[i]);
#endif
			}
#ifdef __TEST_
			printf_s("}\n");
#endif
		}
	};
	
	void testCase() {
		try {
			const unsigned int testIndex = 20;

			SparseVector a;
			a.generate(20);
			printf("A:");
			a.find(testIndex)->second = 10;
			a.printDataValid();
			printf_s("\n");
			printf_s("\n");

			SparseVector b;
			b.generate(100);
			b.find(testIndex)->second = 2;
			printf("B:");
			b.printDataValid();
			printf_s("\n");
			printf_s("\n");

			SparseVector c = a + b;
			DATA cData = c.find(testIndex)->second;
			if (cData != 12.0f) {
				throw new std::exception("test failed");
			}

			c.printDataValid();
		}
		catch (std::exception e) {
			printf(e.what());
		}
	}
}