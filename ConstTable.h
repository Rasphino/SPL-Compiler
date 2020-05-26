//
// Created by QZQ on 2018/6/9.
//

#ifndef SPLC_CONSTTABLE_H
#define SPLC_CONSTTABLE_H

#include <string>
#include <list>
#include <map>
#include <iostream>

struct ConstValueUnion {
	double real{};
	int integer{};
	char ch{};

	explicit ConstValueUnion(int i) : integer(i) {}

	explicit ConstValueUnion(double r) : real(r) {}

	explicit ConstValueUnion(char c) : ch(c) {}

};

enum ConstType {
	integer, real, ch
};

class ConstTable {
public:
	std::map<std::string, std::list<std::pair<ConstType, ConstValueUnion>>> table;

	bool isConst(const std::string &name) {
		if (table.find(name) == table.end()) return false;
		return !table.at(name).empty();
	}

	void printTable() {
		std::cout << "const table : \n============================";
		for (auto bucket : table) {
			std::cout << bucket.first << ": ";
			for (auto item : bucket.second)
				switch (item.first) {
					case ConstType::integer:
						std::cout << item.second.integer << ", ";
						break;
					case ConstType::real:
						std::cout << item.second.real << ", ";
						break;
					case ConstType::ch:
						std::cout << item.second.ch << ", ";
						break;
				}
			std::cout << std::endl;
		}
	}

	int getInt(const std::string &name) const {
		auto item = table.at(name).back();
		assert(item.first == ConstType::integer);
		return table.at(name).back().second.integer;
	}

	double getReal(const std::string &name) const {
		auto item = table.at(name).back();
		assert(item.first == ConstType::real);
		return table.at(name).back().second.real;
	}

	char getChar(const std::string &name) const {
		auto item = table.at(name).back();
		assert(item.first == ConstType::ch);
		return table.at(name).back().second.ch;
	}

	void addInt(const std::string &name, int i) {
		if (table.find(name) != table.end()) {
			table.at(name).push_back(std::make_pair(ConstType::integer, ConstValueUnion(i)));
		} else {
			table.insert(std::make_pair(name, std::list<std::pair<ConstType, ConstValueUnion>>()));
			table.at(name).push_back(std::make_pair(ConstType::integer, ConstValueUnion(i)));
		}
	}

	void addReal(const std::string &name, double r) {
		if (table.find(name) != table.end()) {
			table.at(name).push_back(std::make_pair(ConstType::real, ConstValueUnion(r)));
		} else {
			table.insert(std::make_pair(name, std::list<std::pair<ConstType, ConstValueUnion>>()));
			table.at(name).push_back(std::make_pair(ConstType::real, ConstValueUnion(r)));
		}
	}

	void addChar(const std::string &name, char c) {
		if (table.find(name) != table.end()) {
			table.at(name).push_back(std::make_pair(ConstType::ch, ConstValueUnion(c)));
		} else {
			table.insert(std::make_pair(name, std::list<std::pair<ConstType, ConstValueUnion>>()));
			table.at(name).push_back(std::make_pair(ConstType::ch, ConstValueUnion(c)));
		}
	}

	void remove(const std::string &name) {
		if (table.find(name) == table.end()) {
			std::cerr << "Error: try to remove a non-existent const binding " << name << std::endl;
		} else {
			assert(!table.at(name).empty());
			table.at(name).pop_back();
		}
	}
};

#endif //SPLC_CONSTTABLE_H
