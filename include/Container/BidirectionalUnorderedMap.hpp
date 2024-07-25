#pragma once
#include <vector>
#include <exception>
#include <unordered_map>
#include <initializer_list>

template<typename A, typename B, typename = std::enable_if_t<!std::is_same_v<A, B>>>
class BidirectionalUnorderedMap {
public:
	BidirectionalUnorderedMap() {

	}
	BidirectionalUnorderedMap(std::initializer_list<std::pair<A, B>> list) {
		m_listA.reserve(list.size());
		m_listB.reserve(list.size());
		for (auto ptr = list.begin(), end = list.end(); ptr != end; ++ptr) {
			insertWithoutRealloc(*ptr);
		}
	}

	void insert(const A& a, const B& b) {
		m_listA.push_back(a);
		m_listB.push_back(b);
		for (int i = 0; i < m_listA.size(); ++i) {
			m_AtoB[&m_listA[i]] = &m_listB[i];
			m_BtoA[&m_listB[i]] = &m_listA[i];
		}
	}
	void insert(const B& b, const A& a) {
		m_listA.push_back(a);
		m_listB.push_back(b);
		for (int i = 0; i < m_listA.size(); ++i) {
			m_AtoB[&m_listA[i]] = &m_listB[i];
			m_BtoA[&m_listB[i]] = &m_listA[i];
		}
	}
	void insert(const std::pair<A, B>& value) {
		m_listA.push_back(value.first);
		m_listB.push_back(value.second);
		for (int i = 0; i < m_listA.size(); ++i) {
			m_AtoB[&m_listA[i]] = &m_listB[i];
			m_BtoA[&m_listB[i]] = &m_listA[i];
		}
	}

	A& operator[](const B& b) {
		auto itr = std::find(m_listB.begin(), m_listB.end(), b);
		if (itr == m_listB.end()) {
			throw std::exception("Key not found");
		}
		return *(m_BtoA.at(&(*itr)));
	}
	B& operator[](const A& a) {
		auto itr = std::find(m_listA.begin(), m_listA.end(), a);
		if (itr == m_listA.end()) {
			throw std::exception("Key not found");
		}
		return *(m_AtoB.at(&(*itr)));
	}
	const A& operator[](const B& b) const {
		auto itr = std::find(m_listB.begin(), m_listB.end(), b);
		if (itr == m_listB.end()) {
			throw std::exception("Key not found");
		}
		return *(m_BtoA.at(&(*itr)));
	}
	const B& operator[](const A& a) const {
		auto itr = std::find(m_listA.begin(), m_listA.end(), a);
		if (itr == m_listA.end()) {
			throw std::exception("Key not found");
		}
		return *(m_AtoB.at(&(*itr)));
	}
private:
	std::vector<A> m_listA;
	std::vector<B> m_listB;
	std::unordered_map<A*, B*> m_AtoB;
	std::unordered_map<B*, A*> m_BtoA;

	void insertWithoutRealloc(const std::pair<A, B>& value) {
		m_listA.push_back(value.first);
		m_listB.push_back(value.second);
		m_AtoB[&m_listA.back()] = &m_listB.back();
		m_BtoA[&m_listB.back()] = &m_listA.back();
	}
};