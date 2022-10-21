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

	void remove(const Something& s) {
		for (auto it = data.begin(); it != data.end(); ++it) {
			if (&s == &*it) {
				data.erase(it);
				break;
			}
		}
	}

	std::vector<Something> data;
};