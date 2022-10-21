#pragma once

template <typename Something>
class BagOf {
public:
	void init(int size) {
		data.reserve(size);
	}

	Something& add(const Something& s) {
		data.push_back(s);
		return data[data.size() - 1];
	}

	std::vector<Something> data;
};