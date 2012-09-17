///
/// this file taken from muduo::timestamp
///
#ifndef MURADIN_BASE_TIMESTAMP_H__
#define MURADIN_BASE_TIMESTAMP_H__

#include <muradin/config/known_env.h>
#include <muradin/config/integer_define.h>
#include <string>
#include <boost/operators.hpp>

#if (defined(_ENV_MSVCPP)) 
#include <time.h>
#else
#include <sys/time.h>
#endif

namespace muradin
{
namespace base
{


///
/// Time stamp in UTC, in microseconds resolution.
///
/// This class is immutable.
/// It's recommended to pass it by value, since it's passed in register on x64.
///
class Timestamp :public boost::less_than_comparable<Timestamp>
{
public:


	///
	/// Constucts an invalid Timestamp.
	///
	Timestamp()
	: microSecondsSinceEpoch_(0)
	{
	}

	///
	/// Constucts a Timestamp at specific time
	///
	/// @param microSecondsSinceEpoch
	explicit Timestamp(int64_t microSecondsSinceEpoch);

	void swap(Timestamp& that)
	{
	std::swap(microSecondsSinceEpoch_, that.microSecondsSinceEpoch_);
	}

	// default copy/assignment/dtor are Okay

	std::string toString() const;
	std::string toFormattedString() const;
	std::string toPathString() const;

	bool valid() const { return microSecondsSinceEpoch_ > 0; }

	// for internal usage.
	int64_t microSecondsSinceEpoch() const { return microSecondsSinceEpoch_; }
	time_t secondsSinceEpoch() const
	{ return static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond); }

	///
	/// Get time of now.
	///
	static Timestamp now();
	static Timestamp invalid();

	static const int kMicroSecondsPerSecond = 1000 * 1000;

private:
	int64_t microSecondsSinceEpoch_;
};

inline bool operator<(Timestamp lhs, Timestamp rhs)
{
  return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
}

inline bool operator==(Timestamp lhs, Timestamp rhs)
{
  return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
}

///
/// Gets time difference of two timestamps, result in seconds.
///
/// @param high, low
/// @return (high-low) in seconds
/// @c double has 52-bit precision, enough for one-microseciond
/// resolution for next 100 years.
inline double timeDifference(Timestamp high, Timestamp low)
{
  int64_t diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
  return static_cast<double>(diff) / Timestamp::kMicroSecondsPerSecond;
}

///
/// Add @c seconds to given timestamp.
///
/// @return timestamp+seconds as Timestamp
///
inline Timestamp addTime(Timestamp timestamp, double seconds)
{
  int64_t delta = static_cast<int64_t>(seconds * Timestamp::kMicroSecondsPerSecond);
  return Timestamp(timestamp.microSecondsSinceEpoch() + delta);
}

};//namespace base
};//muradin
#endif // MURADIN_BASE_TIMESTAMP_H__
