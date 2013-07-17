
#ifndef UTIL_SHAREDPOINTER_HPP_
#define UTIL_SHAREDPOINTER_HPP_

namespace tungsten { namespace util {

template<class T>
class SharedPointer {
private:
	typedef unsigned Counter;
public:
	template<class... Args>
	SharedPointer(Args&&... args) : countedData( new CountedData(std::forward<Args>(args)...) ) {}

	SharedPointer(SharedPointer& other) : countedData(other.countedData) {
		incrementReferece();
	}
	SharedPointer(const SharedPointer& other) : countedData(other.countedData) {
		incrementReferece();
	}

	SharedPointer& operator=(const SharedPointer& other) {
		if ( this == &other ) {
			return *this;
		}
		decrementReference();
		countedData = other.countedData;
		incrementReferece();
		return *this;
	}

	Counter useCount() const {
		return countedData->counter;
	}

	~SharedPointer() {
		decrementReference();
	}

private:

	void incrementReferece() {
		assert(countedData);
		++countedData->counter;
	}

	void decrementReference() {
		assert(countedData);
		if ( --countedData->counter == 0 ) {
			delete countedData;
		}
	}

	struct CountedData {
		template<class... Args>
		CountedData(Args&&... args) : data(std::forward<Args>(args)...), counter(1) {}
		T data;
		Counter counter;
	};
	CountedData *countedData;
};

}} //namespace tungsten::util

#endif //UTIL_SHAREDPOINTER_HPP_

