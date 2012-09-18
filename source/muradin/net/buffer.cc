#include <muradin/net/buffer.h>
#include <algorithm>
#include <assert.h>



/************************************************************************/
/*                                                                      */
/************************************************************************/
namespace muradin
{
namespace base{

	const char channel_buffer::kCRLF[] = "\r\n";


	channel_buffer::channel_buffer()
		: buffer_(kCheapPrepend + kInitialSize),
		readerIndex_(kCheapPrepend),
		writerIndex_(kCheapPrepend)
	{
		assert(readableBytes() == 0);
		assert(writableBytes() == kInitialSize);
		assert(prependableBytes() == kCheapPrepend);

	}

	// default copy-ctor, dtor and assignment are fine

	void 	channel_buffer::swap(channel_buffer& rhs)
	{
		buffer_.swap(rhs.buffer_);
		std::swap(readerIndex_, rhs.readerIndex_);
		std::swap(writerIndex_, rhs.writerIndex_);
	}

	size_t 	channel_buffer::readableBytes() const
	{ return writerIndex_ - readerIndex_; }

	size_t 	channel_buffer::writableBytes() const
	{ return buffer_.size() - writerIndex_; }

	size_t 	channel_buffer::prependableBytes() const
	{ return readerIndex_; }

	const char* 	channel_buffer::peek() const
	{ return begin() + readerIndex_; }

	char*			channel_buffer::read_ptr()
	{ return begin() + readerIndex_; }

	const char* 	channel_buffer::findCRLF() const
	{
		const char* crlf = std::search(peek(), beginWrite(), kCRLF, kCRLF+2);
		return crlf == beginWrite() ? NULL : crlf;
	}

	const char* 	channel_buffer::findCRLF(const char* start) const
	{
		assert(peek() <= start);
		assert(start <= beginWrite());
		const char* crlf = std::search(start, beginWrite(), kCRLF, kCRLF+2);
		return crlf == beginWrite() ? NULL : crlf;
	}

	// retrieve returns void, to prevent
	// string str(retrieve(readableBytes()), readableBytes());
	// the evaluation of two functions are unspecified
	void 	channel_buffer::retrieve(size_t len)
	{
		assert(len <= readableBytes());
		readerIndex_ += len;
	}

	void 	channel_buffer::retrieveUntil(const char* end)
	{
		assert(peek() <= end);
		assert(end <= beginWrite());
		retrieve(end - peek());
	}

	void 	channel_buffer::retrieveInt32()
	{
		retrieve(sizeof(int));
	}


	void	channel_buffer::append(const channel_buffer& another)
	{
		if(another.readableBytes () > 0)
			append (another.peek (),another.readableBytes ());
	}

	void 	channel_buffer::retrieveAll()
	{
		readerIndex_ = kCheapPrepend;
		writerIndex_ = kCheapPrepend;
	}

	std::string 	channel_buffer::retrieveAsString()
	{
		std::string str(peek(), readableBytes());
		retrieveAll();
		return str;
	}

	void 	channel_buffer::append(const std::string& str)
	{
		append(str.data(), str.length());
	}

	void 	channel_buffer::append(const char* /*restrict*/ data, size_t len)
	{
		ensureWritableBytes(len);
		std::copy(data, data+len, beginWrite());
		hasWritten(len);
	}


	void 	channel_buffer::append(const void* /*restrict*/ data, size_t len)
	{
		append(static_cast<const char*>(data), len);
	}

	void 	channel_buffer::ensureWritableBytes(size_t len)
	{
		if (writableBytes() < len)
		{
			makeSpace(len);
		}
		assert(writableBytes() >= len);
	}

	char* 	channel_buffer::beginWrite()
	{ return begin() + writerIndex_; }

	const char* 	channel_buffer::beginWrite() const
	{ return begin() + writerIndex_; }

	void 	channel_buffer::hasWritten(size_t len)
	{ writerIndex_ += len; }


	void 	channel_buffer::prepend(const void* /*restrict*/ data, size_t len)
	{
		assert(len <= prependableBytes());
		readerIndex_ -= len;
		const char* d = static_cast<const char*>(data);
		std::copy(d, d+len, begin()+readerIndex_);
	}



	void 	channel_buffer::shrink(size_t reserve)
	{
		std::vector<char> buf(kCheapPrepend+readableBytes()+reserve);
		std::copy(peek(), peek()+readableBytes(), buf.begin()+kCheapPrepend);
		buf.swap(buffer_);
	}



	char*	channel_buffer::begin()
	{ return &*buffer_.begin(); }

	const char* 	channel_buffer::begin() const
	{ return &*buffer_.begin(); }


	void 	channel_buffer::makeSpace(size_t len)
	{
		if (writableBytes() + prependableBytes() < len + kCheapPrepend)
		{
			buffer_.resize(writerIndex_+len);
		}
		else
		{
			// move readable data to the front, make space inside buffer
			assert(kCheapPrepend < readerIndex_);
			size_t readable = readableBytes();
			std::copy(begin()+readerIndex_,
				begin()+writerIndex_,
				begin()+kCheapPrepend);
			readerIndex_ = kCheapPrepend;
			writerIndex_ = readerIndex_ + readable;
			assert(readable == readableBytes());
		}
	}

	bool		channel_buffer::drop_end(size_t len)
	{
		if(readableBytes () >= len){
			writerIndex_ -= len;
			return true;
		}else{
			return false;
		}
	}
};//base
};//muradin
