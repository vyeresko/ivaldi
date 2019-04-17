#pragma once

namespace ivaldi {
	template <typename T>
	class IIterator {
	public:
		virtual ~IIterator() = default;

		virtual bool hasNext() const = 0;
		virtual void advance() = 0;
		virtual const T& get() const = 0;
	};
}