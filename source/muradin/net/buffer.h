
#ifndef MURADIN_NET_BUFFER_H__
#define MURADIN_NET_BUFFER_H__



#include <vector>
#include <string>


/// taken from  nuduo.net.buffer

namespace muradin
{
namespace base{

	class channel_buffer
	{
	public:
		static const size_t kCheapPrepend = 8;
		static const size_t kInitialSize =  1024;

		channel_buffer();

		// default copy-ctor, dtor and assignment are fine

		//! ������������
		void swap(channel_buffer& rhs);

		//! ���ؿɶ����ݵ�����
		size_t readableBytes() const;

		//! ���ؿ�д�ռ��С
		size_t writableBytes() const;

		//! ���ر��������С
		size_t prependableBytes() const;

		//! ���ص�ǰ��ָ��.��ָ�벻�ɳ��ڳ���.
		const char* peek() const;

		//! ���ص�ǰ��ָ��.��ָ�벻�ɳ��ڳ���.
		char*		read_ptr();

		//! ����ָ���ƶ�һ�ξ���
		void retrieve(size_t len);

		//! ����ָ���ƶ���end ��,end�����������ڲ��������ڵ�ָ��
		void retrieveUntil(const char* end);

		//! ����ָ���ƶ�һ��intλ��
		void retrieveInt32();

		//! ֱ�Ӹ�λ��дλ��
		void retrieveAll();

		//! ������ȡ��,��Ϊstring����,����λ��дλ��
		std::string retrieveAsString();


		//! ������������
		template <class T>
		void	append_integer(T val)
		{
			append(&val,sizeof(T));
		};

		//! ����һ���ַ���������
		void append(const std::string& str);

		//! ����channel_buffer����
		void append(const channel_buffer& another);

		//! ����char������
		void append(const char* /*restrict*/ data, size_t len);

		//! ������������
		void append(const void* /*restrict*/ data, size_t len);

		//! ���ݿ�д����,������������len��С�������д.
		void ensureWritableBytes(size_t len);

		//! ����дָ��,��ָ�벻�ɳ��ڳ���
		char* beginWrite();

		//! ����дָ��,��ָ�벻�ɳ��ڳ���
		const char* beginWrite() const;

		//! ��дָ���ƶ�һ�ξ���
		void hasWritten(size_t len);

		//! ��ǰд������(�����ݱ��浽��ǰ��ָ���ǰ��)
		void prepend(const void* /*restrict*/ data, size_t len);

		//! �����ڴ�
		void shrink(size_t reserve);

		//! ���һ��Żس�����
		const char* findCRLF() const;

		//! ��start ����ʼ,���һ��Żس�����
		const char* findCRLF(const char* start) const;

		//! ����һ����δ����β������
		bool		drop_end(size_t len);
	private:
		char* begin();

		const char* begin() const;

		void makeSpace(size_t len);

	private:
		std::vector<char> buffer_;
		size_t readerIndex_;
		size_t writerIndex_;
		static const char kCRLF[];

	};

};//base
};//muradin

#endif // MURADIN_NET_BUFFER_H__
