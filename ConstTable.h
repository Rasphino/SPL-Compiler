//
// Created by LHH on 2020/5/26.
//

#ifndef SPLC_CONSTTABLE_H
#define SPLC_CONSTTABLE_H

#include <string>
#include <list>
#include <map>
#include <iostream>
#include <variant>

struct ConstValueUnion {
  enum {INTEGER, REAL, CHAR} type;
  std::variant<double, int, char> val;
};

class ConstTable {
public:
	std::map<std::string, std::list<ConstValueUnion>> table;

	bool isConst(const std::string &name) {
		if (table.find(name) == table.end()) return false;
		return !table.at(name).empty();
	}

	void printTable() {
		std::cout << "const table : \n============================";
		for (const auto& bucket : table) {
			std::cout << bucket.first << ": ";
			for (auto item : bucket.second)
				switch (item.type) {
					case ConstValueUnion::INTEGER:
						std::cout << std::get<int>(item.val) << ", ";
						break;
					case ConstValueUnion::REAL:
						std::cout << std::get<double>(item.val)  << ", ";
						break;
					case ConstValueUnion::CHAR:
						std::cout << std::get<char>(item.val)  << ", ";
						break;
				}
			std::cout << std::endl;
		}
	}

	int getInt(const std::string &name) const {
		auto item = table.at(name).back();
		assert(item.type == ConstValueUnion::INTEGER);
		return std::get<int>(table.at(name).back().val);
	}

	double getReal(const std::string &name) const {
		auto item = table.at(name).back();
		assert(item.type == ConstValueUnion::REAL);
		return std::get<double>(table.at(name).back().val);
	}

	char getChar(const std::string &name) const {
		auto item = table.at(name).back();
		assert(item.type == ConstValueUnion::CHAR);
		return std::get<char>(table.at(name).back().val);
	}

	void addInt(const std::string &name, int i) {
		if (table.find(name) != table.end()) {
      table.at(name).push_back( {ConstValueUnion::INTEGER, i});
		} else {
		  std::list<ConstValueUnion> tmp = {{ConstValueUnion::INTEGER, i}};
			table.insert(std::make_pair(name, tmp));
		}
	}

	void addReal(const std::string &name, double r) {
		if (table.find(name) != table.end()) {
      table.at(name).push_back( {ConstValueUnion::REAL, r});
		} else {
      std::list<ConstValueUnion> tmp = {{ConstValueUnion::REAL, r}};
      table.insert(std::make_pair(name, tmp));
		}
	}

	void addChar(const std::string &name, char c) {
    if (table.find(name) != table.end()) {
      table.at(name).push_back( {ConstValueUnion::CHAR, c});
    } else {
      std::list<ConstValueUnion> tmp = {{ConstValueUnion::REAL, c}};
      table.insert(std::make_pair(name, tmp));
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
