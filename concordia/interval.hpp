#ifndef INTERVAL_HDR
#define INTERVAL_HDR

/*!
  Class representing word interval.

*/

using namespace std;

class Interval {
public:
    explicit Interval(const unsigned char start, const unsigned char end);

    /*! Destructor.
    */
    virtual ~Interval();

	bool intersects(Interval & interval);
	
	unsigned char getLength();

    unsigned char getStart() const {
        return _start;
    }

    unsigned char getEnd() const {
        return _end;
    }

private:
    unsigned char _start;
    
    unsigned char _end;
};

#endif
